#include "Knight.h"

Knight::Knight( const ChessTeam t_team, 
            sf::RenderWindow* t_window,
            std::pair<int, int> t_position)
    : Chess(t_team, Knight::getFileName(), Knight::getSpriteXY(), t_window, t_position) {
    
    icon.setPosition(position.first*50, position.second*50);
}  


void Knight::draw(){
    window->draw(icon);
}


bool Knight::isValid(int x, int y, std::pair<Chess*, ChessTeam> t){
    if(abs(x - position.first) == 2 ){
        if (abs(y - position.second) == 1)
            return true;
    }
    if(abs(y - position.second) == 2 ){
        if (abs(x - position.first) == 1)
            return true;
    }
    return false;
}

