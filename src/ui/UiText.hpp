#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

#include "UiPanel.hpp"
#include "Font.hpp"
#include "../render/RenderWindow.hpp"

class UiText : public UiPanel
{
public:
  UiText(Font *p_font, glm::vec2 p_position, glm::vec2 p_size = glm::vec2(INFINITY), UiPanelAnchor p_anchor = TOP_LEFT, glm::vec4 p_color = glm::vec4(glm::vec3(0.), 1.f), std::string p_text = "Hello Worold!") : UiPanel(p_position, p_size, p_anchor), m_font(p_font), m_color(p_color)
  {
    setText(p_text);
  };

  void setText(std::string p_text)
  {
    m_text = p_text;

    _updateTexture();
  };

  void setFontSize(int p_font_size)
  {
    _updateTexture();
  };

  void setColor(glm::vec4 p_color)
  {
    m_color = p_color;

    _updateTexture();
  };

  virtual void drawSelf(RenderWindow *p_window)
  {
    SDL_FRect rect;
    rect.x = m_screen_position.x;
    rect.y = m_screen_position.y;
    rect.w = m_screen_size.x;
    rect.h = m_screen_size.y;

    SDL_RenderCopyF(p_window->getRenderer(), m_texture, NULL, &rect);
  };

private:
  Font *m_font;
  glm::vec4 m_color;
  std::string m_text = "";
  float m_font_size = 24.f;

  SDL_Texture *m_texture;
  SDL_Surface *m_surface;

  glm::vec2 m_text_size;

  void _updateTexture()
  {
    SDL_DestroyTexture(m_texture);

    glm::vec4 _color = m_color * 255.0f;
    SDL_Color color = {(Uint8)(_color.r), (Uint8)(_color.g), (Uint8)(_color.b), (Uint8)(_color.a)};

    m_surface = TTF_RenderText_Solid(m_font->getFont(), m_text.c_str(), color);
    m_texture = SDL_CreateTextureFromSurface(m_font->getWindow()->getRenderer(), m_surface);

    m_text_size = glm::vec2(m_surface->w, m_surface->h);

    m_size = m_text_size;

    SDL_FreeSurface(m_surface);
  }
};