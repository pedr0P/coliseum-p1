#include "battle.cpp"

int main(int argc, char* argv[]) {

    Warrior a;
    a.name = "Superman";
    a.health = 30;
    a.stat_stats = { 5, 2, 1};

    Warrior b;
    b.name = "Batman";
    b.health = 30;
    b.stat_stats = { 5, 5, 5 };

    Arena coliseum;
    coliseum.list_of_warriors = { &a, &b };
    coliseum.combat();
}
