#ifndef __PLAYERSTATS_H__
#define __PLAYERSTATS_H__
#include <iostream>

struct Player{
  int score;
  int level;

  int numberOfMissiles;
  int missilePoints;
  float missileSpeed;
  int missilesLeft;
  int bombCost;
  int levelNumber;
  int cityHits;
  int missileFrequency;

  void init();
  void loadLevel() ;
  std::string levelMessage();
};

#endif
