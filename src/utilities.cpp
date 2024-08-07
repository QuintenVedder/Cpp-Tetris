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
            if(checkPieceCollision(piece, pieceArray)){
                piece.active = false;
                generatePiece(pieceArray);
            }else{
                piece.moveDown();
            }
        }
    }
};

bool checkPieceCollision(Piece& piece, std::vector<Piece> pieceArray){
    for(sf::Vector2f& position : piece.getAllPositions()){
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

void movementActivePiece(std::vector<Piece>& pieceArray, sf::Keyboard::Key& pressedKey, bool& KeyReleased, bool& KeyHold){
    for(Piece& piece : pieceArray){
        if(piece.active){
            if (KeyReleased || KeyHold) {
                if (pressedKey == sf::Keyboard::Left)
                {
                    piece.moveLeft(0);
                }
                else if (pressedKey == sf::Keyboard::Right)
                {
                    piece.moveRight(rowLimit);
                }
                else if (pressedKey == sf::Keyboard::Up && KeyHold == false)
                {
                    piece.Rotate();
                }
                else if (pressedKey == sf::Keyboard::Down)
                {
                    // piece.moveInstantDown();
                }
                pressedKey = sf::Keyboard::Unknown;
                KeyReleased = false;
            }
        }
    }
};