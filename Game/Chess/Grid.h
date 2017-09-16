#ifndef GRID_H
#define GRID_H

#include <stdio.h>
#include <stdlib.h>
#include "Chess.h"
#include "SpriteSheet.h"
#include <utility>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <array>

struct ChessGrid {
    enum Colour {
        White, 
        Black
    };
};
class Grid {
    using ChessPiece = std::pair<Chess*, ChessTeam::Team>;
public:
    Grid(sf::RenderWindow* t_window): 
        window(t_window), 
        spriteMaker(SpriteSheet("./chessgrid.png")){

        //Get grid sprite, set position
        chessGrid = spriteMaker.makeSprite("Grid", std::make_pair(0,0), 1000, 1000);
        chessGrid->setPosition(sf::Vector2f(0, 0));

        //Initialise empty grid
        for(auto itA = grid.begin(); itA != grid.end(); ++itA){
            for(auto itB = itA->begin(); itB != itA->end(); ++itB){
                *itB = std::make_pair(nullptr, ChessTeam::Empty);
            }
        }
    }
    //Draw grid to window
    void drawGrid(){
        window->draw(*chessGrid);
    }
    
private:
    SpriteSheet spriteMaker;
    std::array<std::array<ChessPiece, 10>, 10> grid;
    sf::Sprite* chessGrid = nullptr;
    sf::RenderWindow* window = nullptr;
}; 

#endif 