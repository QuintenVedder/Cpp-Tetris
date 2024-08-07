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
#include "playerInputController.cpp"


std::vector<Node> gridArray;
sf::Event event;

bool genPiece;
std::vector<Piece> pieceArray;

const float FPS = 60;
float multiplier = 1;
float frameCounter = 0;
float interval = FPS / multiplier;

float keyPressframeCounter = 0;
float keyPressInterval = 1 / multiplier;

float timeToHoldKey = 20 / multiplier;
float holdCounter = 0;
bool KeyHold = false;

bool KeyReleased = true;
sf::Keyboard::Key pressedKey = sf::Keyboard::Unknown;

int main();

void gameloop(
    std::vector<Node>& gridArray,
    bool& genPiece,
    std::vector<Piece>& pieceArray,
    float& frameCounter,
    float& interval
);