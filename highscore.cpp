#include "highscore.h"

void TopTen::resetHighscores()
{
  highscores.clear();
  for(int i = 10; i > 0; i--)
  {
    Highscore current { "NILKUN", (100*i), i};
    highscores.push_back(current);
  }
}

bool TopTen::isHighscore(Highscore &player)
{
  for (std::list<Highscore>::iterator it = highscores.begin(); it != highscores.end(); ++it) {
    if( player.score > it-> score)
    {
      return true;
    }
  }
  return false;
}

bool TopTen::updateTopTen(Highscore &player)
{
  for (std::list<Highscore>::iterator it = highscores.begin(); it != highscores.end(); ++it) {
    if( player.score > it-> score)
    {
      highscores.insert(it, player);
      highscores.pop_back();
      return true;
    }
  }
  return false;
}

// SDL_Texture* TopTen::getTopTen(SDL_Renderer* renderer,
//   FontAtlas &fontAtlas)
// {
//   SDL_Texture* leaderboard;
//   SDL_Texture* temp;
//   std::string stringToSend;
//   int ranking = 1;
//   SDL_Rect drawArea = { 0, 0, 140, 9 };
//   TextureCreator textures;
//
//   // y spacing of 3 and y size of 9 means 7 spaces of 3 = 21 + 9*10 = 111
//   // x names are max 6 char, ie 6*7 = 42 + spacing + score, score max 8 digits 8*7 = 56 + 42 = 98 + 14 padding = 112
//   leaderboard = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
//     SDL_TEXTUREACCESS_TARGET,
//     140,
//     111);
//   SDL_SetRenderTarget(renderer, leaderboard);
//   SDL_Color isRed = { 255, 0, 0, 0 };
//   // iterate through the list
//   for (std::list<Highscore>::iterator it = highscores.begin();
//       it != highscores.end();
//       ++it)
//   {
//     if(ranking < 10)
//     {
//     stringToSend = std::to_string(ranking) + ".  ";
//     }
//     else
//     {
//       stringToSend = std::to_string(ranking) + ". ";
//     }
//     stringToSend += it -> name;
//     int addSpacing = stringToSend.length();
//     for(int i = 0; i < (10 - addSpacing); i++)
//     {
//       stringToSend += " ";
//     }
//     std::string score = std::to_string(it -> score);
//     for(int i = 0; i < 10 - score.length(); i++)
//     {
//       stringToSend += " ";
//     }
//     stringToSend += score;
//
//     // String is ok.
//     textures.setColor(0, 255, 0, 255);
//     temp = textures.fromAtlasToText(renderer, stringToSend, &fontAtlas, isRed);
//
//     SDL_RenderCopy(renderer, temp, NULL, &drawArea);
//     drawArea.y += 9;
//     ranking++;
//     SDL_DestroyTexture(temp);
//   }
//
//   SDL_SetRenderTarget(renderer, NULL);
//   return leaderboard;
// }

std::string TopTen::getRank(int x) {

  std::list<Highscore>::iterator it = highscores.begin();
  std::advance(it, x-1);
    // 'it' points to the element at index 'N'

  std::string stringToSend;
  if(x < 10)
  {
  stringToSend = std::to_string(x) + ".  ";
  }
  else
  {
    stringToSend = std::to_string(x) + ". ";
  }
  stringToSend += it -> name;
  std::string score = std::to_string(it -> score);
  for(int i = 0; i < 10 - score.length(); i++)
  {
    stringToSend += " ";
  }
  stringToSend += score;
  std::cout << stringToSend << std::endl;
  return stringToSend;
}

void TopTen::saveHighscores() {
  // std::cout << "saving scores..." << std::endl;
  file.openToSave("highscore.dat");
  for (std::list<Highscore>::iterator it = highscores.begin();
    it != highscores.end();
    ++it)
  {
    file.writeString(it -> name);
    // std::cout << "IT VALUE: " << it -> name << std::endl;
    file.writeData(it -> score);
    file.writeData(it -> level);
  }
  file.close();
  // std::cout << "saved!!!" << std::endl;
}

void TopTen::loadHighscores()
{
/*
  if no file, then create and populate
  else load;
} */
  if(file.load("highscore.dat"))
  {
    highscores.clear();
    for(int i = 0; i < 10; i++)
    {
      // std::cout << "writing data: " << i << std::endl;
      Highscore current;
      file.readString(current.name);
      file.readData(current.score);
      file.readData(current.level);
      highscores.push_back(current);
    }
    file.close();
  }
  else
  {
    // std::cout << "RESETTING HIGHSCORES!" << std::endl;
    resetHighscores();
  }
}

std::list<std::string> TopTen::getTopTen()
{
  std::list<std::string> strings;

  std::string stringToSend;
  stringToSend = "rank  Name  level  score";
  strings.push_back(stringToSend);
  stringToSend = "------------------------";
  strings.push_back(stringToSend);
  int ranking = 1;

  for (std::list<Highscore>::iterator it = highscores.begin();
      it != highscores.end();
      ++it)
  {
    if(ranking < 10)
    {
    stringToSend = std::to_string(ranking) + ".   ";
    }
    else
    {
      stringToSend = std::to_string(ranking) + ".  ";
    }
    stringToSend += it -> name;
    int addSpacing = stringToSend.length();
    std::string level = std::to_string(it -> level);
    for(int i = 0; i < (16 - addSpacing - level.length()); i++)
    {
      stringToSend += " ";
    }
    stringToSend += level;
    for(int i = 0; i < 2; i++)
    {
      stringToSend += " ";
    }
    std::string score = std::to_string(it -> score);
    for(int i = 0; i < 7 - score.length(); i++)
    {
      stringToSend += " ";
    }
    stringToSend += score;

    // String is ok.
    strings.push_back(stringToSend);
    ranking++;
  }
  return strings;
}


 //
 // 1. show loaded leaderboard;
 // 2. enter highScores
 // 3. show loaded leaderboard
 //
