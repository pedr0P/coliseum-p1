#include "battle.h"

void Warrior::reset_debuff() {
    this->atk_debuff = 0;
}

void Warrior::afflict(){}

void Arena::combat( Warrior a, Warrior b ){}

int Dice::RNG(int min, int max){
    return 0;
}

int Dice::WRNG(int min, int max, int bias){
    return 0;
}
