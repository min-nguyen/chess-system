#include "Pawn.h"

Pawn::Pawn( const ChessTeam t_team, sf::RenderWindow* t_window, std::pair<int, int> t_position)
    :   Chess(t_team, Pawn::getFileName(), Pawn::getSpriteXY(), t_window, t_position), 
        initialPosition(t_position) {
            
    icon.setPosition(position.first*50, position.second*50);
}  


void Pawn::draw(){
    window->draw(icon);
}

bool Pawn::isValid(int x, int y){
    return (position.first - x == position.second - y) ? true : false;
}
