#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "NodeStruct.h"
#include <vector>

//a class for pieces...
class Piece {
    private:
    public:
        const char shape;
        sf::Vector2f centerPosition;
        std::vector<sf::Vector2f> positions;
        sf::Color color;
        bool active = true;
        int rotation = 1;// 1=up 2=right 3=down 4=left

        Piece(sf::Vector2f centerPosition, const char shape, sf::Color color)
            :shape{shape}, centerPosition{centerPosition}, color{color}
        {
            calculatePiecePositions();
        };

        void calculatePiecePositions();
        std::vector<sf::Vector2f> getAllPositions();
        void moveDown();
        void moveLeft();
        void moveRight();
        void Rotate();
};