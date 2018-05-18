#include "screen.h"
#include <iostream>

void Screen::draw() {
  // Renders the whole texture
  for(Block block : blocks) {

    SDL_RenderCopy(m_renderer, block.texture, NULL, &block.targetDimensions);
  }
  // DRAW SOMETHING
}
Screen::Block::Block(SDL_Rect sourceDimensions, SIZE_MODE sizeMode, float ratioX, float ratioY) :
    sourceDimensions(sourceDimensions), sizeMode(sizeMode), ratioX(ratioX), ratioY(ratioY)
{
  targetDimensions = sourceDimensions;
}

// Screen::Block::Block(SDL_Rect sourceDimensions, float size, bool isFixed) :
//     sourceDimensions(sourceDimensions), size(size), isFixed(isFixed)
// {
//   hScale = size;
//   targetDimensions = sourceDimensions;
// }
// void Screen::Block::setScale(int x, int y, int w, int h)
// {
//   scale.x=x;
//   scale.y = y;
//   scale.w = w;
//   scale.h=h;
// }

// Screen::Block* Screen::add(SDL_Rect sourceDimensions, float size, bool isFixed) {
//   Block adding(sourceDimensions, size, isFixed);
//   blocks.push_back(adding);
//   return &blocks.back();
// }

Screen::Block* Screen::add(SDL_Rect sourceDimensions, SIZE_MODE sizeMode, float ratioX, float ratioY) {
  Block adding(sourceDimensions, sizeMode, ratioX, ratioY);
  blocks.push_back(adding);
  return &blocks.back();
}

Screen::Block* Screen::add(int x, int y, int w, int h, SIZE_MODE sizeMode, float ratioX, float ratioY) {
  SDL_Rect sourceDimensions = { x, y, w, h };
  Block adding(sourceDimensions, sizeMode, ratioX, ratioY);
  blocks.push_back(adding);
  return &blocks.back();
}


void Screen::rescale() {
  int xCoordinate = 0;
  int yCoordinate = 0;
  for(Block& block: blocks) {
    block.targetDimensions.x = xCoordinate;
    block.targetDimensions.y = yCoordinate;
    block.rescale(width, height, fixedY);
    xCoordinate += block.targetDimensions.w;
    if (block.isLast) {
      yCoordinate += block.targetDimensions.h;
      xCoordinate = 0;
    }
  }
}
void Screen::calculateFreeArea() {
  bool found = false;
  fixedY = 0;
  for(Block& block: blocks) {
    if(!found) {
      if(block.sizeMode == FIXED || block.sizeMode == FIXED_Y) {
        fixedY += block.sourceDimensions.h;
        found = true;
      }
    }
    if (block.isLast) found = false;
  }
}
void Screen::Block::rescale(int width, int height, int fixedY) {
  int freeY = height - fixedY;
  switch(sizeMode) {
    case FIXED:
      // DO NOTHING!
      break;
    case ASPECT_BOUND_TO_X:
      // resize x THEN resize y
      // ratioX ratioY
      /*
        should add x and y ???
      */
      // targetDimensions.x = (width * ratioX);
      // targetDimensions.y = (targetDimensions.y * ratioY);
      targetDimensions.w = (width * ratioY);
      targetDimensions.h = (targetDimensions.w * ratioY);
      break;
    case ASPECT_BOUND_TO_Y:
      targetDimensions.h = (freeY * ratioY);
      targetDimensions.w = (targetDimensions.h / ratioX);
      break;
    case STRETCH:
      targetDimensions.w = (width * ratioX);
      targetDimensions.h = (freeY * ratioY);
      break;
    case FIXED_X:
      break;
    case FIXED_Y:
      targetDimensions.w = width - targetDimensions.x;
      break;
    case AUTOSCALE:
      targetDimensions.h = freeY * ratioY;
      targetDimensions.w = targetDimensions.h / ratioX;
      if(targetDimensions.w > width) {
        targetDimensions.w = (width);
        targetDimensions.h = (targetDimensions.w * ratioX);
      }


    //   break;
      // aspect // aspect ratio x / y or y / x depending on mode.
      // ratio // portion of screen
      // case ASPECT_BOUND_TO_X:
      //   ratio = sourceDimensions.y / sourceDimensions.x;
      //   break;
      // case ASPECT_BOUND_TO_X:
      //   ratio = sourceDimensions.x / sourceDimensions.y;
      //   break;
  }
}
