#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <cmath>

#include "../render/RenderWindow.hpp"

class Font
{
public:
  Font(RenderWindow *window, const char *p_file_path, float p_size = 24.f) : m_size(p_size), m_window(window)
  {
    loadFromFile(p_file_path, p_size);
  };
  ~Font()
  {
    TTF_CloseFont(m_font);
  };

  void loadFromFile(const char *p_file_path, float p_size = 24.f)
  {
    m_font = TTF_OpenFont(p_file_path, p_size);
    if (m_font == nullptr)
    {
      std::cout << "TTF_OpenFont Error: " << SDL_GetError() << std::endl;
    }
  };

  void setStyle(int p_style)
  {
    TTF_SetFontStyle(m_font, p_style);
  };

  TTF_Font *getFont()
  {
    return m_font;
  };

  RenderWindow *getWindow()
  {
    return m_window;
  }

protected:
  float m_size;
  TTF_Font *m_font = nullptr;
  RenderWindow *m_window = nullptr;
};