#ifndef __MISSILES_H_INCLUDED__
#define __MISSILES_H_INCLUDED__
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>  // for circles
#include <list>
#include "gameStats.h"

class MissileHandler {


public:


  struct Missile {
    int ground = 600;
    int kill = 0;
    bool hitCity = false;
    bool awardPoints = false;

    int radius = 1;
    int speed = 0;
    float ratio;
    Uint32 fader=0xFF00FFFF;
    bool remove = false;
    bool isAlive = true;
    float x = 0;
    float y = 0;

    SDL_Rect course; // the projectile course
    Missile();
    void update();
    void display(SDL_Renderer* renderer);
  };

  MissileHandler();
  std::list<Missile> missiles;
  void add();
  void draw(SDL_Renderer *renderer);
  void update(GameStats *stats);
};

#endif
