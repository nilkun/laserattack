#include "missiles.h"
#include <list>

// MissileHandler::checkNew() {
//
// }


MissileHandler::MissileHandler() {
}
void MissileHandler::clear() {
  missiles.clear();
}
bool MissileHandler::isEmpty() {
  return missiles.empty();
}

MissileHandler::Missile::Missile() {

  trajectory.x = rand()%screenWidth;
  trajectory.y = 0;
  trajectory.w = rand()%screenWidth;
  trajectory.h = screenHeight;

  x_location = trajectory.x;
  y_location = trajectory.y;

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

MissileHandler::Missile::Missile(float &speed) {

  trajectory.x = rand()%screenWidth;
  trajectory.y = 0;
  trajectory.w = rand()%screenWidth;
  trajectory.h = screenHeight;

  x_location = trajectory.x;
  y_location = trajectory.y;

  yVelocity = speed;
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
    //currentLocation.y
    y_location+= yVelocity;
    //currentLocation.x
    x_location= trajectory.x + y_location * xToYRatio;

    if( y_location >= ground) // If missile hits ground...
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

    if( trajectory.y >= y_location) // If the beginning of the line has passed the end...
    {
      remove = true;
    }
  }
}

void MissileHandler::add(float &speed) {
  Missile adding(speed);
  missiles.push_back(adding);
}

void MissileHandler::draw(SDL_Renderer* renderer)
{
  for(Missile &missile : missiles) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderDrawLine(renderer, missile.trajectory.x, missile.trajectory.y, missile.x_location, missile.y_location);

    if(!missile.isAlive) { // If the missile is dead, then do this...
      filledCircleColor(renderer, missile.x_location, missile.y_location, missile.radius, missile.fader);
      missile.fader-=0x0F000F00;
      missile.radius+=3;
    }
  }
}

void MissileHandler::update(int &hits) {
  for (std::list<Missile>::iterator missile = missiles.begin(); missile != missiles.end();) {
    missile -> update();
    if(missile -> hitCity) {
      missile -> hitCity = false;
      hits++;
      if(hits > 5) hits = 5;
    }
    if (missile -> remove) {
       missile = missiles.erase(missile);
    }
    else {
       ++missile;
    }
  }
}
