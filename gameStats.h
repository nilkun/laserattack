#ifndef __GAMESTATS_H__
#define __GAMESTATS_H__
#include <string>
#include <SDL2/SDL.h>
#include "../gameEngine/creatorTools/CreatorTools.h"
class GameStats {
  //
  // TextureCreator creator;
  //
  // SDL_Texture *statusText;
  // SDL_Texture *scoreText;
  // SDL_Texture *scoreT;
  // SDL_Texture *status;
  // SDL_Texture *mainTexture;

public:
    // void updateScore(SDL_Renderer *renderer, int score);
    // void updateStatus(SDL_Renderer *renderer);
    // bool updateTexture(SDL_Renderer *renderer, int score, int hits);
    // GameStats();
    // SDL_Texture *init(SDL_Renderer *renderer, int score);

    const char* statusMessages[6] = {
      "Everything is under control. ",
      "No cause for alarm. ",
      "Beginning evacuation! ",
      "Critical! ",
      "Almost dead ",
      "Game over, man! ",
    };
    //
    // int hits = 0;
      // int score = 0;
      // int missile = 500;
};

#endif
