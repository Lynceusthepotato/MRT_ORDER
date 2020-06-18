//
//  Game.cpp
//  newTryForGame
//
//  Created by Lukman Hanafi  on 25/05/20.
//  Copyright © 2020 Lukman Hanafi . All rights reserved.
//
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

#include "Game.hpp"
#include "Player.hpp"
#include "Inventory.hpp"
#include "Monster.hpp"
#include "forTheMaze.hpp"
#include <vector>
#include <curses.h>
#include <iostream>
#include <time.h>

// Player
Player p = Player();
Item playerInventory[10];
// Item
// Name, Value
Item emptySlot = Item("", 0);
Item ruggedCloth = Item("Rugged Cloth", 2);
Item ironIngot = Item("Iron Ingot", 7);
Item roughFur = Item("Rough Fur", 5);
Item dropItem[] = {ruggedCloth,ironIngot,roughFur};
// Usable
// Name, Plus, Value
Usable carrot = Usable("Carrot", 4, 2);
Usable lesserPotion = Usable("Lesser Potion", 15, 7);
Usable apple = Usable("Apple", 5, 3);
Usable eatMe[] = {carrot, lesserPotion, apple};
// Weapon
// Name, Attack, Value
Weapon woodSword = Weapon("Wooden Sword", 5, 7);
Weapon steelSword = Weapon("Steel Sword", 7, 15);
Weapon legendarySword = Weapon("Chunchunmaru", 40, 100);
Weapon weapons[] = {woodSword, steelSword,legendarySword};
// Armor
// Name, Defense, Special, Value
Armor leatherArmor = Armor("Leather Armor", 2, 0, 15);
Armor ironArmor = Armor("Iron Armor", 5, 0, 25);
Armor sacredBeast = Armor("Valkyn Skoria", 5, 0, 100);
Armor armors[] = {leatherArmor,ironArmor,sacredBeast};
// Enemy
// Name, Health, MP, Attack, Defense, Gold drop
Monster spider = Monster("Spider", 40, 10, 6, 1, 10);
Monster goblin = Monster("Goblin", 50, 5, 5, 2, 15);
Monster BigFish = Monster("Magickarp", 10, 0, 15, 8, 25);
Monster Enemy[] = {goblin,spider,BigFish};

// other stuff
int length_of_Inventory = sizeof(playerInventory)/sizeof(playerInventory[0]);
int battleCount = 0;
int reward = 0;
int Cost = 0;
int inventoryEmptySlot = -1;

forTheMaze fTM;

Weapon tempWeapon;
Weapon anotherTemp;
Weapon emptyWeapon;
Armor tempArmor;
Armor anotherTempar;
Armor emptyArmor;
Usable tempUsable;


template<typename Base, typename T>
inline bool instanceof(const T*) {
    return std::is_base_of<Base, T>::value;
}


Game :: Game(){
}

void Game::mainMenu(){
    system("clear");
    std::cout << "==============================" << std::endl;
    std::cout << "====       COLLAPSE       ====" << std::endl;
    std::cout << "==============================" << std::endl;
    
    std::cout << "Please choose : " << std::endl;
    std::cout << "1. Start" << std::endl;
    std::cout << "2. Quit" << std::endl;
    std::cout << "Choice : ";
    currentLocation = "MainMenu";
    std::cin >> choice;
    switch(choice){
        case 1:
        {
            firstTime();
        }
            break;
        case 2:
        {
            setGameRunning(false);
            exit(0);
        }
        default:
        {
            wrongInput();
        }
    }

}

void Game::homeMenu(){
    system("clear");
    if(!Home){
        std::cout << BOLDWHITE << "Welcome to your home " << RESET << std::endl;
        std::cout << "I know it's not much but... you know" << std::endl;
        std::cout << "..." << std::endl;
        dialogContinue();
        std::cout << "I mean you can't even see it" << std::endl;
        dialogContinue();
        std::cout << "I think...... " << std::endl;
        std::cout  << "Uh see you later I guess..." << std::endl;
        dialogContinue();
        std::cout << "Ah almost forgot here some starter item" << std::endl;
        std::cout << "You recieve "<< GREEN << woodSword.getName() << RESET << " And " << GREEN << carrot.getName() << RESET << std::endl;
        std::cout << "Oh and you also want to go to the bar" << std::endl;
        playerInventory[1] = woodSword;
        playerInventory[2] = carrot;
        Home = true;
    }
    currentLocation = "Home";
    std::cout << "Please choose : " << std::endl;
    std::cout << "1. Go Outside" << std::endl;
    std::cout << "2. Stats" << std::endl;
    std::cout << "3. Inventory" << std::endl;
    std::cout << "4. Rest" << std::endl;
    std::cout << "5. Quit" << std::endl;
    std::cout << "Choice : ";
    std::cin >> choice;
    
    
    switch(choice){
        case 1 :
        {
            map();
        }
            break;
        case 2:
        {
            showStats();
        }
            break;
        case 3:
        {
            Inventory();
        }
            break;
        case 4:
        {
            std::cout << BOLDCYAN << "(-, – )…zzzZZZ" << RESET <<std::endl;
            std::cout << BOLDCYAN << "You feel refreshed" << RESET <<std::endl;
            dialogContinue();
            p.plusHP(50);
            goTo();
        }
            break;
        case 5:
        {
            setGameRunning(false);
            exit(0);
        }
            break;
        default:
        {
            wrongInput();
        }
            break;
    }
}

void Game::sortInventory(){
    auto tempitem = Item();
    for(int i = 0; i < length_of_Inventory; i++){
        for(int i = 0; i < length_of_Inventory; i++){
            if(playerInventory[i].getName() == emptySlot.getName()){
                tempitem = playerInventory[i];
                playerInventory[i] = playerInventory[i + 1];
                playerInventory[i + 1] = tempitem;
            }
        }
    }
}

void Game::firstTime(){
    startInventory();
    system("clear");
    std::cout << RED << "===============================" << std::endl;
    std::cout << "=====" << RESET << " Welcome to the game " << RED << "=====" << std::endl;
    std::cout << "===============================" << RESET <<std::endl;
    std::cout << std::endl;
    std::cout << "Hello... could you tell me your name ?" << std::endl;
    std::cin >> Response;
    p.setName(Response);
    std::cout << "Hello " << p.getName() << std::endl;
    dialogContinue();
    std::cout << "Oh i forgot to tell you, you are going to be teleported to your house !" <<std::endl;
    dialogContinue();
    homeMenu();
}

void Game::dialogContinue(){
    std::cout << "Enter anything to continue : ";
    system("read");
    system("clear");
}

void Game::goTo(){
    if(currentLocation == "Home"){
        homeMenu();
    } else if (currentLocation == "Battle"){
        Battle();
    } else if (currentLocation == "Store"){
        store();
    } else if (currentLocation == "Bar"){
        bar();
    } else if (currentLocation == "Maze"){
        maze();
    } else if (currentLocation == "MainMenu"){
        mainMenu();
    } else if (currentLocation == "Map"){
        map();
    }
}

void Game::town(){
    system("clear");
    if(Town){
        std::cout << "Oh wow this place is..." << std::endl;
        std::cout << "Wait I forgot..." << std::endl;
        std::cout << "Im blind" << std::endl;
        std::cout << "......" << std::endl;
        dialogContinue();
        Town = false;
    }
    std::cout << "Where do you want to go now ?" << std::endl;
    std::cout << "Please choose : " << std::endl;
    std::cout << "1. Store" << std::endl;
    std::cout << "2. Bar" << std::endl;
    std::cout << "3. Quit" << std::endl;
    std::cout << "Choice : ";
    std::cin >> choice;
    switch(choice){
        case 1:
        {
            store();
        }
            break;
        case 2:
        {
            bar();
        }
            break;
        case 3:
        {
            map();
        }
            break;
        default:
        {
            wrongInput();
        }
            break;
    }
}

void Game::bar(){
    system("clear");
    std::cout << BOLDWHITE << "*Loud people noises*" << RESET << std::endl;
    std::cout << "===========================" << std::endl;
    std::cout << "What would you like to do ?" << std::endl;
    std::cout << "1. Go to bartender" << std::endl;
    std::cout << "2. Talk to that one person on the back of the room" << std::endl;
    std::cout << "3. Go back out" << std::endl;
    std::cout << "===========================" << std::endl;
    currentLocation = "Bar";
    std::cout << "Choice : ";
    std::cin >> choice;
    switch(choice){
        case 1:
        {
            bartender();
        }
            break;
        case 2:
        {
            thatOneCreepyGuyInTheCorner();
        }
            break;
        case 3:
        {
            town();
        }
            break;
        default:
        {
            wrongInput();
        }
            break;
    }
    
}

void Game::bartender(){
    system("clear");
    std::cout << "Do you want to drink apple juice?" << std::endl;
    std::cout << "Its only " << YELLOW << "20 Gold" << RESET << std::endl;
    std::cout << "===========================" << std::endl;
    std::cout << "1. Yes" << std::endl;
    std::cout << "2. No" << std::endl;
    std::cin >> choice;
    switch(choice){
        case 1:
        {
            moneyChecker();
            std::cout << "This is totally an apple juice" << std::endl;
            std::cout << "You recieve " << BOLDRED << "5 damage" << std::endl;
            p.setDamaged(5);
            p.removeGold(20);
            dialogContinue();
            goTo();
        }
            break;
        case 2:
        {
            std::cout << "So what are you doing here ?" << BOLDRED <<  "scram!" << RESET << std::endl;
            dialogContinue();
            goTo();
        }
            break;
        default:
        {
            wrongInput();
        }
            break;
    }
}

void Game::thatOneCreepyGuyInTheCorner(){
    if(!epicNews){
        std::cout << "Hey psst" << std::endl;
        dialogContinue();
        std::cout << "You look fresh..." << std::endl;
        dialogContinue();
        std::cout << "Ill tell you a secret how to get money!" << std::endl;
        std::cout << "Its just the south from here go there" << std::endl;
        std::cout << "but beware...." << std::endl;
        dialogContinue();
        std::cout << BOLDCYAN << "You can now go to Arena" << RESET << std::endl;
        dialogContinue();
        arenaUnlocked = true;
        epicNews = true;
    } else {
        std::cout << "Well what are you still doing here go there and get some guap" << std::endl;
    }
    dialogContinue();
    goTo();
}

void Game::store(){
    system("clear");
    if(!Store){
        std::cout << "Welcome to the store!" << std::endl;
        std::cout << "I never see you before? ...." << std::endl;
        std::cout << "Are you tha-" << std::endl;
        dialogContinue();
        std::cout << "Well nevermind if i put a dialog here the code will be way longer that it should be" << std::endl;
        dialogContinue();
        Store = true;
    }
    currentLocation = "Store";
    std::cout << "===========================" << std::endl;
    std::cout << "What would you like to do ?" << std::endl;
    std::cout << "1. Buy" << std::endl;
    std::cout << "2. Sell" << std::endl;
    std::cout << "3. Nevermind" << std::endl;
    std::cout << "===========================" << std::endl;
    std::cout << "Choice : ";
    std::cin >> choice;
    switch(choice){
        case 1:
        {
            storeBuyMenu();
        }
            break;
        case 2:
        {
            storeSellMenu();
        }
            break;
        case 3:
        {
            std::cout << "Come again!" << std::endl;
            dialogContinue();
            town();
        }
            break;
        default:
        {
            wrongInput();
        }
            break;
    }
}

void Game::storeSellMenu(){
    for(int i = 0; i < length_of_Inventory; i++){
        std::cout << i + 1 << ". " << playerInventory[i].getName() << std::endl;
    }
    std::cout << "============================" << std::endl;
    std::cout << "Your Gold = " << YELLOW << p.getGold() << " Gold" << RESET << std::endl;
    std::cout << "Which Item you want to sell?" << std::endl;
    std::cout << "Choice : ";
    std::cin >> choice;
    choice -= 1;
    if(playerInventory[choice].getName() != emptySlot.getName()){
        tempSellChoice = choice;
        std::cout << "Are you sure u want to sell " << playerInventory[choice].getName() << " for " << YELLOW <<  playerInventory[choice].getValue() << " Gold?" << RESET << std::endl;
        std::cout << "1. Yes" << std::endl;
        std::cout << "2. No" << std::endl;
        std::cin >> choice;
        if(choice == 1){
            std::cout << "You recieve " << YELLOW <<  playerInventory[tempSellChoice].getValue() << RESET << " Gold" << std::endl;
            p.plusGold(playerInventory[tempSellChoice].getValue());
            playerInventory[tempSellChoice] = emptySlot;
        } else if (choice == 2){
            std::cout << "Well made up your mind already" << std::endl;
            goTo();
        }
    } else {
        std::cout << "You ok there bud?, cuz you know... you ain't holding an item" << std::endl;
    }
    goTo();
}
void Game::moneyChecker(){
    if(p.getGold() < Cost){
        std::cout << "You dont have enough money you dummy" << std::endl;
        dialogContinue();
        goTo();
    }
}

void Game::storeBuyMenu(){
    std::cout << "1. Lesser Potion || Cost : " << YELLOW << lesserPotion.getValue() * costToBuy << RESET <<  std::endl;
    std::cout << "2. Steel Sword || Cost : " << YELLOW << steelSword.getValue() * costToBuy << RESET <<  std::endl;
    std::cout << "3. Carrot || Cost : " << YELLOW << carrot.getValue() * costToBuy << RESET <<  std::endl;
    std::cout << "4. Leather Armor || Cost : " << YELLOW << leatherArmor.getValue() * costToBuy << RESET <<  std::endl;
    std::cout << "5. Iron Armor || Cost : " << YELLOW << ironArmor.getValue() * costToBuy << RESET <<  std::endl;
    std::cout << "============================" << std::endl;
    std::cout << "Your Gold = " << YELLOW << p.getGold() << " Gold" << RESET << std::endl;
    std::cout << "Which one you want to buy? : ";
    std::cin >> choice;
    if(choice == 1){
        Cost = lesserPotion.getValue() * costToBuy;
    } else if(choice == 2){
        Cost = steelSword.getValue() * costToBuy;
    } else if(choice == 3){
        Cost = carrot.getValue() * costToBuy;
    } else if(choice == 4){
        Cost = leatherArmor.getValue() * costToBuy;
    } else if(choice == 5){
        Cost = ironArmor.getValue() * costToBuy;
    }
    dialogContinue();
    switch(choice){
        case 1:
        {
            moneyChecker();
            inventoryChecker();
            if(inventoryEmptySlot < 0){
                std::cout << "I think your inventory is full..." << std::endl;
            } else {
                p.removeGold(Cost);
                playerInventory[inventoryEmptySlot] = lesserPotion;
            }
            goTo();
        }
            break;
        case 2:
        {
            moneyChecker();
            inventoryChecker();
            if(inventoryEmptySlot < 0){
                std::cout << "I think your inventory is full..." << std::endl;
            } else {
                p.removeGold(Cost);
                playerInventory[inventoryEmptySlot] = steelSword;
            }
            goTo();
        }
            break;
        case 3:
        {
            moneyChecker();
            inventoryChecker();
            if(inventoryEmptySlot < 0){
                std::cout << "I think your inventory is full..." << std::endl;
            } else {
                p.removeGold(Cost);
                playerInventory[inventoryEmptySlot] = carrot;
            }
            goTo();
        }
            break;
        case 4:
        {
            moneyChecker();
            inventoryChecker();
            if(inventoryEmptySlot < 0){
                std::cout << "I think your inventory is full..." << std::endl;
            } else {
                p.removeGold(Cost);
                playerInventory[inventoryEmptySlot] = leatherArmor;
            }
            goTo();
        }
            break;
        case 5:
        {
            moneyChecker();
            inventoryChecker();
            if(inventoryEmptySlot < 0){
                std::cout << "I think your inventory is full..." << std::endl;
            } else {
                p.removeGold(Cost);
                playerInventory[inventoryEmptySlot] = ironArmor;
            }
            goTo();
        }
            break;
        case 6:
        {
            goTo();
        }
            break;
        default:
        {
            wrongInput();
        }
            break;
    }
}

void Game::map(){
    system("clear");
    currentLocation = "Map";
    std::cout << "Where do you want to go ?" << std::endl;
    std::cout << "1. Town" << std::endl;
    if(arenaUnlocked){
        std::cout << "2. Arena" << std::endl;
    } else if (!arenaUnlocked){
        std::cout << "2. ?????" << std::endl;
    }
    if(mazeUnlocked){
        std::cout << "3. Maze" << std::endl;
    } else if (!mazeUnlocked) {
        std::cout << "3. ?????" << std::endl;
    }
    std::cout << "4. Home" << std::endl;
    std::cout << "Choice : ";
    std::cin >> choice;
    
    switch (choice) {
        case 1:
        {
            town();
        }
            break;
        case 2:
        {
            if(arenaUnlocked){
                arena();
            } else if(!arenaUnlocked){
                std::cout << "You dummy, you don't know the place yet" << std::endl;
                dialogContinue();
                goTo();
            }
        }
            break;
        case 3:
        {
            if(mazeUnlocked){
                maze();
            } else if(!mazeUnlocked){
                std::cout << "You dummy, you don't know the place yet" << std::endl;
                dialogContinue();
                goTo();
            }
        }
            break;
        case 4:
        {
            homeMenu();
        }
            break;
        default:
        {
            wrongInput();
        }
            break;
    }
}

void Game::maze(){
    srand((unsigned)time(NULL));
    fTM.setInsideMaze(true);
    mazePicker = rand() % 46;
    if (mazePicker < 15){
        fTM.mazeMapOne();
    }else if (mazePicker > 16 && mazePicker < 30){
        fTM.mazeMapTwo();
    }else if (mazePicker > 31 && mazePicker < 45){
        fTM.mazeMapThree();
    }
    chanceDrop = rand() % 20;
    if(chanceDrop < 2){
        inventoryChecker();
        if(inventoryEmptySlot < 0){
            std::cout << "... YOU HAD THE CHANCE TO GET THE LEGENDARY SWORD! ..." << std::endl;
        } else {
            std::cout << "You got " << BOLDCYAN << legendarySword.getName() << RESET << std::endl;
            playerInventory[inventoryEmptySlot] = legendarySword;
        }
    } else if (chanceDrop > 10 && chanceDrop < 11){
        inventoryChecker();
        if(inventoryEmptySlot < 0){
            std::cout << "... YOU HAD THE CHANCE TO GET THE LEGENDARY ARMOR! ..." << std::endl;
        } else {
            std::cout << "You got " << BOLDCYAN << sacredBeast.getName() << RESET << std::endl;
            playerInventory[inventoryEmptySlot] = sacredBeast;
        }
    } else {
        std::cout << "Better luck next time" << std::endl;
    }
    dialogContinue();
    if(fTM.getYouDidMinMove()){
        moneyDrop = rand() % 100;
        std::cout << "As I promise here are the reward " << std::endl;
        std::cout << "You got " << YELLOW << moneyDrop << RESET << " Gold" << std::endl;
        p.plusGold(moneyDrop);
        dialogContinue();
    }
    map();
}

void Game::arena(){
    battleLocation = "Arena";
    std::cout << "Hello welcome to the Arena, which package do you want to choose ?" << std::endl;
    std::cout << "Please choose : " << std::endl;
    std::cout << "1. 1 Battle (Reward : 20 Gold)" << std::endl;
    std::cout << "2. 3 Battle (Reward : 75 Gold)" << std::endl;
    std::cout << "3. 5 Battle (Reward : 150 Gold)" << std::endl;
    std::cout << "4. Go back" << std::endl;
    std::cout << "Choice : ";
    std::cin >> choice;
    if(choice == 1){
        reward = 20;
    } else if (choice == 2){
        reward = 75;
    } else if (choice == 3){
        reward = 150;
    }
    switch(choice){
        case 1:
        {
            Battle();
        }
            break;
        case 2:
        {
            Battle();
        }
            break;
        case 3:
        {
            Battle();
        }
            break;
        case 4:
        {
            map();
        }
            break;
        default:
        {
            wrongInput();
        }
            break;
    }
}

void Game::startInventory(){
    for (int i = 0; i < length_of_Inventory; i++){
        playerInventory[i] = emptySlot;
    }
}

void Game::inventoryChecker(){
    for (int i = 0; i < length_of_Inventory; i++){
        if (playerInventory[i].getName() == emptySlot.getName()){
            inventoryEmptySlot = i;
        }
    }
    if(inventoryEmptySlot < 0){
        std::cout << "You don't have any slot" << std::endl;
        goTo();
    }
}

void Game::Inventory(){
    for(int i = 0; i < length_of_Inventory; i++){
        std::cout << i + 1 << ". " << playerInventory[i].getName() << std::endl;
    }
    std::cout << "What do you want to do?" << std::endl;
    std::cout << "1. Use Item" << std::endl;
    std::cout << "2. Remove Item" << std::endl;
    std::cout << "3. Sort Inventory" << std::endl;
    std::cout << "4. Quit Invevntory" << std::endl;
    std::cout << "Choice : ";
    std::cin >> choice;
    switch(choice){
        case 1:
        {
            std::cout << "What Item Number item you want to use ?" << std::endl;
            std::cout << "Choice : ";
            std::cin >> choice;
            choice -= 1;
            useItem(choice);
        }
            break;
        case 2:
        {
            std::cout << "What Item Number item you want to remove ?" << std::endl;
            std::cout << "Choice : ";
            std::cin >> choice;
            choice -= 1;
            playerInventory[choice] = emptySlot;
            system("clear");
            Inventory();
        }
            break;
        case 3:
        {
            sortInventory();
            goTo();
        }
            break;
        case 4:
        {
            goTo();
        }
            break;
        default:
        {
            wrongInput();
        }
            break;
    }
}

void Game::useItem(int itemSlot){
    for (int i = 0; i < sizeof(weapons)/sizeof(weapons[0]); i++){
        if (playerInventory[itemSlot].getName() == weapons[i].getName()){
            anotherTemp = weapons[i];
        } else if (playerInventory[itemSlot].getName() == eatMe[i].getName()){
            p.useItem(eatMe[i]);
            playerInventory[itemSlot] = emptySlot;
        } else if (playerInventory[itemSlot].getName() == armors[i].getName()){
            anotherTempar = armors[i];
        }
    }
    tempWeapon = p.weapon_Equipped;
    tempArmor = p.armor_Equipped;
    p.equipWeapon(anotherTemp);
    p.equipArmor(anotherTempar);
    if(playerInventory[itemSlot].getName() == tempWeapon.getName()){
        playerInventory[itemSlot] = emptySlot;
    } else if(playerInventory[itemSlot].getName() != tempArmor.getName() && playerInventory[itemSlot].getName() != p.armor_Equipped.getName()){
        playerInventory[itemSlot] = tempWeapon;
    }
    if(playerInventory[itemSlot].getName() == tempArmor.getName()){
        playerInventory[itemSlot] = emptySlot;
    } else if(playerInventory[itemSlot].getName() != tempWeapon.getName() && playerInventory[itemSlot].getName() != p.weapon_Equipped.getName()){
        playerInventory[itemSlot] = tempArmor;
    }
    goTo();
}



void Game::showStats(){
    std::cout << "===========================" << std::endl;
    std::cout << "Name : " << p.getName() << std::endl;
    std::cout << "HP : " << p.getHP() << std::endl;
    std::cout << "MP : " << p.getMP() << std::endl;
    std::cout << "Attack : " << p.getAttack() << std::endl;
    std::cout << "Defense : " << p.getDefense() << std::endl;
    std::cout << "Gold : " << p.getGold() << std::endl;
    std::cout << "===========================" << std::endl;
    std::cout << "Item that currently being used" << std::endl;
    std::cout << "Weapon : " << p.weapon_Equipped.getName() << std::endl;
    std::cout << "Armor : " << p.armor_Equipped.getName() << std::endl;
    std::cout << "===========================" << std::endl;
    dialogContinue();
    goTo();
}

void Game::Battle(){
    system("clear");
    srand((unsigned)time(NULL));
    int damage = 0;
    int exDef = 0;
    int pT = 0;
    int tryExcape;
    int randIndex = rand() % sizeof(Enemy)/sizeof(Enemy[0]);
    auto enemy = Enemy[randIndex];
    currentLocation = "Battle";
    while ((p.getHP() > 0) && (enemy.getHP() > 0)){
        std::cout << "You are fighting " << enemy.getName() << std::endl;
        std::cout << "===========================" << std::endl;
        std::cout << "Your HP : " << p.getHP() << std::endl;
        std::cout << "Enemy HP : " << enemy.getHP() << std::endl;
        std::cout << "1. Attack" << std::endl;
        std::cout << "2. Defend" << std::endl;
        std::cout << "3. Stats" << std::endl;
        std::cout << "4. Inventory" << std::endl;
        std::cout << "5. Run" << std::endl;
        std::cout << "Choice : ";
        std::cin >> choice;
        dialogContinue();
        switch(choice){
            case 1:
            {
                damage = (rand() % p.getAttack()) - (rand() % enemy.getDefense());
                if(damage <= 0){
                    damage = 1;
                }
                std::cout << "Your attack deals " << damage << " damage" << std::endl;
                enemy.setDamaged(damage);
                damage = 0;
                damage = (rand() % enemy.getAttack()) - (rand() % p.getDefense());
                if(damage <= 0){
                    damage = 1;
                }
                std::cout << "You got attacked for " << damage << " damage" << std::endl;
                p.setDamaged(damage);
                damage = 0;
            }
                break;
            case 2:
            {
                exDef = (rand() % p.getDefense()) * 2;
                damage = (rand() % enemy.getAttack()) - (rand() % p.getDefense());
                pT = damage - exDef;
                if(pT <= 0){
                    pT = 0;
                    std::cout << "You blocked all of the damage" << std::endl;
                } else {
                    std::cout << "You recieve " << pT << " Damage" << std::endl;
                }
                p.setDamaged(pT);
            }
                break;
            case 3:
            {
                showStats();
            }
                break;
            case 4:
            {
                Inventory();
            }
            case 5:
            {
                if (battleLocation == "Arena"){
                    std::cout << BOLDRED << "You can't run from the arena" << RESET << std::endl;
                } else if (battleLocation == "Maze"){
                    std::cout << BOLDWHITE << "Are you sure you want to run you might lose progress" << RESET << std::endl;
                    std::cout << "1. Yes" << std::endl;
                    std::cout << "2. No" << std::endl;
                    std::cin >> choice;
                    switch(choice){
                        case 1:
                        {
                            tryExcape = rand() % 11;
                            if(tryExcape <= 0){
                                std::cout << "You try to flee but you failed" << std::endl;
                            } else {
                                goTo();
                            }
                        }
                            break;
                        case 2:
                        {
                            continue;
                        }
                            break;
                    }
                } else {
                    tryExcape = rand() % 11;
                    if(tryExcape <= 0){
                        std::cout << "You try to flee but you failed" << std::endl;
                    } else {
                        goTo();
                    }
                }
            }
                break;
            default:
            {
                wrongInput();
            }
                break;
        }
    }
    if (enemy.getHP() <= 0){
        std::cout << "===========================" << std::endl;
        std::cout << "I did it?!" << std::endl;
        std::cout << "ᕦ( ͡° ͜ʖ ͡°)ᕤ " << BOLDWHITE << "Stronk" << RESET << std::endl;
        itemDrop();
        p.plusGold(enemy.getGold());
        std::cout << "You got " << YELLOW << enemy.getGold() << " Gold" << RESET << std::endl;
        std::cout << "===========================" << std::endl;
        dialogContinue();
        if (battleLocation == "Arena"){
            if(reward == 20){
                std::cout <<  "Congratulation you get " << YELLOW << reward << " Gold" << RESET << " From winning the arena" << std::endl;
                p.plusGold(reward);
                dialogContinue();
                arena();
            } else if(reward == 75){
                battleCount++;
                if (battleCount < 3){
                    Battle();
                }
                else if(battleCount >= 3){
                    std::cout <<  "Congratulation you get " << YELLOW << reward << " Gold" << RESET << " From winning the arena" << std::endl;
                    p.plusGold(reward);
                    dialogContinue();
                    battleCount = 0;
                    arena();
                }
            } else if(reward == 150){
                battleCount++;
                if (battleCount < 5){
                    Battle();
                } else if(battleCount >= 5) {
                    std::cout <<  "Congratulation you get " << YELLOW << reward << " Gold" << RESET << " From winning the arena" << std::endl;
                    if(!knowMaze){
                        std::cout << "Hey you!" << std::endl;
                        dialogContinue();
                        std::cout << "I think you deserve something" << std::endl;
                        std::cout << "I just opened the maze, you could go there now " << std::endl;
                        std::cout << BOLDCYAN << "You can now travel to maze" << RESET << std::endl;
                        dialogContinue();
                    }
                    p.plusGold(reward);
                    dialogContinue();
                    battleCount = 0;
                    mazeUnlocked = true;
                    arena();
                }
            }
        } else if (battleLocation == "Maze"){
            goTo();
        }
    }
        else if (enemy.getHP() <= 0){
            if (p.getHP() <0){
                std::cout << MAGENTA << " ff---------- " <<  RESET << std::endl;
                std::cout << BLACK << " ヽ(ﾟДﾟ)ﾉ " << RESET << std::endl;
                std::cout << BOLDRED <<"Game Over" << RESET << std::endl;
                system("read");
                setGameRunning(false);
                exit(0);
            }
        } else {
            std::cout << BOLDRED << "Game Over" << RESET << std::endl;
            system("read");
            setGameRunning(false);
            exit(0);
        }
}

void Game::itemDrop(){
    srand((unsigned)time(NULL));
    chanceDrop = rand() % 11;
    itemDropChance = rand() % sizeof(dropItem)/sizeof(dropItem[0]);
    inventoryChecker();
    if(inventoryEmptySlot < 0){
        std::cout << "I think your inventory is full..." << std::endl;
    } else {
        if(chanceDrop <= 5){
            auto drop = dropItem;
            playerInventory[inventoryEmptySlot] = drop[itemDropChance];
        } else if (chanceDrop > 5 && chanceDrop <= 10){
            auto drop = eatMe;
            playerInventory[inventoryEmptySlot] = drop[itemDropChance];
        }
        std::cout << "You got " << GREEN << playerInventory[inventoryEmptySlot].getName() << RESET << std::endl;
    }
    
    
    
}

void Game::setGameRunning(bool game_Running){
    this -> game_Running = game_Running;
}

void Game::setCurrentLocation(std::string cL){
    this -> currentLocation = cL;
}

void Game::setBattleLocation(std::string bL){
    this -> battleLocation = bL;
}
bool Game::getGameRunning(){
    return game_Running;
}

void Game::wrongInput(){
    std::cout << "Enter the right thing" << std::endl;
    dialogContinue();
    goTo();
}
