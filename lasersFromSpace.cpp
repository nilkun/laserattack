#include <SDL2/SDL.h>

// Game Engine
#include "../gameEngine/window/viewport.h"
#include "../gameEngine/window/window.h"
#include "../gameEngine/creatorTools/CreatorTools.h"
#include "highscore.h"

// Game files
#include "Bomb.h"
#include "missiles.h"
#include "eventHandler.h"
#include "gameStats.h"
#include "playerStats.h"

void showMessage(SDL_Renderer* renderer, std::string message, FontAtlas *bitfont, int yPos = 300, int xPos = -1);

TextureCreator images;

SDL_Color isRed = { 255, 0, 0, 0 };

int main()
{
  /* Set the random seed */
  srand(time(NULL));

  /* Create game engine objects */
  EventHandler events;

  ACTIONS input;
  int SCREENWIDTH = 1024;
  /* Create window, it is hardcoded to 1024 x 768 */
  Screen screen("Lasers from space!!!", SCREENWIDTH, 768);

  /* Prepare pointers and ints */
  SDL_Renderer *renderer = nullptr; // Pointer to renderer
  SDL_Texture *infoText = nullptr; // Used for "press any key..."
  SDL_Texture* logoText =nullptr;
  SDL_Texture *mousePointer = nullptr;
  SDL_Rect mousePosition = { 0, 0, 5, 5 };
  FontAtlas bitfont; // For the 8-bit font
  int logoSizeX = 5 * 7 * 20;
  int logoSizeY = 5 * 9;
  SDL_Rect logo = { (SCREENWIDTH - logoSizeX)/2, 350, logoSizeX, logoSizeY };

  // Set renderer to screen window
  renderer = screen.getRenderer();

  /* Lets add a font */
    bitfont.texture = images.fromImage(renderer, "resources/alphabet.png");
    SDL_Rect destination = { 0, 0, 7, 9 };
    for(int i = 32; i <= 128; i++) {
      /* set location data in atlas */
      bitfont.fontMap[i] = destination;
      destination.x += 6;
    }

  logoText = images.fromAtlasToText(renderer, "Lasers from Space!!!", &bitfont);
  infoText = images.fromAtlasToText(renderer, "PRESS ANY KEY TO CONTINUE...", &bitfont);
  mousePointer = images.fromImage(renderer, "resources/pointer.png");

  /* Set up start screen variables */
  SDL_ShowCursor(0); // Hide cursor

  /* Get size of texture and assign it to rectangle */
  int texW = 0, texH = 0;
  SDL_QueryTexture(infoText, NULL, NULL, &texW, &texH);
  SDL_Rect info = { -30 + (SCREENWIDTH - texW)/2, 400, texW, texH };

  while(input != CLICKED_LEFT) {
    input = events.processEvents();

    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    SDL_RenderCopy(renderer, logoText, NULL, &logo);
    SDL_RenderCopy(renderer, infoText, NULL, &info);

    SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
    SDL_RenderCopy(renderer, mousePointer, NULL, &mousePosition);
    SDL_RenderPresent(renderer);
  }


  /* Initialize game objects */
  BombHandler bombs;
  MissileHandler missiles;
  CollisionDetection collision;
  GameStats stats;
  // SDL_Rect scoreboardLocation = { 0, 0, 49, 9 };

  SDL_Texture* scoreboardStaticText = images.fromAtlasToText(
                                              renderer,
                                              "SCORE: ",
                                              &bitfont);

  SDL_Texture* scoreboardStaticText2 = images.fromAtlasToText(
                                              renderer,
                                              "STATUS:",
                                              &bitfont);


  /* Game variables */
  Viewport gameViewport;
  Viewport scoreViewport;
  bool gameIsRunning;
  bool gameover;
  int timer;
  enum GameState { running, paused, startNextLevel, gameOver };
  GameState GAMESTATE = startNextLevel;
  Player player;
  player.init();
  //init();

      // Game textures
      SDL_Texture *background = nullptr;
      // VIEWPORTS!!!
      gameViewport.position = { 0, 0, 1024, 600 };
      scoreViewport.position = { 0, 600, 1024, 128 };
      background = images.fromImage(renderer, "resources/city.png");

      gameIsRunning = true;
      gameover = false;

      //stats.init(renderer, player.score);
      //stats.updateTexture(renderer, player.score, player.cityHits);

      timer = 0;



  while(gameIsRunning) {
    switch(GAMESTATE) {
      case startNextLevel:
      {
        SDL_RenderSetViewport(renderer, NULL);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        /* Render to game viewport, 1st the background */
        SDL_RenderSetViewport(renderer, &gameViewport.position);
        SDL_RenderCopy(renderer, background, NULL, NULL);
        // /* Render to score viewport */
        SDL_RenderSetViewport(renderer, &scoreViewport.position);

        // stats.updateTexture(renderer, player.score, player.cityHits);

        SDL_Rect scoreboardLocation = { 0, 0, 49, 9 };
        SDL_RenderCopy(renderer, scoreboardStaticText, NULL, &scoreboardLocation);
        scoreboardLocation = { 0, 10, 49, 9 };
        SDL_RenderCopy(renderer, scoreboardStaticText2, NULL, &scoreboardLocation);
        showMessage(renderer, std::to_string(player.score), &bitfont, 0, 50);
        showMessage(renderer, stats.statusMessages[player.cityHits], &bitfont, 10, 50);





        SDL_RenderSetViewport(renderer, NULL);
        SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
        SDL_RenderCopy(renderer, mousePointer, NULL, &mousePosition);
        showMessage(renderer, player.levelMessage(), &bitfont);
        screen.render();
        // std::cout << "starting level" << std::endl;

        switch(events.processEvents()) {
          case CLICKED_LEFT:
          {
            GAMESTATE = running;
            break;
          }
          case ESCAPE:
          {
            GAMESTATE = running;
            break;
          }
          case QUIT:
          {
            gameIsRunning=false;
            break;
          }
        }
        break;
      }
      case paused:
      {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        /* Render to game viewport, 1st the background */
        SDL_RenderSetViewport(renderer, &gameViewport.position);
        SDL_RenderCopy(renderer, background, NULL, NULL);

        // /* Render to score viewport */
        SDL_RenderSetViewport(renderer, &scoreViewport.position);

        // stats.updateTexture(renderer, player.score, player.cityHits);
        SDL_Rect scoreboardLocation = { 0, 0, 49, 9 };
        SDL_RenderCopy(renderer, scoreboardStaticText, NULL, &scoreboardLocation);
        scoreboardLocation = { 0, 10, 49, 9 };
        SDL_RenderCopy(renderer, scoreboardStaticText2, NULL, &scoreboardLocation);
        showMessage(renderer, std::to_string(player.score), &bitfont, 0, 50);
        showMessage(renderer, stats.statusMessages[player.cityHits], &bitfont, 10, 50);

        SDL_RenderSetViewport(renderer, NULL);
        SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
        SDL_RenderCopy(renderer, mousePointer, NULL, &mousePosition);
        showMessage(renderer, "paused", &bitfont);
        screen.render();

      //  std::cout << "game is paused" << std::endl;
        switch(events.processEvents()) {
          case CLICKED_LEFT:
          {
            break;
          }
          case ESCAPE:
          {
            GAMESTATE = running;
            break;
          }
          case QUIT:
          {
            gameIsRunning=false;
            break;
          }
        }
        // EVENT LOOP
        break;
      }
      case running:
      {

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        /* This is the event handling */
        switch(events.processEvents()) {
          case CLICKED_LEFT:
          {
            bombs.add(events.mouse.x, events.mouse.y);
            player.score -= player.bombCost;
            break;
          }
          case ESCAPE:
          {
            GAMESTATE = paused;
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
        bombs.update(&collision, &missiles.missiles, player.score, player.missilePoints);
        missiles.update(player.cityHits);
        missiles.draw(renderer);
        bombs.draw(renderer);

        // /* Render to score viewport */
        SDL_RenderSetViewport(renderer, &scoreViewport.position);

        SDL_Rect scoreboardLocation = { 0, 0, 49, 9 };
        SDL_RenderCopy(renderer, scoreboardStaticText, NULL, &scoreboardLocation);
        scoreboardLocation = { 0, 10, 49, 9 };
        SDL_RenderCopy(renderer, scoreboardStaticText2, NULL, &scoreboardLocation);
        showMessage(renderer, std::to_string(player.score), &bitfont, 0, 50);
        showMessage(renderer, stats.statusMessages[player.cityHits], &bitfont, 10, 50);
        gameover = player.cityHits >= 5;
        if(gameover) GAMESTATE = gameOver;

        SDL_RenderSetViewport(renderer, NULL);
        SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
        SDL_RenderCopy(renderer, mousePointer, NULL, &mousePosition);
        screen.render();

        if(player.missilesLeft < 0) {
          if(missiles.isEmpty()) {
            GAMESTATE = startNextLevel;
            player.loadLevel();
          }
        } else
        if(timer>=player.missileFrequency) {
          timer = 0;
          missiles.add(player.missileSpeed);
          player.missilesLeft--;
        }
        SDL_Delay(10);
        timer++;
        break;
      }
      case gameOver:
      {
        SDL_RenderSetViewport(renderer, NULL);

        TopTen ranking;
        Highscore hSPlayer;
        std::list<std::string> strings;
        SDL_Texture* rankingList;

        SDL_Rect gameOverLocation;
        SDL_Rect rankingLocation;

        hSPlayer.name = "";
        hSPlayer.score = player.score;
        hSPlayer.level = player.level;

        ranking.loadHighscores();

        enum process { userInput, loadData, updateData, showData };
        process PROCESS = loadData;

        // highscore logic
        if(ranking.isHighscore(hSPlayer))
        {
          PROCESS = userInput;
        }

        while(gameover) {
          /* Event handler for Game over */
          // std::cout << "UPDATE:" << std::endl;
          screen.clear();
          /* Render to game viewport, 1st the background */
          SDL_RenderSetViewport(renderer, &gameViewport.position);
          SDL_RenderCopy(renderer, background, NULL, NULL);

          /* update and render bombs and missiles to game viewport */
          bombs.update(&collision, &missiles.missiles, player.score, player.missilePoints);
          missiles.update(player.cityHits);
          missiles.draw(renderer);
          bombs.draw(renderer);

          SDL_RenderSetViewport(renderer, &scoreViewport.position);
          // stats.updateTexture(renderer, player.score, player.cityHits);
          SDL_Rect scoreboardLocation = { 0, 0, 49, 9 };
          SDL_RenderCopy(renderer, scoreboardStaticText, NULL, &scoreboardLocation);
          scoreboardLocation = { 0, 10, 49, 9 };
          SDL_RenderCopy(renderer, scoreboardStaticText2, NULL, &scoreboardLocation);
          showMessage(renderer, std::to_string(player.score), &bitfont, 0, 50);
          showMessage(renderer, stats.statusMessages[player.cityHits], &bitfont, 10, 50);

          SDL_RenderSetViewport(renderer, NULL);

          switch(PROCESS) {
            case userInput:
            {
              showMessage(renderer, "ENTER NAME:", &bitfont, 200);
              showMessage(renderer, hSPlayer.name, &bitfont, 210);
              SDL_Event event;
              while(SDL_PollEvent(&event)) {
                switch (event.type) {
                  case SDL_QUIT:
                  {
                    gameIsRunning=false;
                    gameover=false;
                    break;
                  }
                  case SDL_KEYDOWN:
                  {
                    const char input = event.key.keysym.sym;
                    if(input >= ' ' && input <= 'z' && hSPlayer.name.length() < 6)
                    {
                      hSPlayer.name += input;
                    }
                    else if (input==13) // ENTER
                    {
                      PROCESS = updateData;
                    }
                    else if (input==8 && hSPlayer.name.length() > 0) // BACKSPACE
                    {
                      hSPlayer.name = hSPlayer.name.substr(0, hSPlayer.name.length() - 1);
                    }
                    break;
                  }
                }
              }
              break;
            }
            case loadData:
            {
              strings = ranking.getTopTen();
              rankingList = images.fromAtlasToTextbox(renderer, strings, &bitfont);
              int texW = 0;
              int texH = 0;
              SDL_QueryTexture(rankingList, NULL, NULL, &texW, &texH);
              gameOverLocation = { (1024 - texW)/2, 300, texW, texH };
              rankingLocation = { (1024 - texW)/2, 330, texW, texH };
              PROCESS = showData;
              break;
            }
            case updateData:
            {
              ranking.updateTopTen(hSPlayer);
              ranking.saveHighscores();
              PROCESS = loadData;
              ranking.loadHighscores();
              break;
            }
            case showData:
            {
              switch(events.processEvents()) {
                case QUIT:
                {
                  gameIsRunning=false;
                  gameover=false;
                  break;
                }
                case CLICKED_RIGHT:
                case _Y_:
                {
                  GAMESTATE = startNextLevel;
                  timer = 0;
                  missiles.clear();
                  bombs.clear();
                  player.init();
                  gameover=false;
                  break;
                }
                case ESCAPE:
                case _N_:
                {
                  gameIsRunning=false;
                  gameover=false;
                  break;
                }
              }
              SDL_RenderCopy(renderer, rankingList, NULL, &rankingLocation);
              showMessage(renderer, "game over", &bitfont);
              showMessage(renderer, "PLAY AGAIN? (Y/N)", &bitfont, 315);
              break;
            }
          }
          SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
          SDL_RenderCopy(renderer, mousePointer, NULL, &mousePosition);
          screen.render();
        }
        SDL_DestroyTexture(rankingList);
      }
    }
  }
  return 1;
}

void showMessage(SDL_Renderer *renderer, std::string message, FontAtlas *bitfont, int yPos, int xPos) {
  SDL_Texture *messageTexture = nullptr;
  images.setColor(0, 0, 0, 255);
  messageTexture = images.fromAtlasToText(renderer, message.c_str(), bitfont, isRed);

  int texW = 0;
  int texH = 0;
  SDL_QueryTexture(messageTexture, NULL, NULL, &texW, &texH);
  if(xPos == -1) xPos = (1024 - texW)/2; //centered
  SDL_Rect messageLocation = { xPos, yPos, texW, texH };
//  SDL_RenderSetViewport(renderer, NULL);
  SDL_RenderCopy(renderer, messageTexture, NULL, &messageLocation);
  SDL_DestroyTexture(messageTexture);
}
