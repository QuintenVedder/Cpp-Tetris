#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "NodeStruct.h"
#include <vector>

class Piece {
    private:
        const char shape;
        int rotation = 1;// 1=up 2=right 3=down 4=left

    public:
        sf::Vector2f centerPosition;
        std::vector<sf::Vector2f> positions;
        sf::Color color;
        bool active = true;

        Piece(sf::Vector2f centerPosition, const char shape, sf::Color color)
            :shape{shape}, centerPosition{centerPosition}, color{color}
        {
            calculatePiecePositions();
        };

        void calculatePiecePositions();
        std::vector<sf::Vector2f> getAllPositions();
        void moveDown();
        void moveLeft(float minimumXPosition);
        void moveRight(float maximumXPosition);
        void Rotate();
        void moveInstantDown();
};