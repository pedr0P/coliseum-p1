#include <iostream>
#include "battle.cpp"

int main(int argc, char* argv[]) {

    Warrior a;
    a.name = "A";
    a.stat_stats = { 100, 100, 25};

    Warrior b;
    b.name = "B";
    b.stat_stats = { 25, 50, 100 };

    Arena coliseum;
    coliseum.list_of_warriors = { a, b };
    coliseum.combat();
}
