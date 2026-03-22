#include "character_class.cpp"
#include "menu.h"
#include <iostream>

int main() {
  menu();
  Character char1("Greg", "Human", 100, 1);
  char1.attack();
  char1.takeDamage(10);
  std::cout << char1.getName() << " has " << char1.getHp() << " HP."
            << std::endl;
  return 0;
}