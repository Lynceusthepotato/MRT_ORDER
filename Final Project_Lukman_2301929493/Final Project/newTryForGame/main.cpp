//
//  main.cpp
//  newTryForGame
//
//  Created by Lukman Hanafi  on 25/05/20.
//  Copyright © 2020 Lukman Hanafi . All rights reserved.
//
#include <iostream>
#include "Game.hpp"
#include "forTheMaze.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    Game game;
    
    while(game.getGameRunning())
    {
        game.mainMenu();
    }
    return 0;
}
