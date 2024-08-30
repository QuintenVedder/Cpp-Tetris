#pragma once

#include "main.h"
#include "piece.cpp"
#include "NodeStruct.h"
#include <vector>
#include <iostream>
#include "cpp_dump.h"
#include "mock_piece_functions.h"
#include <algorithm>
#include <random>
#include <string>

const float rowLimit = 10;
const float colLimit = 20;
const sf::Vector2f rectSize(40, 40);
float startPositionX = (windowWidth - (10 * rectSize.x)) / 2;
float startPositionY = 10;

std::map<char, sf::Color> tetrisColors = {
    {'I', sf::Color(0, 200, 200)},   // Slightly Darkened Cyan
    {'O', sf::Color(200, 200, 0)},   // Slightly Darkened Yellow
    {'T', sf::Color(200, 20, 200)},  // Slightly Darkened Magenta
    {'S', sf::Color(20, 200, 20)},   // Slightly Darkened Green
    {'Z', sf::Color(200, 20, 20)},   // Slightly Darkened Red
    {'J', sf::Color(20, 20, 200)},   // Slightly Darkened Blue
    {'L', sf::Color(220, 160, 20)},  // Slightly Darkened Orange
};

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