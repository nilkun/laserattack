// EVENT HANDLER FOR LASER ATTACK
// BASED ON MENUSYSTEM v0.3

#ifndef __EVENTHANDLER_H__
#define __EVENTHANDLER_H__
#include <SDL2/SDL.h>


enum ACTIONS { DEFAULT, RESIZE, QUIT, CLICKED_LEFT, CLICKED_RIGHT, ESCAPE };

struct Mouse {
  int x;
  int y;
};

class EventHandler{
  SDL_Event event;

public:
  EventHandler();
  ACTIONS processEvents();
  int action;
  Mouse mouse;
};
#endif
