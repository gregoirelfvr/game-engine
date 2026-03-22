#pragma once
#include <iostream>
#include <string>

class Character {
protected:
  std::string name, type;
  int hp, maxHp, level;

public:
  Character(std::string pName, std::string pType, int pMaxHp, int pLevel) {
    name = pName;
    type = pType;
    maxHp = pMaxHp;
    hp = maxHp;
    level = pLevel;
  }

  // Getters
  std::string getName() { return name; }

  std::string getType() { return type; }

  int getHp() { return hp; }

  int getMaxHp() { return maxHp; }

  int getLevel() { return level; }

  // Setters
  void setHp(int pHp) { hp = pHp; }

  void setMaxHp(int pMaxHp) { maxHp = pMaxHp; }

  void setLevel(int pLevel) { level = pLevel; }

  // Methods
  virtual void attack() {
    std::cout << name << " uses a basic " << type << " attack!" << std::endl;
  }

  void takeDamage(int damage) {
    hp -= damage;
    if (hp < 0)
      hp = 0;
    std::cout << name << " took " << damage << " damage! (HP: " << hp << "/"
              << maxHp << ")\n";
  }
};
