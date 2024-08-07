#include "piece.h"

void Piece::calculatePiecePositions() {
    switch (shape) {
        case 'I':
            if(rotation % 2 == 0){
                positions.push_back({centerPosition.x, centerPosition.y + 1});
                positions.push_back({centerPosition.x, centerPosition.y - 1});
                positions.push_back({centerPosition.x, centerPosition.y - 2});
            }else{
                positions.push_back({centerPosition.x + 1, centerPosition.y});
                positions.push_back({centerPosition.x - 1, centerPosition.y});
                positions.push_back({centerPosition.x - 2, centerPosition.y});
            }
            break;

        case 'O':
            // Handle case for shape O
            std::cout << "Shape is O." << std::endl;
            // Add logic specific to shape O
            break;

        case 'T':
            // Handle case for shape T
            std::cout << "Shape is T." << std::endl;
            // Add logic specific to shape T
            break;

        case 'S':
            // Handle case for shape S
            std::cout << "Shape is S." << std::endl;
            // Add logic specific to shape S
            break;

        case 'Z':
            // Handle case for shape Z
            std::cout << "Shape is Z." << std::endl;
            // Add logic specific to shape Z
            break;

        case 'J':
            // Handle case for shape J
            std::cout << "Shape is J." << std::endl;
            // Add logic specific to shape J
            break;

        case 'L':
            // Handle case for shape L
            std::cout << "Shape is L." << std::endl;
            // Add logic specific to shape L
            break;

        default:
            // Handle unknown shapes or errors
            std::cout << shape << std::endl;
            break;
    }
};

std::vector<sf::Vector2f> Piece::getAllPositions() {
    std::vector<sf::Vector2f> allPositions;
    for(sf::Vector2f position : positions){
        allPositions.push_back(position);
    }
    allPositions.push_back(centerPosition);

    return allPositions;
};

void Piece::moveDown(){
    positions.clear();
    centerPosition = {centerPosition.x, centerPosition.y + 1.f};
    calculatePiecePositions();
};

void Piece::moveLeft(){
    positions.clear();
    centerPosition = {centerPosition.x - 1.f, centerPosition.y};
    calculatePiecePositions();
};

void Piece::moveRight(){
    positions.clear();
    centerPosition = {centerPosition.x + 1.f, centerPosition.y};
    calculatePiecePositions();
};

void Piece::Rotate(){
    positions.clear();
    if(rotation >= 4){
        rotation = 0;
    }else{
        rotation++;
    }
    calculatePiecePositions();
};