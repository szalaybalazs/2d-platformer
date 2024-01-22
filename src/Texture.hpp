#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <iostream>
#include <string>
#include <cmath>

#include "./render/RenderWindow.hpp"

class Texture
{
public:
  Texture(RenderWindow *window) : m_window(window){};
  Texture(RenderWindow *window, const char *file_path) : m_window(window)
  {
    loadFromFile(file_path);
  };

  ~Texture()
  {
    SDL_DestroyTexture(m_texture);
  };

  void loadFromFile(const char *file_path)
  {
    m_texture = IMG_LoadTexture(m_window->getRenderer(), file_path);
    SDL_SetTextureBlendMode(m_texture, SDL_BLENDMODE_BLEND);

    if (m_texture == nullptr)
    {
      std::cout << "IMG_LoadTexture Error: " << SDL_GetError() << std::endl;
    }
  }

  glm::vec2 getSize()
  {
    int w, h;
    SDL_QueryTexture(m_texture, NULL, NULL, &w, &h);
    return glm::vec2(w, h);
  }

  void setOpacity(float p_opacity)
  {
    m_opacity = p_opacity;
    if (SDL_SetTextureAlphaMod(m_texture, p_opacity * 255) != 0)
    {
      std::cout << "SDL_SetTextureAlphaMod Error: " << SDL_GetError() << std::endl;
    }
  }

  SDL_Texture *getTexture()
  {
    return m_texture;
  }

protected:
  SDL_Texture *m_texture;
  RenderWindow *m_window;

  float m_opacity = 1.0f;
};