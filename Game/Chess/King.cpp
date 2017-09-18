#include "King.h"

King::King( const ChessTeam t_team, 
            sf::RenderWindow* t_window,
            std::pair<int, int> t_position)
    : Chess(t_team, King::getFileName(), King::getSpriteXY(), t_window, t_position) {
    
    icon.setPosition(position.first*50, position.second*50);
    //Make valid moves     
    validMoves.push_back(std::make_pair(-1,-1));
    validMoves.push_back(std::make_pair(-1,0));
    validMoves.push_back(std::make_pair(-1,1));
    validMoves.push_back(std::make_pair(0,-1));
    validMoves.push_back(std::make_pair(0,0));
    validMoves.push_back(std::make_pair(0,1));
    validMoves.push_back(std::make_pair(1,-1));
    validMoves.push_back(std::make_pair(1,0));
    validMoves.push_back(std::make_pair(1,1));
}  


void King::draw(){
    window->draw(icon);
}


bool King::isValid(int x, int y, std::pair<std::shared_ptr<Chess>, ChessTeam> t){
    auto pair = std::make_pair(position.first - x, position.second - y);
    for(int i = 0; i < validMoves.size(); i++){
        if(validMoves[i].first == pair.first && validMoves[i].second == pair.second){
            return true;
        }
    }
    return false;
}

