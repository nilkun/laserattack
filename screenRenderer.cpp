#include "screen.h"
#include <iostream> //debugging
#include <SDL2/SDL_image.h>

Screen::Screen():
  m_window(NULL), m_renderer(NULL), m_texture(NULL), m_title("NILKUN SCREEN HANDLER 0.2") {
    //nativeResolutionX = 100;
    //nativeResolutionY = 100;

    // windowSize = 100; // Point to size of window for easy reference
    availablePixels = 100;  // Number of available pixels (along y) after fixed blocks have been allocated
    // blocks.add();
  }

Screen::Screen(const char *title, int width, int height):
  m_window(NULL), m_renderer(NULL), m_texture(NULL),
  m_title(title), width(width), height(height) {
    // set screen size and title
    //nativeResolutionX = 100;
    //nativeResolutionY = 100;
    // windowSize = 100; // Point to size of window for easy reference
    availablePixels = 100;  // Number of available pixels (along y) after fixed blocks have been allocated
    // blocks.add();
  }

bool Screen::init() {
  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    return false;
  }

  m_window =
    SDL_CreateWindow( m_title,
                      SDL_WINDOWPOS_UNDEFINED,
                      SDL_WINDOWPOS_UNDEFINED,
                      width,
                      height,
                      SDL_WINDOW_SHOWN);

                      // CANNOT HANDLE RIGHT NOW | SDL_WINDOW_RESIZABLE);
  if(m_window == NULL) {
    SDL_Quit();
    return false;
  }

  m_renderer =  SDL_CreateRenderer(m_window, -1,
                SDL_RENDERER_PRESENTVSYNC);
  m_texture =  SDL_CreateTexture(
                          m_renderer,
                          SDL_PIXELFORMAT_RGBA8888,
                          SDL_TEXTUREACCESS_STATIC,
                          width,
                          height);

  if(m_renderer == NULL) {
    SDL_DestroyWindow(m_window);
    SDL_Quit();
    return false;
  }
  if(m_texture == NULL) {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
    return false;
  }
  TTF_Init();
  SDL_GetDesktopDisplayMode(0, &mode);
  return true;
}

void Screen::clear() {
  SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 0); // SET SCREEN TO RED
  SDL_RenderClear(m_renderer);
  }

void Screen::render() {
  SDL_RenderPresent(m_renderer);
}
SDL_Renderer* Screen::getRenderer() {
  return m_renderer;
}

void Screen::close() {
  SDL_DestroyRenderer(m_renderer);
  SDL_DestroyTexture(m_texture);
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}

void Screen::toggleScreen() {
  switch(screenMode) {
    case 1:
      SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN);
      screenMode++;
      break;
    case 2:
      SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN_DESKTOP);
      screenMode++;
      break;
    case 3:
      SDL_SetWindowFullscreen(m_window, 0);
      screenMode=1;
      break;
  }


}

void Screen::resize() {
  //if(x < 1) x = 1;
  //if(y < 1) y = 1;
  //SDL_GetWindowSize(m_window, &width, &height);
  SDL_GetRendererOutputSize(m_renderer, &width, &height);
  // SDL_GetRendererOutputSize(m_renderer, &width, &height);
  // std::cout << "SDL_GetRendererOutputSize: " << width << " " << height;
  // SDL_GetWindowSize(m_window, &width, &height);
  // std::cout << "SDL_GetGetWindowSize: " << width << " " << height;
  // SDL_GL_GetDrawableSize(m_window, &width, &height);
  // std::cout << "SDL_GL_GetDrawableSize: " << width << " " << height;
}

void Screen::Block::setTexture(SDL_Texture *texture) {
  this -> texture = texture;
}
