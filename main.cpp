#include "eventHandler.h"
#include "screen.h"
#include "Bomb.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h> // To draw circles
#include <iostream>
#include <SDL2/SDL_image.h>
#include "gameStats.h"
// #include <list>
// #include <string>
// #include "bombs.h"
// #include "missiles"
#include "imageCreator.h"
#include "missiles.h"
#include "collisionDetection.h"
/* Some global stuff */
using namespace std;



int main()
{


      srand(time(NULL));

  EventHandler events;
  ImageCreator images;
  ACTIONS input;
  images.setColor(255, 0, 0);
  Screen screen("Laser Attack Alpha", 1024, 768);
  if(screen.init()==false) {
    cout << "Error initializing SDL." << endl;
  }

  SDL_Renderer *renderer;
  renderer = screen.getRenderer();

  SDL_Texture *startScreen = nullptr;
  startScreen = images.getTexture(renderer, "startscreen.png");
  bool notClicked = true;

  SDL_Texture *info = nullptr;
  info = images.fromText(renderer, "OpenSans-Bold.ttf", "PRESS ANY KEY TO CONTINUE...", 20);

  //
  int texW = 0;
  int texH = 0;
  SDL_QueryTexture(info, NULL, NULL, &texW, &texH);
  SDL_Rect dstrect = { 400 - texW/2, 500, texW, texH };
  // SDL_RenderCopy(renderer, texture, NULL, &dstrect);

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // SET SCREEN TO BLACK


  while(input != CLICKED_LEFT) {
    input = events.processEvents();

    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderCopy(renderer, startScreen, NULL, NULL);
    SDL_RenderCopy(renderer, info, NULL, &dstrect);
    SDL_RenderPresent(renderer);
  }


// Are these needed?
  bool running = true;
  bool gameOver = false;

// Initialize game:
  // SDL_Renderer *gameRenderer;

  // gameRenderer = SDL_CreateRenderer(screen.getWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
  SDL_Texture *background = nullptr;
  background = images.getTexture(renderer, "city.png");
  SDL_Texture *gameView = nullptr;
  gameView = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1024, 600);
  Screen::Block *gamePointer;
  gamePointer = screen.add(0, 0, 1024, 600, FIXED, 1, 1);
	gamePointer -> setTexture(gameView);
  gamePointer -> isLast = true;

  //SDL_SetRenderTarget(gameRenderer, gameView);
// SDL_SetRenderTarget(renderer, gameView);
  images.setColor(0, 0, 0);
  Screen::Block *scorePointer;
  scorePointer = screen.add(0, 0, 1024, 168, FIXED, 1, 1);
  GameStats stats;
  scorePointer -> setTexture(stats.init(renderer));

    //stats.init(renderer));
  stats.updateTexture(renderer);



  BombHandler bombs;
  MissileHandler missiles;
  CollisionDetection collision;



  screen.rescale();

    int timer = 0;

  while(running) {
    switch(events.processEvents()) {
			case CLICKED_LEFT:
			{
        bombs.add(events.mouse.x, events.mouse.y);
        break;
			}
			case RESIZE:
			{
				screen.resize();
				screen.rescale();
				break;
			}
			case QUIT:
			{
				running=false;
				break;
			}
  }

      SDL_SetRenderTarget(renderer, gameView);
      SDL_RenderCopy(renderer, background, NULL, NULL);
      bombs.update(&collision, &missiles.missiles);
      missiles.update(&stats);
      missiles.draw(renderer);
      bombs.draw(renderer);

      gameOver = stats.updateTexture(renderer);

      //SDL_RenderPresent(gameRenderer);
      SDL_SetRenderTarget(renderer, NULL);
      screen.clear();
      screen.draw();
      screen.render();


// ADD SOME MISSILES
      if(timer>=100) {
        timer = 0;
        missiles.add();
      }
      SDL_Delay(10);
      timer++;


      if(gameOver) {
        // INITIALIZE GAME OVER
        SDL_Texture *infoGameOver = nullptr;
        infoGameOver = images.fromText(renderer, "OpenSans-Bold.ttf", "GAME OVER", 50);
        int texW = 0;
        int texH = 0;
        SDL_QueryTexture(infoGameOver, NULL, NULL, &texW, &texH);
        SDL_Rect dstrect = { 400 - texW/2, 300, texW, texH };


        while(gameOver) {
          switch(events.processEvents()) {
            case QUIT:
            {
              running=false;
              gameOver=false;
              break;
            }
          }
          screen.clear();
          screen.draw();
          SDL_RenderCopy(renderer, infoGameOver, NULL, &dstrect);
          screen.render();
        }
        SDL_DestroyTexture(infoGameOver);
      }
    }


  return 1;
}
