//Open file for reading in binary
#include <SDL2/SDL.h>
#include <vector>
#include "../tiles.h"
#include <iostream>

//1. Create high score arbitrary

struct HighScore {
  string name;
  int score;
  HighScore(string name, int score) { this.name = name; this.score = score };
}

// Create highscores
void populate(vector<HighScore> list) {
  for(int i = 1; i < 11; i++)
  {
    list.add("NILKUN", 5000*i);
  }
}

vector<HighScore> highScores;


void saveData(std::vector< std::vector <TileManager::Tile> > trackData) {
  std::string name = "new.track";
SDL_RWops* file = SDL_RWFromFile( name.c_str(), "r+b" );
  if(file == nullptr) {
    // No such file, so create it
    file = SDL_RWFromFile( name.c_str(), "w+b" );
  }

  if (file==nullptr) std::cout << "Error creating file!" << std::endl;

  // pointer to data

  // size of struct
  int sizeInBytes = sizeof(TileManager::Tile);
  // number of struct
  int noOfStructs = 80;
  std::cout << "No of structs(80): " << trackData.size() * trackData[0].size() << std::endl;

  for(auto &mediator : trackData) {
    for(auto &track : mediator) {
      std::cout << "Writing x:" << track.location.x << " y:" << track.location.y << std::endl;
      SDL_RWwrite(file, &track, 1, sizeInBytes);
    //  SDL_RWwrite(file, &track, sizeInBytes, noOfStructs);
    }
  }

  SDL_RWclose(file);
}

void loadData(std::vector< std::vector <TileManager::Tile> > &trackData)
{
  std::string name = "new.track";
  SDL_RWops* file = SDL_RWFromFile( name.c_str(), "r+b" );
  if(file==nullptr) { std::cout << "ERROR!!! CANNOT FIND FILE!!!" << std::endl; }

  int sizeInBytes = sizeof(TileManager::Tile);
  // number of struct
  std::cout << "SIZE OF TRACKDATA: " << sizeof(TileManager::Tile) << std::endl;
    std::cout << "SIZE OF TRACKDATA: " << sizeof(trackData[0][0]) << std::endl;
  int noOfStructs = 80;

  trackData.clear();
  // trackData.size() * trackData[0].size();
     //Load data
     int counter = 0;
     printf( "Reading file...!\n" );
     for(auto &mediator : trackData) {
       for(auto &track : mediator) {
         std::cout << "READING: " << counter << std::endl;
         counter++;
         SDL_RWread( file, &track, sizeInBytes, noOfStructs );
       }
     }

     //Close file handler
     SDL_RWclose( file );
 }

 //
 // if (rw == NULL) return NULL;
std::vector< std::vector <TileManager::Tile> > loader(){ //std::vector< std::vector <TileManager::Tile> > *trackData) {
     std::string name = "new.track";
     int x = 10;
     int y = 8;
     int sizeInBytes = sizeof(TileManager::Tile);
     SDL_RWops* file = SDL_RWFromFile( name.c_str(), "r+b" );
     std::vector< std::vector < TileManager::Tile > > loadedTiles;
     TileManager::Tile currentTile;
     std::vector< TileManager::Tile> loadedRows;
     int finished = 0;

     for(int i = 0; i < x; i ++) {
       loadedRows.clear();

       for(int j = 0; j < y; j++) {
         SDL_RWread(file, &currentTile, 1, sizeInBytes);

         // 80/sizeInBytes);

         std::cout << "From x: " << i << " y: " << j << std::endl;
         loadedRows.push_back(currentTile);
         std::cout << "Reading x:" << loadedRows.back().location.x << " y:" << loadedRows.back().location.y << std::endl;
         std::cout << "Moving on..." << std::endl;
       }
       std::cout << "loadedRows[1]:" << loadedRows[1].location.y << std::endl;
       std::cout << "Preparing to push back vector" << std::endl;
       loadedTiles.push_back(loadedRows);
       std::cout << "SUCCESS!!!" << std::endl;
       finished++;
     }
       SDL_RWclose(file);
     return loadedTiles;
   }


  //
  //    int sizeInBytes = sizeof(TileManager::Tile);
  //
  //    Sint64 res_size = SDL_RWsize(file);
  //    char* res = (char*)malloc(res_size + 1);
  //
  //    Sint64 nb_read_total = 0, nb_read = 1;
  //    // char* buf = res;
  //    TileManager::Tile temp;
  //
  // while (nb_read_total < res_size && nb_read != 0) {

  //  nb_read = SDL_RWread(file, &temp, sizeInBytes, 80);
    // SDL_Rect location;
    // SDL_Rect textureIndex;
    // // SDL_Texture *texture;
    // Tile(SDL_Rect where) {
    //   location = where;
    // }
    // *trackData -> left = temp.left;
    // *trackData -> right = temp.right;
    // *trackData -> up = temp.up;
    // *trackData -> down = temp.down;
    // *trackData -> hasRoad = temp.hasRoad;
    // *trackData -> isComplete = temp.isComplete;
    // trackData++;
    // nb_read_total += nb_read;
    // buf += nb_read;
  //}

         // if (nb_read_total != res_size) {
         //         free(res);
         //
         // }
         //
         // res[nb_read_total] = '\0';
        // return res;
 //}
 // void loadData(std::vector< std::vector <TileManager::Tile> > &trackData)
 // {
 //   std::string name = "new.track";
 //   SDL_RWops* file = SDL_RWFromFile( name.c_str(), "r+b" );
 //   if(file==nullptr) { std::cout << "ERROR!!! CANNOT FIND FILE!!!" << std::endl; }
 //
 //   int sizeInBytes = sizeof(TileManager::Tile);
 //   // number of struct
 //   std::cout << "SIZE OF TRACKDATA: " << sizeof(TileManager::Tile) << std::endl;
 //     std::cout << "SIZE OF TRACKDATA: " << sizeof(trackData[0][0]) << std::endl;
 //   int noOfStructs = 80;
 //
 //   trackData.clear();
 //   // trackData.size() * trackData[0].size();
 //      //Load data
 //      int counter = 0;
 //      printf( "Reading file...!\n" );
 //      for(auto &mediator : trackData) {
 //        for(auto &track : mediator) {
 //          std::cout << "READING: " << counter << std::endl;
 //          counter++;
 //          SDL_RWread( file, &track, sizeInBytes, noOfStructs );
 //        }
 //      }
 //
 //      //Close file handler
 //      SDL_RWclose( file );
 //  }
//
//     //Initialize data
//     for( int i = 0; i < TOTAL_DATA; ++i )
//     {
//         gData[ i ] = 0;
//         SDL_RWwrite( file, &gData[ i ], sizeof(Sint32), 1 );
//     }
//
//     //Close file handler
//     SDL_RWclose( file );
// }
// else
// {
//     printf( "Error: Unable to create file! SDL Error: %s\n", SDL_GetError() );
//     success = false;
// }
// }
//
// //File exists
// else
// {
//     //Load data
//     printf( "Reading file...!\n" );
//     for( int i = 0; i < TOTAL_DATA; ++i )
//     {
//         SDL_RWread( file, &gData[ i ], sizeof(Sint32), 1 );
//     }
//
//     //Close file handler
//     SDL_RWclose( file );
// }
