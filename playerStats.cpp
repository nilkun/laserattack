#include "playerStats.h"

void Player::init() {
  score = 0;
  level = 0;
  loadLevel();
  missileSpeed = 1;
}
void Player::loadLevel() {
  level++;
  numberOfMissiles = missilesLeft = 9;
  // + level;
  missilePoints = 10 * level;
  missileSpeed *= 1.2;
  bombCost = 2 * level;
  cityHits = 0;
  missileFrequency = 50;
}

std::string Player::levelMessage() {
  std::string message = "LEVEL " + std::to_string(level) + ": GET READY!!!";
  return message;
}
