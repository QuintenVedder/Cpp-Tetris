#include "utilities.h"

void initGrid(std::vector<Node>& gridArray){
    for(float i = 0; i < rowLimit; ++i){
        for(float j = 0; j < colLimit; ++j){
            Node node;
            node.position = {i, j};
            node.color = sf::Color::Black;
            node.outlineColor = sf::Color::White;
            gridArray.push_back(node);
        }
    }
}

void drawGrid(std::vector<Node>& gridArray, std::vector<Piece>& pieceArray){
    for(Node& node : gridArray){
        float xPos = (node.position.x * rectSize.x) + startPositionX;
        float yPos = (node.position.y * rectSize.y) + startPositionY;

        sf::RectangleShape rect;
        rect.setSize(rectSize);
        rect.setOutlineColor(node.outlineColor);
        rect.setOutlineThickness(2);
        rect.setPosition({xPos, yPos});
        rect.setFillColor(node.color);
        window.draw(rect);

        for(Piece& piece : pieceArray){
            std::vector<sf::Vector2f> positions = piece.getAllPositions();
            for(sf::Vector2f& position : positions){
                if(position == node.position){
                    sf::RectangleShape rect;
                    rect.setSize(rectSize);
                    rect.setOutlineColor(node.outlineColor);
                    rect.setOutlineThickness(2);
                    rect.setPosition({xPos, yPos});
                    rect.setFillColor(piece.color);
                    window.draw(rect);
                }
            }
        }
    }
}

void lineCheckAndClear(std::vector<Node> gridArray, std::vector<Piece> pieceArray){
    cpp_dump("function call");
    std::vector<float> clearableLines;
    int clearableLineCount;
    bool emptyNode = false;
    for(float i = rowLimit - 1; i >= 0; --i){
        for(float j = colLimit - 1; j >= 0; --j){
            for(Node node : gridArray){
                for(Piece& piece : pieceArray){
                    if(piece.active == false){
                        for(sf::Vector2f position : piece.getAllPositions()){
                            if(node.position != position){
                                emptyNode = true;
                                break;
                            }
                        }
                    }
                }
                if(emptyNode == true){
                    break;
                }
            }
            if(emptyNode == true){
                break;
            }
        }
        if(emptyNode == false){
            clearableLines.push_back(i);
        }
        emptyNode = false;
    }

    clearableLineCount = clearableLines.size();

    for(Piece& piece : pieceArray){
        if(piece.active == false){
            for(int yPos : clearableLines){
                if(piece.centerPosition.y == yPos){
                    piece.centerPosition = sf::Vector2f(-9999.f, -9999.f);
                }
                for (sf::Vector2f& position : piece.positions) {
                    if (position.y == yPos) {
                        position = sf::Vector2f(-9999.f, -9999.f);
                    }
                }
            }
        }
    }

    std::vector<sf::Vector2f> piecePositions;
    for(Piece piece : pieceArray){
        if(piece.active == false){
            piecePositions.push_back(piece.centerPosition);
            if(!checkVerticalPieceCollision(piecePositions, pieceArray)){
                piece.centerPosition.y += clearableLineCount;
            }
            piecePositions.clear();
            for(sf::Vector2f& position : piece.positions){
                piecePositions.push_back(position);
                if(!checkVerticalPieceCollision(piecePositions, pieceArray)){
                    position.y += clearableLineCount;
                }
                piecePositions.clear();
            }
        }
    }
};

void generatePiece(std::vector<Piece>& pieceArray, std::vector<std::vector<char>>& bag){
    lineCheckAndClear(gridArray, pieceArray);
    std::vector<char>& set = bag.front();
    char piecShape = set.front();
    if(set.size() <= 1){
        bag.erase(bag.begin());
    }else{
        set.erase(set.begin());
    }

    Piece piece(sf::Vector2f{rowLimit/2, 0}, piecShape, tetrisColors[piecShape]);
    pieceArray.emplace_back(piece);
}

void moveActivePieceDown(std::vector<Piece>& pieceArray){
    for(Piece& piece : pieceArray){
        if(piece.active){
            std::vector<sf::Vector2f> positions = piece.getAllPositions();
            if(checkVerticalPieceCollision(positions, pieceArray)){
                piece.active = false;
                generatePiece(pieceArray, bag);
            }else{
                piece.moveDown();
            }
        }
    }
};

bool checkVerticalPieceCollision(std::vector<sf::Vector2f> positions, std::vector<Piece> pieceArray){
    for(sf::Vector2f& position : positions){
        if(position.y >= colLimit - 1){
            return true;
        }
        for(Piece& comparePiece : pieceArray){
            if(comparePiece.active == false){
                for(sf::Vector2f& comparePiecePosition : comparePiece.getAllPositions()){
                    if(position.y == comparePiecePosition.y - 1 && position.x == comparePiecePosition.x){
                        return true;
                    }
                }
            }
        }
    }
    return false;
};

bool checkHorizontalPieceCollision(std::vector<sf::Vector2f> positions, std::vector<Piece> pieceArray, bool left, bool right){
    for(sf::Vector2f& position : positions){
        if(left){
            if(position.x < 1){
                return true;
            }
            for(Piece& comparePiece : pieceArray){
                if(comparePiece.active == false){
                    for(sf::Vector2f& comparePiecePosition : comparePiece.getAllPositions()){
                        if(position.y == comparePiecePosition.y && position.x == comparePiecePosition.x + 1){
                            return true;
                        }
                    }
                }
            }
        }
        if(right){
            if(position.x >= rowLimit - 1){
                return true;
            }
            for(Piece& comparePiece : pieceArray){
                if(comparePiece.active == false){
                    for(sf::Vector2f& comparePiecePosition : comparePiece.getAllPositions()){
                        if(position.y == comparePiecePosition.y && position.x == comparePiecePosition.x - 1){
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
};

bool checkRotatedPieceCollision(std::vector<sf::Vector2f> positions, std::vector<Piece> pieceArray){
    for(sf::Vector2f& position : positions){
        if(position.x < 0){
            return true;
        }
        if(position.x >= rowLimit){
            return true;
        }
        for(Piece& comparePiece : pieceArray){
            if(comparePiece.active == false){
                for(sf::Vector2f& comparePiecePosition : comparePiece.getAllPositions()){
                    if(position.y == comparePiecePosition.y && position.x == comparePiecePosition.x){
                        return true;
                    }
                }
            }
        }
    }
    return false;
};

void movementActivePiece(std::vector<Piece>& pieceArray, sf::Keyboard::Key& pressedKey, bool& KeyReleased, bool& KeyHold){
    for(Piece& piece : pieceArray){
        if(piece.active){
            std::vector<sf::Vector2f> activePiecePositions = piece.getAllPositions();
            if (KeyReleased || KeyHold) {
                if (pressedKey == sf::Keyboard::Left)
                {
                    if(!checkHorizontalPieceCollision(activePiecePositions, pieceArray, true, false) && !checkVerticalPieceCollision(activePiecePositions, pieceArray)){
                        piece.moveLeft();
                    }
                }
                else if (pressedKey == sf::Keyboard::Right)
                {
                    if(!checkHorizontalPieceCollision(activePiecePositions, pieceArray, false, true) && !checkVerticalPieceCollision(activePiecePositions, pieceArray)){
                        piece.moveRight();
                    }
                }
                else if (pressedKey == sf::Keyboard::Up && KeyHold == false)
                {
                    std::vector<sf::Vector2f> positions = MOCK_calculatePiecePositions(piece.centerPosition, piece.shape, MOCK_Rotate(piece.rotation));
                    if(!checkRotatedPieceCollision(positions, pieceArray)){
                        piece.Rotate();
                        activePiecePositions = piece.getAllPositions();
                    }
                    positions.clear();
                }
                else if (pressedKey == sf::Keyboard::Down && KeyHold == false)
                {
                    bool canInstantDown = false;

                    std::vector<sf::Vector2f> tempRestorationPositions = piece.getAllPositions();
                    activePiecePositions = piece.getAllPositions();
                    for(int i = 0; i <= colLimit; i++){
                        for(sf::Vector2f& position : activePiecePositions){
                            position.y += 1;
                        }
                        if(checkVerticalPieceCollision(activePiecePositions, pieceArray)){
                            canInstantDown = true;
                            break;
                        }
                    }

                    if(canInstantDown){
                        sf::Vector2f centerPosition = activePiecePositions.back();
                        activePiecePositions.pop_back();

                        piece.positions = activePiecePositions;
                        piece.centerPosition = centerPosition;
                        piece.active = false;
                        generatePiece(pieceArray, bag);
                    }else{
                        sf::Vector2f centerPosition = tempRestorationPositions.back();
                        tempRestorationPositions.pop_back();

                        piece.positions = tempRestorationPositions;
                        piece.centerPosition = centerPosition;
                    }
                }
                pressedKey = sf::Keyboard::Unknown;
                KeyReleased = false;
            }
        }
    }
};

void generateBag(std::vector<char>pieceShapes, std::vector<std::vector<char>>& bag, int bagSize){
    for(int i = bag.size(); i < bagSize; i++){
        std::random_device rd;
        std::default_random_engine rng(rd());
        std::shuffle(pieceShapes.begin(), pieceShapes.end(), rng);
        bag.push_back(pieceShapes);
    }
};