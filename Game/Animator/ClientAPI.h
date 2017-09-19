#ifndef CLIENTAPI_H
#define CLIENTAPI_H

#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Client.h"
#include "Char.h"
#include <functional>
#include <thread>
#include <cstdlib>

class ClientAPI {
public:
    ClientAPI(Char* c);
    void update();
    static void createClient(Client& client);
    void outBuffer(char c);
    Client client;
protected:
    sf::Clock clock;
    Char* c;
private:
    
};

#endif