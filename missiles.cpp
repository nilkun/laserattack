#include "missiles.h"
#include <list>


MissileHandler::MissileHandler() {
}

MissileHandler::Missile::Missile() {

  // Temporary values
  int screenWidth = 1024;
  int screenHeight = 600;

  course.x = rand()%screenWidth;
  course.y = 0;
  course.w = rand()%screenWidth;
  course.h = screenHeight;

  speed = rand()%5 + 2;
  ratio = (float)(course.w - course.x)/(course.h - course.y);
  // if (ratio < 0) ratio = -ratio;
  y = course.y;
  x = course.x;
}

void MissileHandler::Missile::update()
{
  if(isAlive) {
    y += speed;
    x = course.x + y * ratio;
    if( y >= ground) // If missile hits ground
    {
      isAlive = false;
      hitCity = true;
    }
  } else {
    course.y += speed;
    speed++;
    course.x = x - ((y - course.y) * ratio);
    if( course.y >= y) // if surpassed bottom then erase
    {
      remove = true;
    }
  }
}

void MissileHandler::add() {
  Missile adding;
  missiles.push_back(adding);
}

void MissileHandler::draw(SDL_Renderer* renderer)
{
  for(Missile &missile : missiles) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderDrawLine(renderer, missile.course.x, missile.course.y, missile.x, missile.y);
    if(!missile.isAlive) {
      filledCircleColor(renderer, missile.x, missile.y, missile.radius, missile.fader);
      missile.fader-=0x0F000F00;
      missile.radius++;
    }
  }
}

void MissileHandler::update(GameStats *stats) {
  for (std::list<Missile>::iterator missile = missiles.begin(); missile != missiles.end();) {
    missile -> update();
    if(missile -> hitCity) {
      missile -> hitCity = false;
      stats -> hits++;
    }
    else if(missile -> awardPoints) {
      missile -> awardPoints = false;
      stats -> score+= stats -> missile;
    }
    if (missile -> remove) {
       missile = missiles.erase(missile);
    }
    else {
       ++missile;
    }
  }
}
