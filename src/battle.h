#include <array>
#include <string>

//== Enumerations
enum action {
    ATTACK,
    DEFEND,
    HEAL
};

enum stat_field {
    STRENGTH,
    DEFENSE,
    HEALING
};

enum player {
    ONE,
    TWO
};

/// Integer type for tracking stats.
typedef unsigned stat;

class Warrior {
public:
    std::string name;

    stat health;
    stat atk_debuff;

    /// Static stats - Strength, Defense and Healing
    std::array<stat, 3> stat_stats;

    /// Dynamic stats - Attack and Health
    std::array<stat, 2> dyn_stats;

    void afflict();
    void reset_debuff();
};


class Arena {
    std::array<Warrior, 2> list_of_warriors;
    
    void combat();
};

class Dice{
    /// Random Number Generator
    int  RNG(int min, int max);
    /// Weighted Random Number Generator
    int WRNG(int min, int max, int bias);
};

