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
                if(position == node.position && position != sf::Vector2f(-99.f, -99.f)){
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
    if(gameover){
        drawGameoverScreen();
    }else{
        sf::Font font;
        if (!font.loadFromFile("../assets/arial.ttf")) {
            std::cerr<< "was not able to load font -> arial.ttf"<<std::endl;
        }
        sf::Text text;
        text.setFont(font);
        text.setPosition(sf::Vector2f(0.f, 0.f));
        text.setString("score: " + std::to_string(points) + "\nlevel: " + std::to_string(level));
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        window.draw(text);
    }
};

void lineCheckAndClear(std::vector<Node> gridArray, std::vector<Piece>& pieceArray){
    std::vector<float> clearableLines;
    float clearableLineCount = 0;
    int filledNodeCount = 0;

    std::vector<sf::Vector2f> allPiecePositions;
    for(Piece& piece : pieceArray){
        if(piece.active == false){
            for(sf::Vector2f position : piece.getAllPositions()){
                allPiecePositions.push_back(position);
            }
        }
    }

    for(float col = colLimit - 1; col >= 0; --col){
        for(float row = rowLimit - 1; row >= 0; --row){

            for(sf::Vector2f position : allPiecePositions){
                if(position == sf::Vector2f(row, col)){
                    filledNodeCount++;
                }

            }
        }
        if(filledNodeCount == 10){
            clearableLines.push_back(col);
        }
        filledNodeCount = 0;
    }

    clearableLineCount = clearableLines.size();
    updatePointsAndLevel(clearableLineCount);

    if(clearableLineCount > 0){
        for(Piece& piece : pieceArray){
            if(piece.active == false){
                for(float yPos : clearableLines){
                    if(piece.centerPosition.y == yPos){
                        piece.centerPosition = sf::Vector2f(-99.f, -99.f);
                    }
                    for (sf::Vector2f& position : piece.positions) {
                        if (position.y == yPos) {
                            position = sf::Vector2f(-99.f, -99.f);
                        }
                    }
                }
            }
        }

        std::vector<sf::Vector2f> piecePositions;
        for(float col = clearableLines[0]; col >= 0; --col){
            for(Piece& piece : pieceArray){
                if(piece.active == false){
                    if(piece.centerPosition.y == col){
                        if(!checkVerticalPieceCollision({piece.centerPosition}, pieceArray)){
                            piece.centerPosition.y += clearableLineCount;
                        }
                    }
                    for(sf::Vector2f& position : piece.positions){
                        if(position.y == col){
                            piecePositions.push_back(position);
                            if(!checkVerticalPieceCollision(piecePositions, pieceArray)){
                                position.y += clearableLineCount;
                            }
                            piecePositions.clear();
                        }
                    }
                }
            }
            drawGrid(gridArray, pieceArray);
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
                checkGameover(pieceArray);
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
        for(Piece comparePiece : pieceArray){
            if(comparePiece.active == false){
                for(sf::Vector2f comparePiecePosition : comparePiece.getAllPositions()){
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
            for(Piece comparePiece : pieceArray){
                if(comparePiece.active == false){
                    for(sf::Vector2f comparePiecePosition : comparePiece.getAllPositions()){
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
            for(Piece comparePiece : pieceArray){
                if(comparePiece.active == false){
                    for(sf::Vector2f comparePiecePosition : comparePiece.getAllPositions()){
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

void updatePointsAndLevel(int lineCount){
    points += (lineCount * 10) * level;
    points >= 100 ? level = floor(points / 100) : level = 1;
    multiplier += static_cast<float>(level) / 10.0f;
};

void checkGameover(std::vector<Piece> pieceArray){
    for(Piece piece : pieceArray){
        for(sf::Vector2f pos : piece.getAllPositions()){
            if(pos.y < 0){
                gameover = true;
            }
        }
    }
}

void drawGameoverScreen(){
    sf::RectangleShape rect;
    rect.setSize({1000.f, 1000.f});
    rect.setPosition({0.f, 0.f});
    rect.setFillColor(sf::Color(0,0,0,100));
    window.draw(rect);

    sf::Font font;
    if (!font.loadFromFile("../assets/arial.ttf")) {
        std::cerr<< "was not able to load font -> arial.ttf"<<std::endl;
    }
    sf::Text text;
    text.setFont(font);
    text.setPosition(sf::Vector2f(400.f, 400.f));
    text.setString("well done! your score is: " + std::to_string(points));
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    window.draw(text);
}
