#include "battle.cpp"

int main(int argc, char* argv[]) {

    Warrior a;
    a.name = "Superman";
    a.health = 100;
    a.stat_stats = { 5, 4, 1};

    Warrior b;
    b.name = "Batman";
    b.health = 100;
    b.stat_stats = { 3, 2, 5 };

    Arena coliseum;
    coliseum.list_of_warriors = { &a, &b };
    coliseum.combat();
}
