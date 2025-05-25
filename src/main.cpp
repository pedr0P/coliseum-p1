#include <iostream>
#include "battle.cpp"

int main(int argc, char* argv[]) {

    Warrior a;
    a.name = "A";
    a.health = 30;
    a.stat_stats = { 5, 5, 1};

    Warrior b;
    b.name = "B";
    b.health = 30;
    b.stat_stats = { 1, 2, 5 };

    Arena coliseum;
    coliseum.list_of_warriors = { &a, &b };
    coliseum.combat();
}
