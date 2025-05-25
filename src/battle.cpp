#include "battle.h"
#include <random>
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
            if ( target.atk_debuff != FULL ) loglog("CRITICAL HIT: ", 0);
        }

        switch (target.atk_debuff) {
            case UNSET:
                loglog(this->name + " attacks " + target.name + " → " + std::to_string(damage) + " damage", 1);
                break ;;
            case FAIL:
                loglog(this->name + " attacks " + target.name + ", who tried to block and failed → " + std::to_string(damage) + " damage", 1);
                break ;;
            case PARTIAL:
                damage/=2;
                loglog(this->name + " attacks " + target.name + ", who partially blocked the attack → " + std::to_string(damage) + " damage", 1);
                break ;;
            case FULL:
                damage = 0;
                loglog(this->name + " attacks " + target.name + ", but it was blocked → " + std::to_string(damage) + " damage", 1);
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
    loglog( this->name + " enters defense stance", 1);
}

void Warrior::heal() {
    int roll = RNG(1, 20);
    this-> health += roll;

    stat hp = this->health;
    stat max_hp = this->max_health;

    if ( hp > max_hp) this->health = max_hp;

    loglog( this->name + " heals " + std::to_string(roll) + " health", 1);

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
            heal();
            break ;;
    }
}

void Arena::combat(){
    Warrior* a = this->list_of_warriors[PONE];
    Warrior* b = this->list_of_warriors[PTWO];

    auto check_death = [] (Warrior a) -> bool {
        if (a.health < 0) return true;
        return false;
    };

    auto rand_action = [] () -> action {
        int rand = RNG(1, 3);
        if ( rand <= 2 ) return ATTACK;
        else {
            rand = RNG(1, 2);
            if ( rand == 1 ) return DEFEND;
            else return HEAL;
        }
    };

    while ( a->health > 0 || b->health > 0 ) {

        a->afflict(rand_action(), *b);
        if (check_death(*b)) {
            std::cout << a->name;
            break;
        }

        b->afflict(rand_action(), *a);
        if (check_death(*a)) {
            std::cout << b->name;
            break;
        }

        usleep(1000000);
        this->scoreboard();

        a->reset_debuff();
        b->reset_debuff();
        usleep(2000000);
    }
    std::cout << " is declared the winner!" << '\n';
    this->scoreboard();
}

void Arena::scoreboard() {
    auto str_format = [] ( std::string content, column col ) -> std::string {
        std::string spaces{content};
        switch (col) {
            case (HUD_NAME):
                while ( spaces.size() != 15 ) {
                    spaces.push_back(' ');
                }
                break ;;
            case (HUD_HEALTH):
                while ( spaces.size() != 4 ) {
                    spaces.push_back(' ');
                }
                break ;;
            case (HUD_LIFE_STATUS):
                while ( spaces.size() != 8 ) {
                    spaces.push_back(' ');
                }
                break ;;
        };
        return spaces;
    };
    auto hp = [] ( Warrior *a) -> std::string {
        if (a->health < 0) return "0";
        else return std::to_string(a->health);
    };
    auto life = [] ( Warrior *a) -> std::string {
        if (a->health < 0) return "DEAD";
        else return "ALIVE";
    };

    for (size_t i{0}; i < list_of_warriors.size(); ++i) {
        Warrior *player = this->list_of_warriors[i];
        std::cout
            << str_format(player->name, HUD_NAME)
            << " | "
            << str_format(hp(player), HUD_HEALTH)
            << " | "
            << str_format(life(player), HUD_LIFE_STATUS)
            << '\n';
    }
}

int RNG(int min, int max){
    std::random_device dev;
    std::mt19937 random(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(min,max); // distribution in range [1, 6]
    return dist(random);
}
