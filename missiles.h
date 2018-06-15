#ifndef __MISSILES_H_INCLUDED__
#define __MISSILES_H_INCLUDED__
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>  // for circles
#include <list>
#include "gameStats.h"

class MissileHandler {


public:

/*  WHAT DOES A MISSILE NEED TO KNOW?
    1. trajectory
    2. current position
    3. going or leaving

*/

  struct Missile {            // Individual missiles
    SDL_Rect trajectory;
    SDL_Point currentLocation;
    float xToYRatio;
    int yVelocity;

    bool remove = false;
    bool isAlive = true;

    Uint32 fader=0xFF00FFFF;

        int radius = 1;

    int ground = 600;         //
    int kill = 0;
    bool hitCity = false;
    bool awardPoints = false;

    int speed = 0;
    float ratio;

    float x = 0;
    float y = 0;
    int screenWidth = 1024;
    int screenHeight = 600;

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
