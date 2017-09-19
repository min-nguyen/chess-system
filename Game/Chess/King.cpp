#include "King.h"

King::King( const ChessTeam t_team, 
            sf::RenderWindow* t_window,
            std::pair<int, int> t_position)
    : Chess(t_team, King::getFileName(), King::getSpriteXY(), t_window, t_position) {
    
    icon.setPosition(position.first*50, position.second*50);
}  


void King::draw(){
    window->draw(icon);
}


bool King::isValid(int x, int y, std::pair<Chess*, ChessTeam> t){
    auto pair = std::make_pair(position.first - x, position.second - y);
    int xMove = abs(x - position.first);
    int yMove = abs(y - position.second);
    if((xMove == 1 || yMove == 1) && (xMove <= 1 && yMove <= 1)){
        return true;
    }
    return false;
}

