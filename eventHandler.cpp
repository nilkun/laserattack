#include "eventHandler.h"

EventHandler::EventHandler() { Mouse mouse; };

ACTIONS EventHandler::processEvents(){
  while(SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT: {
        return QUIT;
      }
      case SDL_MOUSEBUTTONDOWN:
        switch (event.button.button)
        {
          case SDL_BUTTON_LEFT:
          {
            SDL_GetMouseState(&mouse.x, &mouse.y);
            return CLICKED_LEFT;
          }
          case SDL_BUTTON_RIGHT:
          {
             SDL_GetMouseState(&mouse.x, &mouse.y);
             return CLICKED_RIGHT;
          }
        }
      case SDL_KEYDOWN:
        switch(event.key.keysym.sym)
        {
          case SDLK_ESCAPE:
          {
            return ESCAPE;
          }
          case SDLK_F1:
          {
            return DEFAULT;
          }
          case SDLK_F2:
          {
            return DEFAULT;
          }
          case SDLK_F3:
          {
            return DEFAULT;
          }
          case SDLK_F4:
          {
            return DEFAULT;
          }
          return DEFAULT;
        }

      case SDL_WINDOWEVENT:
      {
        switch (event.window.event) {
          case SDL_WINDOWEVENT_RESIZED:
          {
            // switch (event.type) {
            //   case SDL_MOUSEBUTTONUP: {
                  return RESIZE;
            //   }
            //   return DEFAULT;
            // }
            // return DEFAULT;
          }
          return DEFAULT;
        }
        return DEFAULT;
      }
    }
  }
  return DEFAULT;;
}
