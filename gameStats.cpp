// #include "../gameEngine/creatorTools/CreatorTools.h"
#include "gameStats.h"
// #include <stdlib.h>
// #include <iostream>

// using namespace std;
// GameStats::GameStats() {}

// void GameStats::updateScore(SDL_Renderer *renderer, int score) {
//
//   SDL_DestroyTexture(scoreT);
//   // scoreT = creator.fromFontToText(renderer, "resources/OpenSans-Bold.ttf", std::to_string(score).c_str(), 40);
// }
// void GameStats::updateStatus(SDL_Renderer *renderer) {
//   SDL_DestroyTexture(status);
//   // status = creator.fromFontToText(renderer, "resources/OpenSans-Bold.ttf", statusMessages[hits], 40);
// }

/* adding here
  std::string scoreboardStaticText = creator.fromAtlasToText(
                                              renderer,
                                              bitfont,
                                              "SCORE:",
                                              40);
  std::string scoreboardDynamicText = "placeholder"
  SDL_Texture scoreboardStaticText2 = creator.fromAtlasToText(
                                              renderer,
                                              bitfont,
                                              "STATUS:",
                                              40);
  std::string scoreboardDynamicText2 = "placeholder"
*/

// bool GameStats::updateTexture(SDL_Renderer *renderer, int score, int hits) {
//   SDL_DestroyTexture(scoreT);
//
//   scoreT = creator.fromFontToText(renderer, "resources/OpenSans-Bold.ttf", std::to_string(score).c_str(), 40);
//   SDL_DestroyTexture(statusText);
//   statusText = creator.fromFontToText(renderer, "resources/OpenSans-Bold.ttf", statusMessages[hits], 40);
//   SDL_Rect location = { 10, 10, 0, 0};
//   SDL_QueryTexture(scoreText, NULL, NULL, &location.w, &location.h);
//   SDL_RenderCopy(renderer, scoreText, NULL, &location);
//   location.x += location.w;
//   SDL_QueryTexture(scoreT, NULL, NULL, &location.w, &location.h);
//   SDL_RenderCopy(renderer, scoreT, NULL, &location);
//   location.x += location.w;
//   SDL_QueryTexture(status, NULL, NULL, &location.w, &location.h);
//   SDL_RenderCopy(renderer, status, NULL, &location);
//   location.x += location.w;
//   SDL_QueryTexture(statusText, NULL, NULL, &location.w, &location.h);
//   SDL_RenderCopy(renderer, statusText, NULL, &location);
//   SDL_SetRenderTarget(renderer, NULL);
//
//
//
//   if(hits >= 5) return true;
//   return false;
// }

// SDL_Texture *GameStats::init(SDL_Renderer *renderer, int score) {
//
//   creator.setColor(109, 90, 28, 255);
//   SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//   status = creator.fromFontToText(renderer, "resources/OpenSans-Bold.ttf", "  STATUS:  ", 40);
//   scoreText = creator.fromFontToText(renderer, "resources/OpenSans-Bold.ttf", "  SCORE: ", 40);
//   creator.setColor(128, 128, 128, 255);
//   scoreT = creator.fromFontToText(renderer, "resources/OpenSans-Bold.ttf", std::to_string(score).c_str(), 40);
//   statusText = creator.fromFontToText(renderer, "resources/OpenSans-Bold.ttf", statusMessages[hits], 40);
//   mainTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1024, 168);
//
//   return mainTexture;
// }
