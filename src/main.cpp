#include "main.h"

int main(){
    window.setSize(sf::Vector2u(windowWidth, windowHeight)); 

    window.setFramerateLimit(FPS);

    initGrid(gridArray);
    genPiece = true;

    while (window.isOpen())
    {
        window.clear(sf::Color::Black);

        frameCounter++;

        gameloop(gridArray, genPiece, pieceArray, frameCounter, interval);
        
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
void gameloop(std::vector<Node>& gridArray, bool& genPiece, std::vector<Piece>& pieceArray, float& frameCounter, float& interval){
    if(genPiece == true){
        generatePiece(pieceArray);
        genPiece = false;
    }
    if (frameCounter >= interval) {
        moveActivePieceDown(pieceArray);
        frameCounter = 0;
    }

    
    drawGrid(gridArray, pieceArray);
}