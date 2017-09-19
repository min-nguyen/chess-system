#include "Pawn.h"

Pawn::Pawn( const ChessTeam t_team, sf::RenderWindow* t_window, std::pair<int, int> t_position)
    :   Chess(t_team, Pawn::getFileName(), Pawn::getSpriteXY(), t_window, t_position), 
        initialPosition(t_position) {

    icon.setPosition(position.first*50, position.second*50);
}  


void Pawn::draw(){
    window->draw(icon);
}

bool Pawn::isValid(int x, int y, std::pair<Chess*, ChessTeam> t){
    // if(t.second == team){
    //     return false;
    // }
    // //Check correct direction -- Blues move up
    // if(team == ChessTeam::Red){
    //     //Check if attempt to take opponent piece
    //     if(((x == position.first + 1) || (x == position.first - 1)) && (y - position.second == 1)){
    //         if((t.second != ChessTeam::Empty) ){
    //             return true;
    //         }
    //     }
    //     if(x == position.first){
    //         //Check if pawn is at starting position
    //         if((initialPosition == position) && (y - position.second == 2) ){
    //             return true; 
    //         }
    //         //Check if default move forward by 1
    //         if((y - position.second) == 1 && (x == position.first)){
    //             return true;
    //         }
    //     }
    // }
    // else if(team == ChessTeam::Blue){
    //     //Check if attempt to take opponent piece
    //     if(((x == position.first + 1) || (x == (position.first - 1))) && ((position.second - y) == 1)) {
    //       if((t.second != ChessTeam::Empty)){
    //        return true;
    //       }
    //     }
    //     if(x == position.first){
    //         //Check if pawn is at starting position
    //         if((initialPosition == position) && ((position.second - y) == 2) ){
    //             return true; 
    //         }
    //         //Check if default move forward by 1
    //         if((position.second - y) == 1){
    //             return true;
    //         }
    //     }
    // }

    return false;
}
