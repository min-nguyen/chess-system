#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "Client.h"
#include <functional>
#include <thread>
#include "Grid.h"

class Game {
public:
    Game(sf::RenderWindow* t_window);
    void run();
private:
    sf::RenderWindow* window = nullptr;
};

#endif