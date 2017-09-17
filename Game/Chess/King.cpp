#include "King.h"

King::King( const ChessTeam t_team, 
            std::string fileName, 
            sf::RenderWindow* t_window)
    : Chess(t_team, fileName, t_window) {
    

    position = std::make_pair(5, 5);
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

void King::move(){ 
    
}

void King::add(){ 

}

void King::remove(){ 
    
}

void King::draw(){
    window->draw(icon);
}