#include <iostream>
#include <SFML/Graphics.hpp>

int main(){
    const int windowWidth = 800;
    const int windowHeight = 800;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Tetris");
    window.setSize(sf::Vector2u(windowWidth, windowHeight)); 

    while (window.isOpen())
    {
        window.clear(sf::Color::Black);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }

        window.display();
    }

    return 0;
}