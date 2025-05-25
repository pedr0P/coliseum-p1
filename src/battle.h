#include <array>
#include <iostream>
#include <list>
#include <string>
#include <utility>

/// Integer type for tracking stats.
typedef unsigned stat;

//== Enumerations
enum action {
    ATTACK,
    DEFEND,
    HEAL
};

enum stat_fields {
    STRENGTH,
    DEFENSE,
    HEALTH
};

enum atk_stat {
    MISS,
    HIT,
    CRIT
};
enum def_stat {
    UNSET,
    FAIL,
    PARTIAL,
    FULL
};

enum player {
    PONE,
    PTWO
};

class Warrior {
public:
    std::string name;

    def_stat atk_debuff = UNSET;

    stat max_health{100};
    signed health{100};

    /// Static stats - Strength, Defense, and Healing (Out of 5)
    std::array<stat, 3> stat_stats;


    void afflict(action choice, Warrior &target);
    void attack(Warrior &target);
    void defend();
    void heal();

    void reset_debuff();
    void show_stats();
};

class Arena {
public:
    std::array<Warrior*, 2> list_of_warriors;

    void scoreboard();
    void combat();
};


void loglog(std::string output, short newline);

int RNG(int min, int max);
