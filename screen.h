#ifndef SCREEN_H_
#define SCREEN_H_


#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

enum SIZE_MODE { STRETCH, FIXED, ASPECT_BOUND_TO_X, ASPECT_BOUND_TO_Y, FIXED_X, FIXED_Y, AUTOSCALE };
// float getAspect(int a, int b) {
//   return (float) a / (float) b;
// };
class Screen {
private:
  int width;
  int height;
  int availablePixels;  // Number of available pixels (along y) after fixed blocks have been allocated
  SDL_DisplayMode mode;
  SDL_Window *m_window;
  SDL_Renderer *m_renderer;
  SDL_Texture *m_texture;
  const char* m_title;
  int screenMode = 1;


public:
    struct ViewPort {
      SDL_Rect dimensions;

    };
    struct Textures {
      SDL_Rect *viewPort;
    };

    struct Block {
      SDL_Rect sourceDimensions;  // Original size of texture
      SDL_Rect targetDimensions;       // Size of scaled block
      SDL_Texture *texture; // Pointer to texture, texture should be created elsewhere

      SIZE_MODE sizeMode;   // Set the size mode (fixed, stretch, etc.)

      Block(SDL_Rect sourceDimensions, SIZE_MODE sizeMode, float ratio, float aspect);
      void setTexture(SDL_Texture *texture);

      float ratioX;
      float ratioY;
      bool isLast = false;

      void rescale(int width, int height, int freeY);
    };





    std::vector<Block> blocks;
  Screen();
  Screen(const char* title, int width, int height);
  bool init();                                // RETURNS TRUE IF INITIALIZATION SUCCEEDED
  void setResolution(int width, int height);   // SETS THE RESOLUTION

  void getResolution() { }                    // RETURN X and Y

  void update();
  void clear();   //empty renderer
  void render();
  void close();                           // DESTROY AND EXIT
  SDL_Renderer* getRenderer();
  void toggleScreen();
  void resize();
  void draw();
//  Block* add(SDL_Rect sourceDimensions, float size, bool isFixed);
  Block* add(SDL_Rect sourceDimensions, SIZE_MODE sizeMode, float ratio, float aspect);
  Block* add(int x, int y, int w, int h, SIZE_MODE sizeMode, float ratio, float aspect);
  int getWidth() { return width; }
  int getHeight() { return height; }
  void rescale(); // RECALCULATE ALL SIZES;
  int fixedY;
  void calculateFreeArea();
  SDL_Window* getWindow() { return m_window; };

};

#endif
