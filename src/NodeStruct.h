#pragma once

#include <SFML/Graphics.hpp>

//this is a struct.. used for defining a node and all inormation it needs to do its thing
struct Node {
    sf::Vector2f position;
    sf::Color color;
    sf::Color outlineColor;
};