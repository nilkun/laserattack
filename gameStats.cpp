#include "imageCreator.h"
#include "gameStats.h"
#include <stdlib.h>
GameStats::GameStats() {}

void GameStats::updateScore(SDL_Renderer *renderer) {
  SDL_DestroyTexture(scoreT);
  scoreT = creator.fromText(renderer, "OpenSans-Bold.ttf", std::to_string(score).c_str(), 40);
}
void GameStats::updateStatus(SDL_Renderer *renderer) {
  SDL_DestroyTexture(status);
  status = creator.fromText(renderer, "OpenSans-Bold.ttf", statusMessages[hits], 40);
}



bool GameStats::updateTexture(SDL_Renderer *renderer) {
  SDL_DestroyTexture(mainTexture);

  mainTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1024, 168);

  SDL_DestroyTexture(scoreT);
  scoreT = creator.fromText(renderer, "OpenSans-Bold.ttf", std::to_string(score).c_str(), 40);

  SDL_DestroyTexture(status);
  status = creator.fromText(renderer, "OpenSans-Bold.ttf", statusMessages[hits], 20);


  SDL_SetRenderTarget(renderer, mainTexture);
  SDL_SetRenderDrawColor(renderer, 128, 128, 128, 0);
  SDL_RenderClear(renderer);


  SDL_Rect location = { 10, 10, 0, 0};
  SDL_QueryTexture(scoreText, NULL, NULL, &location.w, &location.h);
  SDL_RenderCopy(renderer, scoreText, NULL, &location);

  location.x += location.w;
  SDL_QueryTexture(scoreT, NULL, NULL, &location.w, &location.h);
  SDL_RenderCopy(renderer, scoreT, NULL, &location);

  location.x += location.w;
  SDL_QueryTexture(statusText, NULL, NULL, &location.w, &location.h);
  SDL_RenderCopy(renderer, statusText, NULL, &location);

  location.x += location.w;
  SDL_QueryTexture(status, NULL, NULL, &location.w, &location.h);
  SDL_RenderCopy(renderer, status, NULL, &location);

  SDL_SetRenderTarget(renderer, NULL);

  if(hits >= 5) return true;
  return false;
}

SDL_Texture *GameStats::init(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  scoreT = creator.fromText(renderer, "OpenSans-Bold.ttf", std::to_string(score).c_str(), 40);
  statusText = creator.fromText(renderer, "OpenSans-Bold.ttf", statusMessages[hits], 40);
  status = creator.fromText(renderer, "OpenSans-Bold.ttf", "  STATUS:  ", 40);
  scoreText = creator.fromText(renderer, "OpenSans-Bold.ttf", "  SCORE: ", 40);
  mainTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1024, 168);

  return mainTexture;
}
