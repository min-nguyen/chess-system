#include "ClientAPI.h"


ClientAPI::ClientAPI(Char* c): c(c){
    
} 

void ClientAPI::update(){
    char ch = client.inBuffer();
    if (ch == 'L'){
        printf("l");
        c->updateState(CharState::WALKLEFT);
    }
    else if(ch == 'R'){
        printf("r");
        c->updateState(CharState::WALKRIGHT);
    }
    else {
        c->updateState(CharState::IDLE);
    }
    c->update(clock.getElapsedTime(), true);
    clock.restart(); 
}

void ClientAPI::createClient(Client& client){
    client.run();
    std::cout << "running " << std::flush;
}

void ClientAPI::outBuffer(char c){
    client.outBuffer(c);
} 