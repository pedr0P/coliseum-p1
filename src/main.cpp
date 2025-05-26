#include "battle.cpp"
#include <iostream>

int main(int argc, char* argv[]) {
    auto input_processer = [] (Warrior &x) -> void {
        std::cout << "|       Name: ";
        std::cin >> x.name ;
        std::cout << "(Recommended to be 100 or more)\n";
        while (1) {
            std::cout << "| Max health: ";
            std::cin >> x.max_health;
            std::cout << "|     Health: ";
            std::cin >> x.health;

            if ( x.health > x.max_health ) {
                loglog("error: max_health needs to be more than health", true);
            } else { break; }
        }

        std::cout << "(Recommended to be out of 5, but the choice is yours):\n";
        std::cout << "|   Strength: ";
        std::cin >> x.stat_stats[STRENGTH];
        std::cout << "|    Defense: ";
        std::cin >> x.stat_stats[DEFENSE];
        std::cout << "|    Healing: ";
        std::cin >> x.stat_stats[HEALING];
    };

    Warrior a;
    Warrior b;
    std::cout << "Player ONE:\n";
    input_processer(a);
    std::cout << "Player TWO:\n";
    input_processer(b);

    std::cin.get();

    // a.name = "Batman";
    // a.max_health = 120;
    // a.health = 120;
    // a.stat_stats = { 3, 2, 5 };
    // b.name = "Superman";
    // b.max_health = 120;
    // b.health = 120;
    // b.stat_stats = { 5, 2, 1 };


    Arena coliseum;
    coliseum.list_of_warriors = { &a, &b };
    coliseum.combat();
}
