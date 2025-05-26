/*!
 * @file battle.cpp
 * @description Implements the functions from battle.h
 * @author Pedro V. B. Pereira
 * @date   May 25th, 2025.
*/

#include "battle.h"
#include <cstdlib>
#include <random>
#include <iostream>
#include <unistd.h>

void loglog(std::string output, bool newline) {
    if (newline) std::cout << ">>> "<< output << '\n';
    else std::cout << output;
}

void Warrior::reset_defense() {
    this->block = UNSET;
}

void Warrior::attack(Warrior &target) {
    int roll = RNG(1, 20);

    /// Three possibilities here: A Miss, a hit, or a double damage hit.
    if ( roll == NAT_FAIL ) {
        loglog(this->name + " missed " + target.name, true);
    }
    else {
        int damage = RNG(1, 10)+(this->stat_stats[STRENGTH] * 2);

        if ( roll == NAT_CRIT ) {
            damage*=2;
            if ( target.block != FULL ) loglog("CRITICAL HIT: ", false);
        }

        /// If the target was blocking, depending on their blocking status the damage (and message) will be different.
        switch (target.block) {
            case UNSET: /// Not blocking
                loglog(this->name + " attacks " + target.name + " → " + std::to_string(damage) + " damage", true);
                break ;;
            case NONE: /// Failed blocking
                loglog(this->name + " attacks " + target.name + ", who tried to block and failed → " + std::to_string(damage) + " damage", true);
                break ;;
            case PARTIAL: /// Succesful blocking
                damage/=2;
                loglog(this->name + " attacks " + target.name + ", who partially blocked the attack → " + std::to_string(damage) + " damage", true);
                break ;;
            case FULL: /// VERY Succesful blocking
                damage = 0;
                loglog(this->name + " attacks " + target.name + ", but it was blocked → " + std::to_string(damage) + " damage", true);
                break ;;
        }
        target.reset_defense();
        target.health -= damage;
    }
}

void Warrior::defend() {
    /// Leave it to somewhat random chance whether blocking works (Defense stat helps).
    short bias = this->stat_stats[DEFENSE];
    int roll = RNG(1, 20) + (bias);
    def_stat outcome;

    if ( roll == NAT_FAIL - bias ) { outcome = NONE; }
    else if (roll == NAT_CRIT - bias ) { outcome = FULL; }
    else { outcome = PARTIAL; }

    this->block = outcome;

    loglog( this->name + " enters defense stance.", true);
}

void Warrior::heal() {
    /// Leave it to chance how much healing will heal (healing stat will help, though).
    int roll = RNG(1, 20);
    this-> health += roll + (this->stat_stats[HEALING] * 2);

    /// Check whether the health added exceeds max health.
    stat hp = this->health;
    stat max_hp = this->max_health;

    if ( hp > max_hp) this->health = max_hp;

    loglog( this->name + " heals " + std::to_string(roll) + " health", true);

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

void Arena::combat() {
    auto warriors = this->list_of_warriors;

    /// Function to check if the warrior died from the attack.
    auto check_death = [] (Warrior a) -> bool {
        if (a.health < 0) return true;
        return false;
    };

    /// Make Attacking more common than Healing or Defending.
    auto rand_action = [] () -> action {
        int rand = RNG(1, 3);
        if ( rand <= 2 ) return ATTACK;
        else {
            rand = RNG(1, 2);
            if ( rand == 1 ) return DEFEND;
            else return HEAL;
        }
    };

    while ( warriors[PONE]->health > 0 || warriors[PTWO]->health > 0 ) {

        /// Decide which player goes first.
        player first = (player)RNG(PONE, PTWO);
        short last;

        if ( first == PONE ) last = PTWO;
        else last = PONE;

        warriors[first]->afflict(rand_action(), *warriors[last]);
        if (check_death(*warriors[last])) {
            std::cout << warriors[first]->name;
            break;
        }

        warriors[last]->afflict(rand_action(), *warriors[first]);
        if (check_death(*warriors[first])) {
            std::cout << warriors[last]->name;
            break;
        }

        this->scoreboard();
        std::cout << ">>> continue... <<<\n";
        std::cin.get();

        /// Wait 4 seconds before continuing.
        // usleep(4000000);
    }
    std::cout << " is declared the winner!" << '\n';
    this->scoreboard();
}

void Arena::scoreboard() {
    /// Even formatting of strings using spaces
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
    
    /// The attack can bring health to negative, but that looks ugly to display.
    auto hp = [] ( Warrior *a) -> std::string {
        if (a->health < 0) return "0";
        else return std::to_string(a->health);
    };

    auto life = [] ( Warrior *a) -> std::string {
        if (a->health < 0) return "DEAD";
        else return "ALIVE";
    };

    std::cout << " -----------------------------------\n";
    for (size_t i{0}; i < list_of_warriors.size(); ++i) {
        Warrior *player = this->list_of_warriors[i];
        std::cout
            << "| "
            << str_format(player->name, HUD_NAME)
            << " | "
            << str_format(hp(player), HUD_HEALTH)
            << " | "
            << str_format(life(player), HUD_LIFE_STATUS)
            << " |"
            << '\n';
    }
    std::cout << " -----------------------------------\n\n";
}

int RNG(int min, int max) {
    std::random_device dev;
    std::mt19937 random(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(min,max);
    return dist(random);
}
