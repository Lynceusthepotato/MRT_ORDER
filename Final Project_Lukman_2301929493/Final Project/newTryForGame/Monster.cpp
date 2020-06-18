//
//  Monster.cpp
//  newTryForGame
//
//  Created by Lukman Hanafi  on 26/05/20.
//  Copyright © 2020 Lukman Hanafi . All rights reserved.
//

#include "Monster.hpp"

Monster :: Monster(){
    
    Name = "im a demon";
    HP = 100;
    MaxHP = HP;
    MP = 100;
    MaxMP = MP;
    Attack = 100;
    Defense = 100;
    Gold = 100;
    
}

Monster :: Monster(std::string Name, int HP, int MP, int Attack, int Defense, int Gold){
    
    this -> Name = Name;
    this -> HP = HP;
    this -> MaxHP = HP;
    this -> MP = MP;
    this -> MaxMP = MP;
    this -> Attack = Attack;
    this -> Defense = Defense;
    this -> Gold = Gold;
    
}

void Monster::setName(std::string Name){
    this -> Name = Name;
}

std::string Monster::getName(){
    return Name;
}

void Monster::setHP(int HP){
    this -> HP = HP;
}

int Monster::getHP(){
    return HP;
}

void Monster::setMP(int MP){
    this -> MP = MP;
}

int Monster::getMP(){
    return MP;
}

void Monster::setAttack(int Attack){
    this -> Attack = Attack;
}

int Monster::getAttack(){
    return Attack;
}

void Monster::setDefense(int Defense){
    this -> Defense = Defense;
}

int Monster::getDefense(){
    return Defense;
}

void Monster::setGold(int Gold){
    this -> Gold = Gold;
}

int Monster::getGold(){
    return Gold;
}

void Monster::setDamaged(int dmg){
    this -> HP -= dmg;
}
