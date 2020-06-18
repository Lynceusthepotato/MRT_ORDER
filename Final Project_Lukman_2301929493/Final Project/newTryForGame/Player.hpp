//
//  Player.hpp
//  newTryForGame
//
//  Created by Lukman Hanafi  on 25/05/20.
//  Copyright © 2020 Lukman Hanafi . All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include <string>
#include "Inventory.hpp"


class Player {
    
public:
    Player();
    Player(std::string Name, int HP, int MP, int Attack, int Defense, int Gold);
    void setName(std::string Name);
    std::string getName();
    void setHP(int HP);
    int getHP();
    void setMP(int MP);
    int getMP();
    void setAttack(int Attack);
    int getAttack();
    void setDefense(int Defense);
    int getDefense();
    void setGold(int Gold);
    int getGold();
    void setDamaged(int dmg);
    void plusGold(int Gold);
    void removeGold(int Gold);
    void equipWeapon(Weapon wapon);
    void unequipWeapon();
    void equipArmor(Armor armor);
    void unequipArmor();
    void useItem(Usable consumable);
    void plusHP(int HP);
    Weapon weapon_Equipped;
    Armor armor_Equipped;

    
private:
    std::string Name;
    int HP;
    int MaxHP;
    int MP;
    int MaxMP;
    int Attack;
    int Defense;
    int Gold;
    

};

#endif /* Player_hpp */
