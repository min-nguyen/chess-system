#include "HostRoom.h"

HostRoom::HostRoom(sf::RenderWindow* t_window, Client& t_client): window(t_window), client(t_client){
    font.loadFromFile("./Font/Roboto-Thin.ttf");
    sf::Text title("CHESS ENGINE", font);
    title.setCharacterSize(30);
    title.setPosition(200, 0);
    title.setStyle(sf::Text::Bold);
    title.setColor(sf::Color::Red);
}

void HostRoom::deleteRoom(){

}

void HostRoom::insertRoom(){
    
}

void HostRoom::update(){
    //Check if any new rooms
    std::string lobbyRoom = client.lobbyRoomUpdate();
    if(lobbyRoom != ""){
        sf::Text room(lobbyRoom, font);
        title.setCharacterSize(30);
        title.setPosition(200, tabs.size()*50);
        title.setStyle(sf::Text::Bold);
        title.setColor(sf::Color::Red);
        tabs.push_back(title);
    }
}

void HostRoom::draw(){
    window->draw(title);
    for(auto it = tabs.begin(); it != tabs.end(); it++){
        window->draw(*it); 
    }
}