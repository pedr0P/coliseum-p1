#include <array>
#include <string>

/// Integer type for tracking stats.
typedef unsigned stat;

//== Enumerations
enum action {
    ATTACK,
    DEFEND,
    HEAL
};

enum stat_field {
    OFFENSE,
    HEALTH
};

enum player {
    PONE,
    PTWO
};

class Warrior {
public:
    std::string name;

    stat max_health{100};
    stat atk_debuff{0};

    /// Static stats - Strength, Defense and Healing (Out of 100)
    std::array<stat, 3> stat_stats;

    /// Dynamic stats - Offense and Health (Out of 100)
    std::array<stat, 2> dyn_stats;

    void afflict();
    void reset_debuff();
};

class Arena {
public:
    std::array<Warrior, 2> list_of_warriors;
    
    void combat();
};

class Dice{
public:
    /// Random Number Generator
    int  RNG(int min, int max);
    /// Weighted Random Number Generator
    int WRNG(int min, int max, int bias);
};

