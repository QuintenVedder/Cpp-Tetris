#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

const int windowWidth = 1000;
const int windowHeight = 1000;
sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Tetris");

#include "piece.h"
#include "utilities.cpp"
#include "NodeStruct.h"


std::vector<Node> gridArray;
sf::Event event;

bool genPiece;
std::vector<Piece> pieceArray;

const float FPS = 60;
const float multiplier = 1;
float frameCounter = 0;
float interval = FPS * multiplier;

int main();

void gameloop(
    std::vector<Node>& gridArray,
    bool& genPiece,
    std::vector<Piece>& pieceArray,
    float& frameCounter,
    float& interval
);