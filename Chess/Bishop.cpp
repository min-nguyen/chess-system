#include "Bishop.h"

Bishop::Bishop( const ChessTeam t_team,  
    sf::RenderWindow* t_window,
    std::pair<int, int> t_position)
: Chess(t_team, Bishop::getFileName(), Bishop::getSpriteXY(), t_window, t_position) {
    icon.setPosition(position.first*50, position.second*50);
}  


void Bishop::draw(){
    window->draw(icon);
}

bool Bishop::isValid(int x, int y, std::pair<Chess*, ChessTeam> t){
    return (abs(position.first - x) == abs(position.second - y)) ? true : false;
}
