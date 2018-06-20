#ifndef __BOMBS_H__
#define __BOMBS_H__

#include <SDL2/SDL.h>
#include <list>
#include <stack>
#include <SDL2/SDL2_gfxPrimitives.h>  // for circles

#include <iostream>
#include "../gameEngine/collisionDetection/collisionDetection.h"
#include "missiles.h"

class BombHandler {

  struct Bomb {
    int x;
    int y;
    float radius;
    int expansion = 2;
    int maxsize;
    Uint32 fader=0xFF0000FF;
    bool remove;
    Bomb();
    Bomb(int &x, int &y);
    void update();
  };

public:
  std::list<Bomb> bombs;
  void add(int &x, int &y);
  void draw(SDL_Renderer* renderer);
  void clear();
  void update(CollisionDetection *collision, std::list<MissileHandler::Missile> *missiles, int &score, int &points);
  BombHandler();
  std::stack<int> removeIndex;
};

#endif
