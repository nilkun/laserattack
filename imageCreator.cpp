
#include "imageCreator.h"

SDL_Texture* ImageCreator::getTexture(SDL_Renderer *renderer, const char* imageLocation) {

  SDL_Texture *texture;
  texture = NULL;

  SDL_Surface* loadImage = IMG_Load(imageLocation);

  texture = SDL_CreateTextureFromSurface(renderer, loadImage);

  SDL_FreeSurface(loadImage);

  return texture;
}

void ImageCreator::setProperties(SDL_Texture *texture, int *w, int *h, float *ratio) {
  SDL_QueryTexture(texture, NULL, NULL, w, h);
  *ratio = static_cast<float>(*h)/(*w);

}

SDL_Texture* ImageCreator::filledRectangle(SDL_Renderer *renderer) {
  SDL_Texture *texture;
  // SDL_Rect rectangle;
  // Create a 1 X 1 texture
  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 50, 50);
  SDL_SetRenderTarget(renderer, texture);
  SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
  SDL_RenderFillRect(renderer, NULL);
  SDL_SetRenderTarget(renderer, NULL);

  return texture;
}

SDL_Texture* ImageCreator::fromText(SDL_Renderer* renderer, const char* fontName, const char* text, int fontSize = 20) {
  // SIZE AND COLOR!!!

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

  TTF_Init();
  TTF_Font *font = TTF_OpenFont(fontName, fontSize);
  SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

  SDL_FreeSurface(surface);
    //kill init
    // kill font
  return texture;
  }

void ImageCreator::setColor(Uint8 red, Uint8 green, Uint8 blue) {
  color = {red, green, blue};
}
