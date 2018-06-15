#include <SDL2/SDL.h>

// Game Engine
#include "../gameEngine/window/viewport.h"
#include "../gameEngine/window/window.h"
#include "../gameEngine/creatorTools/CreatorTools.h"

// Game files
#include "Bomb.h"
#include "missiles.h"
#include "eventHandler.h"
#include "gameStats.h"

int main()
{
  /* Set the random seed */
  srand(time(NULL));

  /* Create game engine objects */
  EventHandler events;
  TextureCreator images;
  ACTIONS input;

  /* Create window, it is hardcoded to 1024 x 768 */
  Screen screen("Lasers from space!!!", 1024, 768);
  int SCREENWIDTH = 1024;
  /* Prepare pointers and ints */
  SDL_Renderer *renderer = nullptr; // Pointer to renderer
  // SDL_Texture *startScreen = nullptr; // This will be the start screen image
  SDL_Texture *info = nullptr; // Used for "press any key..."
  SDL_Texture *newStartScreen = nullptr; // Using fonts instead of image
  SDL_Texture *mousePointer = nullptr;
  SDL_Rect mousePosition = { 0, 0, 5, 5 };






  // Set renderer to screen window
  renderer = screen.getRenderer();

  /* Lets add a font */
    FontAtlas bitfont;
    bitfont.texture = images.fromImage(renderer, "resources/alphabet.png");
    SDL_Rect destination = { 0, 0, 7, 9 };
    for(int i = 32; i <= 128; i++) {
      /* set location data in atlas */
      bitfont.fontMap[i] = destination;
      destination.x += 6;
    }
    SDL_Texture* logoText = images.fromAtlasToText(renderer, "Lasers from Space!!!", &bitfont);
    int logoSizeX = 5 * 7 * 20;
    int logoSizeY = 5 * 9;
    SDL_Rect logo = { (SCREENWIDTH - logoSizeX)/2, 350, logoSizeX, logoSizeY };
  /* End of font adding */
    info = images.fromAtlasToText(renderer, "PRESS ANY KEY TO CONTINUE...", &bitfont);

  /* Set up start screen textures */
  // startScreen = images.fromImage(renderer, "resources/startscreen.png");
  // images.setColor(255, 0, 0, 255); // Red text
  // info = images.fromFontToText(renderer, "resources/OpenSans-Bold.ttf", "PRESS ANY KEY TO CONTINUE...", 20);

  // images.fromFontToText(renderer, "resources/OpenSans-Bold.ttf", "Lasers from Space", 70);
  mousePointer = images.fromImage(renderer, "resources/pointer.png");
  /* Set up start screen variables */
  SDL_ShowCursor(0); // Hide cursor
  /* Get size of texture and assign it to rectangle */
  int texW = 0, texH = 0;
  SDL_QueryTexture(info, NULL, NULL, &texW, &texH);
  SDL_Rect infoLocation = { -30 + (SCREENWIDTH - texW)/2, 450, texW, texH };
  // SDL_QueryTexture(newStartScreen, NULL, NULL, &texW, &texH);
  // SDL_Rect startTextLocation = { 10, 550, texW, texH };

  while(input != CLICKED_LEFT) {
    input = events.processEvents();

    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    // SDL_RenderCopy(renderer, startScreen, NULL, NULL);
    SDL_RenderCopy(renderer, logoText, NULL, &logo);
    SDL_RenderCopy(renderer, info, NULL, &infoLocation);
//    SDL_RenderCopy(renderer, newStartScreen, NULL, &startTextLocation);

  //  SDL_RenderSetViewport(renderer, &logoScreen);
  //  images.setColor(255, 0, 0, 255); // Red text
    //images.fromAtlasToText(renderer, "Lasers from Space!!!", &bitfont);
//    SDL_RenderSetViewport(renderer, NULL);


    SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
    SDL_RenderCopy(renderer, mousePointer, NULL, &mousePosition);
    SDL_RenderPresent(renderer);
  }

/*  THIS IS THE END OF THE STARTSCREEN
    FROM NOW ON, WE ENTER THE GAME */

  // Game textures
  SDL_Texture *background = nullptr;

  // VIEWPORTS!!!
  Viewport gameViewport;
  gameViewport.position = { 0, 0, 1024, 600 };

  Viewport scoreViewport;
  scoreViewport.position = { 0, 600, 1024, 128 };

  background = images.fromImage(renderer, "resources/city.png");

  /* Initialize game objects */
  BombHandler bombs;
  MissileHandler missiles;
  CollisionDetection collision;

  /* Game variables */
  bool gameIsRunning = true;
  bool gameOver = false;

  GameStats stats;
  stats.init(renderer);
  stats.updateTexture(renderer);

  int timer = 0;


  while(gameIsRunning) {

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    /* This is the event handling */
    switch(events.processEvents()) {
			case CLICKED_LEFT:
			{
        bombs.add(events.mouse.x, events.mouse.y);
        break;
			}
			case RESIZE:
			{
				break;
			}
			case QUIT:
			{
				gameIsRunning=false;
				break;
			}
    }

    /* Render to game viewport, 1st the background */
    SDL_RenderSetViewport(renderer, &gameViewport.position);
    SDL_RenderCopy(renderer, background, NULL, NULL);

    /* update and render bombs and missiles to game viewport */
    bombs.update(&collision, &missiles.missiles);
    missiles.update(&stats);
    missiles.draw(renderer);
    bombs.draw(renderer);

    // /* Render to score viewport */
    SDL_RenderSetViewport(renderer, &scoreViewport.position);
    gameOver = stats.updateTexture(renderer);

    SDL_RenderSetViewport(renderer, NULL);
    SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
    SDL_RenderCopy(renderer, mousePointer, NULL, &mousePosition);
    screen.render();


// ADD SOME MISSILES, of course this should be changed!
    if(timer>=100) {
      timer = 0;
      missiles.add();
    }
    SDL_Delay(10);
    timer++;

/* Game over loop */
    if(gameOver) {
      // INITIALIZE GAME OVER
      SDL_Texture *infoGameOver = nullptr;
      images.setColor(0, 0, 0, 255);
      infoGameOver = images.fromFontToText(renderer, "resources/OpenSans-Bold.ttf", "GAME OVER", 50);

      int texW = 0;
      int texH = 0;
      SDL_QueryTexture(infoGameOver, NULL, NULL, &texW, &texH);
      SDL_Rect gameOverLocation = { (1024 - texW)/2, 300, texW, texH };


      while(gameOver) {
        /* Event handler for Game over */
        switch(events.processEvents()) {
          case QUIT:
          {
            gameIsRunning=false;
            gameOver=false;
            break;
          }
        }
        screen.clear();

        /* Render to game viewport, 1st the background */
        //SDL_SetRenderTarget(renderer, gameView);
        SDL_RenderSetViewport(renderer, &gameViewport.position);
        SDL_RenderCopy(renderer, background, NULL, NULL);

        /* update and render bombs and missiles to game viewport */
        bombs.update(&collision, &missiles.missiles);
        missiles.update(&stats);
        missiles.draw(renderer);
        bombs.draw(renderer);


        //SDL_SetRenderTarget(renderer, scorePointer -> texture);
        SDL_RenderSetViewport(renderer, &scoreViewport.position);
        stats.hits = 5; // Or else there will be an index error
        stats.updateTexture(renderer);

        SDL_RenderSetViewport(renderer, NULL);
        SDL_RenderCopy(renderer, infoGameOver, NULL, &gameOverLocation);

        SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
        SDL_RenderCopy(renderer, mousePointer, NULL, &mousePosition);
        screen.render();
      }
      SDL_DestroyTexture(infoGameOver);
    }
  }
  return 1;
}
