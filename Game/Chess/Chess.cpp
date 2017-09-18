#include "Chess.h"
#include "SpriteSheet.h"

Chess::Chess(   const ChessTeam t_team, 
                std::string t_fileName, 
                std::map<ChessTeam, std::pair<int, int>> t_spriteXY,
                sf::RenderWindow* t_window,
                std::pair<int, int> t_position)
            :   team(t_team), 
                spriteMaker(SpriteSheet(t_fileName)),
                window(t_window),
                position(t_position) {
    if(t_team == ChessTeam::Blue)   { 
        auto pair = t_spriteXY[ChessTeam::Blue];
        icon = spriteMaker.makeSprite("ICON", pair, 50, 50);
    }
    else if(t_team == ChessTeam::Red)   { 
        auto pair = t_spriteXY[ChessTeam::Red];
        icon = spriteMaker.makeSprite("ICON", pair, 50, 50);
    }
}  


void Chess::move(int x, int y){
    position = std::make_pair(x, y);
    icon.setPosition(x*50, y*50);
}
