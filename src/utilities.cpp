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

void generatePiece(std::vector<Piece>& pieceArray){
    Piece piece(sf::Vector2f{rowLimit/2, 0}, 'I', sf::Color::Blue);
    pieceArray.emplace_back(piece);
}

void moveActivePieceDown(std::vector<Piece>& pieceArray){
    for(Piece& piece : pieceArray){
        if(piece.active){
            std::vector<sf::Vector2f> positions = piece.getAllPositions();
            if(checkVerticalPieceCollision(positions, pieceArray)){
                piece.active = false;
                generatePiece(pieceArray);
            }else{
                piece.moveDown();
            }
        }
    }
};

bool checkVerticalPieceCollision(std::vector<sf::Vector2f>& positions, std::vector<Piece> pieceArray){
    for(sf::Vector2f& position : positions){
        if(position.y >= colLimit - 1){
            return true;
        }
        for(Piece& comparePiece : pieceArray){
            if(comparePiece.active == false){
                for(sf::Vector2f& comparePiecePosition : comparePiece.getAllPositions()){
                    if(position.y >= comparePiecePosition.y - 1 && position.x == comparePiecePosition.x){
                        return true;
                    }
                }
            }
        }
    }
    return false;
};

bool checkHorizontalPieceCollision(std::vector<sf::Vector2f>& positions, std::vector<Piece> pieceArray, bool left, bool right){
    for(sf::Vector2f& position : positions){
        if(left){
            if(position.x <= 0){
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

void movementActivePiece(std::vector<Piece>& pieceArray, sf::Keyboard::Key& pressedKey, bool& KeyReleased, bool& KeyHold){
    for(Piece& piece : pieceArray){
        if(piece.active){
            std::vector<sf::Vector2f> activePiecePositions = piece.getAllPositions();
            if (KeyReleased || KeyHold) {
                if (pressedKey == sf::Keyboard::Left)
                {
                    if(!checkHorizontalPieceCollision(activePiecePositions, pieceArray, true, false)){
                        piece.moveLeft();
                    }
                }
                else if (pressedKey == sf::Keyboard::Right)
                {
                    if(!checkHorizontalPieceCollision(activePiecePositions, pieceArray, false, true)){
                        piece.moveRight();
                    }
                }
                else if (pressedKey == sf::Keyboard::Up && KeyHold == false)
                {
                    bool canRotate = false;

                    piece.rotation++;
                    piece.calculatePiecePositions();
                    activePiecePositions = piece.getAllPositions();

                    if(!checkHorizontalPieceCollision(activePiecePositions, pieceArray, true, true)){
                        canRotate = true;
                    }

                    piece.rotation--;
                    piece.calculatePiecePositions();
                    activePiecePositions = piece.getAllPositions();
                    if(canRotate){
                        piece.Rotate();
                        canRotate = false;
                    }
                }
                else if (pressedKey == sf::Keyboard::Down)
                {
                    bool canInstantDown = false;

                    std::vector<sf::Vector2f> tempRestorationPositions = piece.getAllPositions();
                    activePiecePositions = piece.getAllPositions();
                    for(int i = 1; i < colLimit+2; i++){
                        for(sf::Vector2f& position : activePiecePositions){
                            position.x += i;
                        }
                        if(checkVerticalPieceCollision(activePiecePositions, pieceArray)){
                            std::cout<<"WAT DE KANKER"<<std::endl;
                            canInstantDown = true;
                            break;
                        }
                    }

                    if(canInstantDown){
                        for(sf::Vector2f& position : activePiecePositions){
                            position.x -= 1;
                        }

                        piece.positions = activePiecePositions;
                    }else{
                        piece.positions = tempRestorationPositions;
                    }
                }
                pressedKey = sf::Keyboard::Unknown;
                KeyReleased = false;
            }
        }
    }
};