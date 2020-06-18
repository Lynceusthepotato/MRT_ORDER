//
//  Monster.hpp
//  newTryForGame
//
//  Created by Lukman Hanafi  on 26/05/20.
//  Copyright © 2020 Lukman Hanafi . All rights reserved.
//

#ifndef Monster_hpp
#define Monster_hpp

#include <stdio.h>
#include <string>

class Monster {
    
public:
    Monster();
    Monster(std::string Name, int HP, int MP, int Attack, int Defense, int Gold);
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



#endif /* Monster_hpp */
