#include "Character.h"
#include <iostream>

Character::Character(std::string pName, std::string pType, int pMaxHp, int pLevel,
                     std::string pIconPath) {
  name = pName;
  type = pType;
  maxHp = pMaxHp;
  hp = maxHp;
  level = pLevel;
  iconPath = pIconPath;
}

std::string Character::getName() const { return name; }
std::string Character::getType() const { return type; }
std::string Character::getIcon() const { return iconPath; }
int Character::getHp() const { return hp; }
int Character::getMaxHp() const { return maxHp; }
int Character::getLevel() const { return level; }

void Character::setHp(int pHp) { hp = pHp; }
void Character::setMaxHp(int pMaxHp) { maxHp = pMaxHp; }
void Character::setLevel(int pLevel) { level = pLevel; }
void Character::setIcon(std::string pIcon) { iconPath = pIcon; }

void Character::Attack() {
  std::cout << name << " uses a basic " << type << " attack!" << std::endl;
}

void Character::TakeDamage(int damage) {
  hp -= damage;
  if (hp < 0)
    hp = 0;
  std::cout << name << " took " << damage << " damage! (HP: " << hp << "/"
            << maxHp << ")\n";
}
