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
bool checkPieceCollision(Piece& piece, std::vector<Piece> pieceArray);