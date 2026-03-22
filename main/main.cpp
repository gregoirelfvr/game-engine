#include "Class/character_class.cpp"
#include "UI/menu.h"
#include <iostream>
#include <vector>

int main() {
  Character char1("Greg", "Human", 100, 1);
  char1.setIcon("../assets/characters/temp_gold.png");
  char1.attack();
  char1.takeDamage(70);
  std::cout << char1.getName() << " has " << char1.getHp() << " HP."
            << std::endl;
  Character char2("Greg2", "Human", 100, 1);
  char2.setIcon("../assets/characters/temp_red.png");

  std::vector<Character> player_team = {char1, char2};
  menu(player_team);
  return 0;
}