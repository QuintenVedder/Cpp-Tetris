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
bool checkPieceCollision(Piece& piece, std::vector<Piece> pieceArray);
void movementActivePiece(std::vector<Piece>& pieceArray, sf::Keyboard::Key& pressedKey, bool& KeyReleased, bool& KeyHold);