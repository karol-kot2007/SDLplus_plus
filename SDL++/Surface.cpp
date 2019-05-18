#include "stdafx.h"
#include "Surface.h"

namespace SDL
{
  Surface::Surface()
  {
  }
  
  Surface::~Surface()
  {
    SDL_FreeSurface(surface);
  }

  void Surface::loadBMP(std::string path)
  {
    surface = SDL_LoadBMP(path.c_str());
    if (surface == NULL)
    {
      //printf("Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError());
    }
  }

}