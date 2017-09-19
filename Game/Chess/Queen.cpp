#include "Queen.h"

Queen::Queen( const ChessTeam t_team, 
            sf::RenderWindow* t_window,
            std::pair<int, int> t_position)
    : Chess(t_team, Queen::getFileName(), Queen::getSpriteXY(), t_window, t_position) {
    
    icon.setPosition(position.first*50, position.second*50);
}  


void Queen::draw(){
    window->draw(icon);
}


bool Queen::isValid(int x, int y, std::pair<Chess*, ChessTeam> t){
    if(abs(position.first - x) == abs(position.second - y)) {
        return true;
    }
    if(x == position.first || y == position.second){
        return true;
    }
    return false;
}

