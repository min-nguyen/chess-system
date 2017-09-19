#include "HostRoom.h"

HostRoom::HostRoom(sf::RenderWindow* t_window): window(t_window){
    font.loadFromFile("./Font/Roboto-Thin.ttf");
    sf::Text title("CHESS ENGINE", font);
    title.setCharacterSize(30);
    title.setPosition(200, 0);
    title.setStyle(sf::Text::Bold);
    title.setColor(sf::Color::Red);
    tabs.push_back(title);
}

void HostRoom::deleteRoom(){

}

void HostRoom::insertRoom(){
    
}

void HostRoom::draw(){
    for(auto it = tabs.begin(); it != tabs.end(); it++){
        window->draw(*it); 
    }
}