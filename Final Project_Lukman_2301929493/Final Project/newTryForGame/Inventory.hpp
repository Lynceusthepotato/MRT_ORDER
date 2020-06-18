//
//  Inventory.hpp
//  newTryForGame
//
//  Created by Lukman Hanafi  on 25/05/20.
//  Copyright © 2020 Lukman Hanafi . All rights reserved.
//

#ifndef Inventory_hpp
#define Inventory_hpp

#include <stdio.h>
#include <string>

class Item {
    
public:
    Item();
    Item(std::string Name, int Value);
    void setName(std::string Name);
    std::string getName();
    void setValue(int Value);
    int getValue();

    
protected:
    
    std::string Name;
    int Value;
    
};

class Usable : public Item {
    
public:
    
    Usable();
    Usable(std::string Name, int Plus, int Value);
    void setPlus(int Plus);
    int getPlus();
    
private:
    
    int Plus;
    
};


class Weapon : public Item {
    
public:
    
    Weapon();
    Weapon(std::string Name, int Attack, int Value);
    void setAttack(int Attack);
    int getAttack();
    
private:
    
    int Attack;
    
};


class Armor : public Item {
    
public:
    
    Armor();
    Armor(std::string Name, int Defense, int Special, int Value);
    void setDefense(int Defense);
    int getDefense();
    void setSpecial(int Special);
    int getSpecial();
    
private:
    
    int Defense;
    int Special;
    
    
};
#endif /* Inventory_hpp */
