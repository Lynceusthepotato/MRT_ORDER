//
//  Inventory.cpp
//  newTryForGame
//
//  Created by Lukman Hanafi  on 25/05/20.
//  Copyright © 2020 Lukman Hanafi . All rights reserved.
//

#include "Inventory.hpp"

Item :: Item(){
    this -> Name = "";
    this -> Value = 0;
}

Item :: Item(std::string Name, int Value){
    this -> Name = Name;
    this -> Value = Value;
}

void Item:: setName(std::string Name){
    this -> Name = Name;
}

std::string Item:: getName(){
    return Name;
}

void Item :: setValue(int Value){
    this -> Value = Value;
}

int Item:: getValue(){
    return Value;
}


Usable :: Usable(){
    this -> Name = "";
    this -> Plus = 0;
    this -> Value = 0;
}

Usable :: Usable(std::string Name, int Plus, int Value){
    this -> Plus = Plus;
    this -> Name = Name;
    this -> Value = Value;
}

void Usable::setPlus(int Plus){
    this -> Plus = Plus;
}

int Usable::getPlus(){
    return Plus;
}

Weapon :: Weapon(){
    this -> Attack = 0;
    this -> Name = "";
    this -> Value = 0;
}
Weapon :: Weapon(std::string Name, int Attack, int Value){
    this -> Attack = Attack;
    this -> Name = Name;
    this -> Value = Value;
}

void Weapon::setAttack(int Attack){
    this -> Attack = Attack;
}

int Weapon::getAttack(){
    return Attack;
}
Armor :: Armor(){
    this -> Defense = 0;
    this -> Special = 0;
    this -> Name = "";
    this -> Value = 0;
}
Armor :: Armor(std::string Name, int Defense, int Special, int Value){
    this -> Defense = Defense;
    this -> Special = Special;
    this -> Name = Name;
    this -> Value = Value;
}

void Armor::setDefense(int Defense){
    this -> Defense = Defense;
}

int Armor::getDefense(){
    return Defense;
}

void Armor::setSpecial(int Special){
    this -> Special = Special;
}

int Armor::getSpecial(){
    return Special;
}
