#include "battle.h"
#include <iostream>
#include <string>
#include <ctime>
#include <unistd.h>

void loglog(std::string output, short newline) {
    if (newline) std::cout << output << '\n';
    else std::cout << output;
}

void Warrior::reset_debuff() { this->atk_debuff = UNSET; }

void Warrior::attack(Warrior &target) {
    int roll = RNG(1, 20);

    if ( roll == 1 ) {
        loglog(this->name + " missed " + target.name, 1);
    }
    else {
        int damage = RNG(1, 10)+(this->stat_stats[STRENGTH] * 2);
        if ( roll == 20 ) {
            damage*=2;
            if ( target.atk_debuff != FULL ) loglog("CRITICAL HIT!: ", 0);
        }

        switch (target.atk_debuff) {
            case UNSET:
                loglog(this->name + " attacked " + target.name + "! - " + std::to_string(damage), 1);
                break ;;
            case FAIL:
                // loglog(target.name + " failed to block " + this->name + "'s attack! - " + std::to_string(damage), 1);
                loglog(this->name + " attacked " + target.name + ", who tried to block and failed! - " + std::to_string(damage), 1);
                break ;;
            case PARTIAL:
                damage/=2;
                // loglog(target.name + " partially blocked " + this->name + "'s attack! - " + std::to_string(damage), 1);
                loglog(this->name + " attacked " + target.name + ", who partially block the attack! - " + std::to_string(damage), 1);
                break ;;
            case FULL:
                damage = 0;
                // loglog(target.name + " succesfully blocked " + this->name + "'s attack!", 1);
                loglog(this->name + " attacked " + target.name + ", but it was blocked! - " + std::to_string(damage), 1);
                break ;;
        }
        target.health -= damage;
    }
}
void Warrior::defend() {
    int roll = RNG(1, 20);
    def_stat outcome;
    if ( roll == 1 ) { outcome = FAIL; }
    else if (roll == 20) { outcome = FULL; }
    else { outcome = PARTIAL; }
    this->atk_debuff = outcome;
    loglog( this->name + " enters defense stance!", 1);
}
void Warrior::heal() {
    int roll = RNG(1, 20);
    this-> health += roll;

    stat hp = this->health;
    stat max_hp = this->max_health;

    if ( hp > max_hp) this->health = max_hp;

    loglog( this->name + " heals " + std::to_string(roll), 1);

}
void Warrior::afflict(action choice, Warrior &target){
    switch ( choice ) {
        case ATTACK:
            this->attack(target);
            break ;;
        case DEFEND:
            this->defend();
            break ;;
        case HEAL:
            break ;;
    }
}

void Arena::combat(){
    Warrior* a = this->list_of_warriors[PONE];
    Warrior* b = this->list_of_warriors[PTWO];

    while ( a->health > 0 || b->health > 0 ) {
        action rand;

        rand = (action)RNG(ATTACK, HEAL);
        a->afflict(rand, *b);

        usleep(500000);

        rand = (action)RNG(ATTACK, HEAL);
        b->afflict(ATTACK, *a);

        usleep(500000);

        this->scoreboard();

        a->reset_debuff();
        b->reset_debuff();
    }
}

void Arena::scoreboard() {
    auto life = [] ( Warrior *a) -> std::string {
        if (a->health == 0) return "DEAD";
        else return "ALIVE";
    };

    for (size_t i{0}; i < list_of_warriors.size(); ++i) {
        Warrior *player = this->list_of_warriors[i];
        std::cout
            << player->name
            << " | "
            << player->health
            << " | "
            << life(player)
            << '\n';
    }
}

int RNG(int min, int max){
    srand(time(NULL));
    return min + rand() % (max - min + 1);
}


