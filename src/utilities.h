#pragma once

#include "main.h"
#include "piece.cpp"
#include "NodeStruct.h"
#include <vector>
#include <iostream>

float rowLimit = 10;
float colLimit = 20;
sf::Vector2f rectSize(40, 40);
float startPositionX = (windowWidth - (10 * rectSize.x)) / 2;
float startPositionY = 10;

void initGrid(std::vector<Node>& gridArray);
void drawGrid(std::vector<Node>& gridArray);
void generatePiece(std::vector<Piece>& pieceArray);
void moveActivePieceDown(std::vector<Piece>& pieceArray);
bool checkVerticalPieceCollision(std::vector<sf::Vector2f>& positions, std::vector<Piece> pieceArray);
bool checkHorizontalPieceCollision(std::vector<sf::Vector2f>& positions, std::vector<Piece> pieceArray, bool left, bool right);
void movementActivePiece(std::vector<Piece>& pieceArray, sf::Keyboard::Key& pressedKey, bool& KeyReleased, bool& KeyHold);