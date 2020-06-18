//
//  Game.hpp
//  newTryForGame
//
//  Created by Lukman Hanafi  on 25/05/20.
//  Copyright © 2020 Lukman Hanafi . All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include <curses.h>
#include "Player.hpp"
#include "Inventory.hpp"
#include "Monster.hpp"

class Game {
    
public:
    Game();
    void homeMenu();
    void firstTime();
    void Battle();
    void showStats();
    void startInventory();
    void Inventory();
    void goTo();
    void useItem(int itemSlot);
    void setGameRunning(bool game_Running);
    void dialogContinue();
    void map();
    void town();
    void arena();
    void maze();
    void store();
    void bar();
    void bartender();
    void moneyChecker();
    void storeBuyMenu();
    void storeSellMenu();
    void inventoryChecker();
    void thatOneCreepyGuyInTheCorner();
    bool getGameRunning();
    void wrongInput();
    void itemDrop();
    void sortInventory();
    void setCurrentLocation(std::string cL);
    void setBattleLocation(std::string bL);
    void mainMenu();

    
private:
    bool game_Running = true;
    int choice, tempSellChoice;
    int costToBuy = 3;
    int chanceDrop, mazePicker, itemDropChance, moneyDrop;
    std::string Response;
    bool Home = false;
    bool Town;
    bool Store = false;
    bool Bar = false;
    bool arenaUnlocked = false;
    bool mazeUnlocked = false;
    bool epicNews = false;
    bool knowMaze = false;
    std::string currentLocation;
    std::string battleLocation;
};
#endif /* Game_hpp */
