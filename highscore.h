#ifndef __HIGHSCORE_H__
#define __HIGHSCORE_H__

#include <list>
#include <string>
#include <SDL2/SDL.h>
#include "../gameEngine/creatorTools/CreatorTools.h"
#include "../gameEngine/fileManager/fileManager.h"

struct Highscore {
  std::string name;
  int score;
  int level = 1;
  Highscore() {};
  Highscore(std::string name,
    int score,
    int level) : name(name), score(score), level(level){};
};

class TopTen {
public:
  FileManager file;
  std::list<Highscore> highscores;
  void loadHighscores();
  void resetHighscores();
  bool isHighscore(Highscore &player);
  bool updateTopTen(Highscore &player);
  // SDL_Texture* getTopTen(SDL_Renderer* renderer, FontAtlas &fontAtlas);
  std::string getRank(int x);
  void saveHighscores();
  std::list<std::string> getTopTen();
};



#endif
