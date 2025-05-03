#include "Spell.h"
#include "Wizard.h"
#include "Creature.h"
#include <vector>
#include <iostream>

int main() {
    // Create a player
    Wizard player("Merlin");

    // Create a list of enemy creatures
    std::vector<Creature> enemies;
    enemies.push_back(Creature("GOBLIN", "FIRE", 50, 10));
    enemies.push_back(Creature("ORC", "WATER", 60, 15));
    enemies.push_back(Creature("DRAGON", "WIND", 100, 25));

    // Create the spells
    Spell fireball("Fireball", 20, "damage", 30);       // Deals 30 damage, costs 20 mana
    Spell healingLight("Healing Light", 10, "heal", 20); // Heals 20 health, costs 10 mana
    Spell manaRestore("Mana Restore", 5, "mana", 30);    // Restores 30 mana, costs 5 mana

    // Main game loop
    for (size_t i = 0; i < enemies.size(); ++i) {
        Creature& enemy = enemies[i];
        std::cout << "\nA wild " << enemy.type << " appears!\n";

        // Battle loop
        while (player.health > 0 && !enemy.isDefeated()) {
            // Show current status
            std::cout << "\nYour Health: " << player.health << " | Mana: " << player.mana << std::endl;
            std::cout << enemy.type << " Health: " << enemy.health << std::endl;

            // Show available actions
            std::cout << "Choose action:\n";
            std::cout << "1) Cast Fireball (Damage, 20 mana)\n";
            std::cout << "2) Cast Healing Light (Heal, 10 mana)\n";
            std::cout << "3) Cast Mana Restore (Restore Mana, 5 mana)\n";
            std::cout << "Enter your choice (1-3): ";
            int choice;
            std::cin >> choice;

            // Player's turn: cast the chosen spell
            if (choice == 1) {
                fireball.apply(player, enemy); // Attack enemy
            } else if (choice == 2) {
                healingLight.apply(player, enemy); // Heal self
            } else if (choice == 3) {
                manaRestore.apply(player, enemy); // Restore mana
            } else {
                std::cout << "Invalid choice. Turn skipped.\n";
            }

            // Enemy's turn: only if it's still alive
            if (!enemy.isDefeated()) {
                int dmg = enemy.attack();
                std::cout << enemy.type << " attacks for " << dmg << " damage!\n";
                player.health -= dmg;
                if (player.health < 0) player.health = 0;
            }
        }

        // After this enemy is defeated or player is defeated
        if (player.health <= 0) {
            std::cout << "You have been defeated!\n";
            break;
        } else {
            std::cout << "You defeated the " << enemy.type << "!\n";
        }
    }

    // End of game: check for victory
    if (player.health > 0) {
        std::cout << "Congratulations! You have defeated all the creatures!\n";
    }
    return 0;
}
