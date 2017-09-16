#include "King.h"

King::King(ChessTeam::Team t_team, std::string fileName)
    : Chess(t_team, fileName) {
    icon = spriteMaker.makeSprite("ICON", std::make_pair(0, 0), 50, 50);

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

