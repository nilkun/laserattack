#include "Bomb.h"

void BombHandler::add(int &x, int &y) {
  Bomb adding { x, y };
  bombs.push_back(adding);
}

BombHandler::BombHandler() {

}
void BombHandler::clear() {
  bombs.clear();
}
void BombHandler::draw(SDL_Renderer* renderer)
{
  for(Bomb &bomb : bombs) {
    filledCircleColor(renderer, bomb.x, bomb.y, bomb.radius, bomb.fader);
    bomb.fader-=0x0F000000;
    bomb.radius++;
  }
}

void BombHandler::update(CollisionDetection *collision, std::list<MissileHandler::Missile> *missiles, int &score, int &points) {
  for (std::list<Bomb>::iterator bomb = bombs.begin(); bomb != bombs.end();) {
    bomb -> update();
    if (bomb -> remove) {
       bomb = bombs.erase(bomb);
    }
    else {
      for (std::list<MissileHandler::Missile>::iterator missile = missiles -> begin(); missile != missiles -> end();) {
        if(missile -> isAlive)
        {
          if (collision -> circleAndPoint(bomb -> x, bomb -> y, bomb -> radius, missile -> currentLocation.x, missile -> currentLocation.y)) {
           missile -> isAlive = false;
           missile -> awardPoints = true;
           score += points;
          }
        }
        ++missile;
      }
    }
    ++bomb;
   }
}

void BombHandler::Bomb::update() {
  radius += expansion;
  if((int)radius > maxsize)
  {
    remove = true;
  }
  else
  {

  }
}
BombHandler::Bomb::Bomb(){}
BombHandler::Bomb::Bomb(int &x, int &y) : x(x), y(y) {
  remove = false;
  maxsize = 50;
  radius = 1;
}
