#include "missiles.h"
#include <list>


MissileHandler::MissileHandler() {
}

MissileHandler::Missile::Missile() {

  trajectory.x = rand()%screenWidth;
  trajectory.y = 0;
  trajectory.w = rand()%screenWidth;
  trajectory.h = screenHeight;

  currentLocation.x = trajectory.x;
  currentLocation.y = trajectory.y;

  yVelocity = rand()%5 + 2;
  xToYRatio = (float)(trajectory.w - trajectory.x)/(trajectory.h - trajectory.y);
  // This value is used to calculate the X location.

  // reuse width for resetting x!
  trajectory.w = trajectory.x;

  isAlive = true;
  hitCity = false;
  remove = false;

// GET RID OF THIS!!!
  ground = 600;

}

void MissileHandler::Missile::update()
{
  if(isAlive) {
    currentLocation.y += yVelocity;
    currentLocation.x = trajectory.x + currentLocation.y * xToYRatio;

    if( currentLocation.y >= ground) // If missile hits ground...
    {
      isAlive = false;
      hitCity = true;
    }
  }
  else {
    trajectory.y += yVelocity;
    yVelocity++;

    // currentLocation.x is the same as trajectory.w
    trajectory.x = trajectory.w + trajectory.y * xToYRatio;

    if( trajectory.y >= currentLocation.y) // If the beginning of the line has passed the end...
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
    SDL_RenderDrawLine(renderer, missile.trajectory.x, missile.trajectory.y, missile.currentLocation.x, missile.currentLocation.y);

    if(!missile.isAlive) { // If the missile is dead, then do this...
      filledCircleColor(renderer, missile.currentLocation.x, missile.currentLocation.y, missile.radius, missile.fader);
      missile.fader-=0x0F000F00;
      missile.radius+=3;
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
