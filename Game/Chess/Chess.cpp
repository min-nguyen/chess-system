#include "Chess.h"
#include "SpriteSheet.h"

Chess::Chess(   const ChessTeam t_team, 
                std::string t_fileName, 
                sf::RenderWindow* t_window,
                std::pair<int, int> t_position)
            :   team(t_team), 
                spriteMaker(SpriteSheet(t_fileName)),
                window(t_window),
                position(t_position) {

    icon = spriteMaker.makeSprite("ICON", std::make_pair(0, 0), 50, 50);

}  


void Chess::move(const int x, const int y){
    position = std::make_pair(x, y);
    icon.setPosition(x*50, y*50);
}
