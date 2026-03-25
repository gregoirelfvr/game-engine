#pragma once

#include <string>

class Character {
protected:
  std::string name, type, iconPath;
  int hp, maxHp, level;

public:
  Character(std::string pName, std::string pType, int pMaxHp, int pLevel,
            std::string pIconPath);

  // Getters
  std::string getName() const;
  std::string getType() const;
  std::string getIcon() const;
  int getHp() const;
  int getMaxHp() const;
  int getLevel() const;

  // Setters
  void setHp(int pHp);
  void setMaxHp(int pMaxHp);
  void setLevel(int pLevel);
  void setIcon(std::string pIcon);

  // Methods
  virtual void Attack();
  void TakeDamage(int damage);
};
