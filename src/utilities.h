#pragma once

#include "main.h"
#include "piece.cpp"
#include "NodeStruct.h"
#include <vector>
#include <iostream>
#include "mock_piece_functions.h"
#include <algorithm>
#include <random>
#include <string>
#include <functional>

const float rowLimit = 10;
const float colLimit = 20;
const sf::Vector2f rectSize(40, 40);
float startPositionX = (windowWidth - (10 * rectSize.x)) / 2;
float startPositionY = 10;

// fancy colors for maxium enjoyment
std::map<char, sf::Color> tetrisColors = {
    {'I', sf::Color(0, 200, 200)},   // Slightly Darkened Cyan
    {'O', sf::Color(200, 200, 0)},   // Slightly Darkened Yellow
    {'T', sf::Color(200, 20, 200)},  // Slightly Darkened Magenta
    {'S', sf::Color(20, 200, 20)},   // Slightly Darkened Green
    {'Z', sf::Color(200, 20, 20)},   // Slightly Darkened Red
    {'J', sf::Color(20, 20, 200)},   // Slightly Darkened Blue
    {'L', sf::Color(220, 160, 20)},  // Slightly Darkened Orange
};


std::map<char, std::function<std::vector<sf::Vector2f>(sf::Vector2f&, sf::Vector2f&)>> extraUiPiecePositions = {
    // a nice dose of pixel precision was needed because the fucking borders would clip into eachother
    {'I', [](const sf::Vector2f& centerPosition, const sf::Vector2f& blockSize) {
        return std::vector<sf::Vector2f>{
            {centerPosition.x - (blockSize.x/2.f) - blockSize.x, centerPosition.y},
            {centerPosition.x - (blockSize.x/2.f), centerPosition.y},
            {centerPosition.x + (blockSize.x/2.f), centerPosition.y},
            {centerPosition.x + (blockSize.x/2.f) + blockSize.x, centerPosition.y},
        };
    }},
    {'O', [](const sf::Vector2f& centerPosition, const sf::Vector2f& blockSize) {
        return std::vector<sf::Vector2f>{
            {centerPosition.x - (blockSize.x/2.f) - 1.f, centerPosition.y - (blockSize.y/2.f) - 1.f},
            {centerPosition.x + (blockSize.x/2.f), centerPosition.y - (blockSize.y/2.f) - 1.f},
            {centerPosition.x + (blockSize.x/2.f), centerPosition.y + (blockSize.y/2.f)},
            {centerPosition.x - (blockSize.x/2.f) - 1.f, centerPosition.y + (blockSize.y/2.f)},
        };
    }},
    {'T', [](const sf::Vector2f& centerPosition, const sf::Vector2f& blockSize) {
        return std::vector<sf::Vector2f>{
            {centerPosition.x, centerPosition.y - blockSize.y},
            {centerPosition.x - blockSize.x, centerPosition.y},
            {centerPosition.x + blockSize.x, centerPosition.y},
            {centerPosition.x, centerPosition.y},
        };
    }},
    {'S', [](const sf::Vector2f& centerPosition, const sf::Vector2f& blockSize) {
        return std::vector<sf::Vector2f>{
            {centerPosition.x, centerPosition.y - (blockSize.y/2.f) - 1.f},
            {centerPosition.x + blockSize.x, centerPosition.y - (blockSize.y/2.f) - 1.f},
            {centerPosition.x - 1.f, centerPosition.y + (blockSize.y/2.f)},
            {centerPosition.x - blockSize.x - 1.f, centerPosition.y + (blockSize.y/2.f)},
        };
    }},
    {'Z', [](const sf::Vector2f& centerPosition, const sf::Vector2f& blockSize) {
        return std::vector<sf::Vector2f>{
            {centerPosition.x, centerPosition.y - (blockSize.y/2.f) - 1.f},
            {centerPosition.x - blockSize.x, centerPosition.y - (blockSize.y/2.f) - 1.f},
            {centerPosition.x + 1.f, centerPosition.y + (blockSize.y/2.f)},
            {centerPosition.x + blockSize.x + 1.f, centerPosition.y + (blockSize.y/2.f)},
        };
    }},
    {'J', [](const sf::Vector2f& centerPosition, const sf::Vector2f& blockSize) {
        return std::vector<sf::Vector2f>{
            {centerPosition.x, centerPosition.y - blockSize.y},
            {centerPosition.x, centerPosition.y},
            {centerPosition.x - blockSize.x, centerPosition.y + blockSize.y},
            {centerPosition.x , centerPosition.y + blockSize.y},
        };
    }},
    {'L', [](const sf::Vector2f& centerPosition, const sf::Vector2f& blockSize) {
        return std::vector<sf::Vector2f>{
            {centerPosition.x, centerPosition.y - blockSize.y},
            {centerPosition.x, centerPosition.y},
            {centerPosition.x + blockSize.x, centerPosition.y + blockSize.y},
            {centerPosition.x , centerPosition.y + blockSize.y},
        };
    }},
};

// a lot of declarations

void initGrid(std::vector<Node>& gridArray);
void drawGrid(std::vector<Node>& gridArray, std::vector<Piece>& pieceArray);
void generatePiece(std::vector<Piece>& pieceArray, std::vector<std::vector<char>>& bag);
void moveActivePieceDown(std::vector<Piece>& pieceArray);
bool checkVerticalPieceCollision(std::vector<sf::Vector2f> positions, std::vector<Piece> pieceArray);
bool checkHorizontalPieceCollision(std::vector<sf::Vector2f> positions, std::vector<Piece> pieceArray, bool left, bool right);
void movementActivePiece(std::vector<Piece>& pieceArray, sf::Keyboard::Key& pressedKey, bool& KeyReleased, bool& KeyHold);
void generateBag(std::vector<char>pieceShapes, std::vector<std::vector<char>>& bag, int bagSize);
bool checkRotatedPieceCollision(std::vector<sf::Vector2f> positions, std::vector<Piece> pieceArray);
void lineCheckAndClear(std::vector<Node> gridArray, std::vector<Piece>& pieceArray);
void updatePointsAndLevel(int lineCount);
void checkGameover(std::vector<Piece> pieceArray);
void drawGameoverScreen();
void drawExtraUi();
void drawSmallRect(sf::Vector2f pos, sf::Vector2f size);
void drawSmallPieceShapeNextInBag(sf::Vector2f pos, sf::Vector2f size);
void drawSmallPieceShapeHold(sf::Vector2f pos, sf::Vector2f size);