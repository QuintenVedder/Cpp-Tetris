#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

// mocking the functionallity of the calculatePiecePositions() function of the piece class, used for checking collision before moving a piece
std::vector<sf::Vector2f> MOCK_calculatePiecePositions(sf::Vector2f centerPosition, char shape, int rotation) {
    std::vector<sf::Vector2f> positions;
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
            positions.push_back({centerPosition.x + 1, centerPosition.y});
            positions.push_back({centerPosition.x + 1, centerPosition.y + 1});
            positions.push_back({centerPosition.x, centerPosition.y + 1});
            break;

        case 'T':
            if(rotation == 1){
                positions.push_back({centerPosition.x, centerPosition.y - 1});
                positions.push_back({centerPosition.x + 1, centerPosition.y});
                positions.push_back({centerPosition.x - 1, centerPosition.y});
            }else if(rotation == 2){
                positions.push_back({centerPosition.x + 1, centerPosition.y});
                positions.push_back({centerPosition.x, centerPosition.y + 1});
                positions.push_back({centerPosition.x, centerPosition.y - 1});
            }else if(rotation == 3){
                positions.push_back({centerPosition.x + 1, centerPosition.y});
                positions.push_back({centerPosition.x - 1, centerPosition.y});
                positions.push_back({centerPosition.x, centerPosition.y + 1});
            }else if(rotation == 4){
                positions.push_back({centerPosition.x - 1, centerPosition.y});
                positions.push_back({centerPosition.x, centerPosition.y + 1});
                positions.push_back({centerPosition.x, centerPosition.y - 1});
            }
            break;

        case 'S':
            if(rotation == 1){
                positions.push_back({centerPosition.x, centerPosition.y - 1});
                positions.push_back({centerPosition.x + 1, centerPosition.y - 1});
                positions.push_back({centerPosition.x - 1, centerPosition.y});
            }else if(rotation == 2){
                positions.push_back({centerPosition.x, centerPosition.y - 1});
                positions.push_back({centerPosition.x + 1, centerPosition.y});
                positions.push_back({centerPosition.x + 1, centerPosition.y + 1});
            }else if(rotation == 3){
                positions.push_back({centerPosition.x - 1, centerPosition.y + 1});
                positions.push_back({centerPosition.x, centerPosition.y + 1});
                positions.push_back({centerPosition.x + 1, centerPosition.y});
            }else if(rotation == 4){
                positions.push_back({centerPosition.x - 1, centerPosition.y - 1});
                positions.push_back({centerPosition.x - 1, centerPosition.y});
                positions.push_back({centerPosition.x, centerPosition.y + 1});
            }
            break;

        case 'Z':
            if(rotation == 1){
                positions.push_back({centerPosition.x, centerPosition.y - 1});
                positions.push_back({centerPosition.x - 1, centerPosition.y - 1});
                positions.push_back({centerPosition.x + 1, centerPosition.y});
            }else if(rotation == 2){
                positions.push_back({centerPosition.x + 1, centerPosition.y - 1});
                positions.push_back({centerPosition.x + 1, centerPosition.y});
                positions.push_back({centerPosition.x, centerPosition.y + 1});
            }else if(rotation == 3){
                positions.push_back({centerPosition.x - 1, centerPosition.y});
                positions.push_back({centerPosition.x, centerPosition.y + 1});
                positions.push_back({centerPosition.x + 1, centerPosition.y + 1});
            }else if(rotation == 4){
                positions.push_back({centerPosition.x - 1, centerPosition.y + 1});
                positions.push_back({centerPosition.x - 1, centerPosition.y});
                positions.push_back({centerPosition.x, centerPosition.y - 1});
            }
            break;

        case 'J':
            if(rotation == 1){
                positions.push_back({centerPosition.x - 1, centerPosition.y});
                positions.push_back({centerPosition.x + 1, centerPosition.y});
                positions.push_back({centerPosition.x - 1, centerPosition.y - 1});
            }else if(rotation == 2){
                positions.push_back({centerPosition.x, centerPosition.y - 1});
                positions.push_back({centerPosition.x, centerPosition.y + 1});
                positions.push_back({centerPosition.x + 1, centerPosition.y - 1});
            }else if(rotation == 3){
                positions.push_back({centerPosition.x - 1, centerPosition.y});
                positions.push_back({centerPosition.x + 1, centerPosition.y});
                positions.push_back({centerPosition.x + 1, centerPosition.y + 1});
            }else if(rotation == 4){
                positions.push_back({centerPosition.x, centerPosition.y - 1});
                positions.push_back({centerPosition.x, centerPosition.y + 1});
                positions.push_back({centerPosition.x - 1, centerPosition.y + 1});
            }
            break;

        case 'L':
            if(rotation == 1){
                positions.push_back({centerPosition.x - 1, centerPosition.y});
                positions.push_back({centerPosition.x + 1, centerPosition.y});
                positions.push_back({centerPosition.x + 1, centerPosition.y - 1});
            }else if(rotation == 2){
                positions.push_back({centerPosition.x, centerPosition.y - 1});
                positions.push_back({centerPosition.x, centerPosition.y + 1});
                positions.push_back({centerPosition.x + 1, centerPosition.y + 1});
            }else if(rotation == 3){
                positions.push_back({centerPosition.x - 1, centerPosition.y});
                positions.push_back({centerPosition.x + 1, centerPosition.y});
                positions.push_back({centerPosition.x - 1, centerPosition.y + 1});
            }else if(rotation == 4){
                positions.push_back({centerPosition.x, centerPosition.y - 1});
                positions.push_back({centerPosition.x, centerPosition.y + 1});
                positions.push_back({centerPosition.x - 1, centerPosition.y - 1});
            }
            break;

        default:
            // Handle unknown shapes or errors
            std::cout << shape << std::endl;
            break;
    }

    return positions;
};

// mocking the functionallity of the Rotate() function of the piece class, used for checking collision before rotating a piece
int MOCK_Rotate(int rotation){
    if(rotation >= 4){
        rotation = 1;
    }else{
        rotation++;
    }
    return rotation;
};