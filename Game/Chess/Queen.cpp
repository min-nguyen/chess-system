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


bool Queen::isValid(int x, int y, std::pair<std::shared_ptr<Chess>, ChessTeam> t){
    return false;
}

