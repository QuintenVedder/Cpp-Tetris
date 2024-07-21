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
            if(piece.centerPosition.y >= colLimit || checkPieceCollision(piece, pieceArray)){
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
        for(Piece& comparePiece : pieceArray){
            if(comparePiece != piece){
                // zorg dat als piece nit vergeleken kan worden met zichzelf
            }
            for(sf::Vector2f& comparePiecePosition : comparePiece.getAllPositions()){
                if(position.y >= comparePiecePosition.y - 1){
                    return true;
                }
            }
        }
    }
    return false;
};