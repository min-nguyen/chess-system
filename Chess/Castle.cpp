#include "Castle.h"

Castle::Castle( const ChessTeam t_team,  
    sf::RenderWindow* t_window,
    std::pair<int, int> t_position)
: Chess(t_team, Castle::getFileName(), Castle::getSpriteXY(), t_window, t_position) {
    icon.setPosition(position.first*50, position.second*50);

}  


void Castle::draw(){
    window->draw(icon);
}

bool Castle::isValid(int x, int y, std::pair<Chess*, ChessTeam> t){
    return (position.first == x || position.second == y) ? true : false;
}
