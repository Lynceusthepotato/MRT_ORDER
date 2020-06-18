//
//  Player.cpp
//  newTryForGame
//
//  Created by Lukman Hanafi  on 25/05/20.
//  Copyright © 2020 Lukman Hanafi . All rights reserved.
//

#include "Player.hpp"

Player :: Player(){
    
    Name = "Bruh you forget to fill up the name";
    HP = 75;
    MaxHP = HP;
    MP = 20;
    MaxMP = MP;
    Attack = 5;
    Defense = 2;
    Gold = 0;
    
}

Player :: Player(std::string Name, int HP, int MP, int Attack, int Defense, int Gold){
    
    this -> Name = Name;
    this -> HP = HP;
    this -> MaxHP = HP;
    this -> MP = MP;
    this -> MaxMP = MP;
    this -> Attack = Attack;
    this -> Defense = Defense;
    this -> Gold = Gold;
    
}

void Player::setName(std::string Name){
    this -> Name = Name;
}

std::string Player::getName(){
    return Name;
}

void Player::setHP(int HP){
    this -> HP = HP;
}

int Player::getHP(){
    return HP;
}

void Player::setMP(int MP){
    this -> MP = MP;
}

int Player::getMP(){
    return MP;
}

void Player::setAttack(int Attack){
    this -> Attack = Attack;
}

int Player::getAttack(){
    return Attack;
}

void Player::setDefense(int Defense){
    this -> Defense = Defense;
}

int Player::getDefense(){
    return Defense;
}

void Player::setGold(int Gold){
    this -> Gold = Gold;
}

int Player::getGold(){
    return Gold;
}

void Player::setDamaged(int dmg){
    this -> HP -= dmg;
}

void Player::plusGold(int Gold){
    this -> Gold += Gold;
}

void Player::removeGold(int Gold){
    this -> Gold -= Gold;
}

void Player::equipWeapon(Weapon weapon){
    unequipWeapon();
    weapon_Equipped = weapon;
    this -> Attack += weapon.getAttack();
}

void Player::unequipWeapon(){
    this -> Attack -= weapon_Equipped.getAttack();
    weapon_Equipped = Weapon("",0,0);
}

void Player::useItem(Usable consume){
    this -> HP += consume.getPlus();
    if (this -> HP > MaxHP){
        this -> HP = MaxHP;
    }
}

void Player::plusHP(int HP){
    this -> HP += HP;
    if (this -> HP > MaxHP){
        this -> HP = MaxHP;
    }
}

void Player::equipArmor(Armor armor){
    unequipArmor();
    armor_Equipped = armor;
    this -> Defense += armor.getDefense();
}

void Player::unequipArmor(){
    this -> Defense -= armor_Equipped.getDefense();
    armor_Equipped = Armor("",0,0,0);
}
