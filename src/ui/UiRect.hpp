#pragma once

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

#include "UiPanel.hpp"
#include "../Texture.hpp"
#include "../render/RenderWindow.hpp"

class UiRect : public UiPanel
{
public:
  UiRect(glm::vec2 p_position, glm::vec2 p_size, UiPanelAnchor p_anchor = TOP_LEFT, glm::vec4 p_color = glm::vec4(glm::vec3(0.), 1.f)) : UiPanel(p_position, p_size, p_anchor), m_color(p_color){};
  UiRect(glm::vec2 p_position, glm::vec2 p_size, UiPanelAnchor p_anchor = TOP_LEFT, Texture *p_texture = nullptr) : UiPanel(p_position, p_size, p_anchor), m_texture(p_texture){};

  virtual void drawSelf(RenderWindow *p_window)
  {
    SDL_FRect rect;
    rect.x = m_screen_position.x;
    rect.y = m_screen_position.y;
    rect.w = m_screen_size.x;
    rect.h = m_screen_size.y;

    glm::vec4 bg_color = m_color * 255.0f;
    if (m_texture != nullptr)
    {
      SDL_RenderCopyF(p_window->getRenderer(), m_texture->getTexture(), NULL, &rect);
    }
    else
    {
      SDL_SetRenderDrawColor(p_window->getRenderer(), bg_color.r, bg_color.g, bg_color.b, bg_color.a);
      SDL_RenderFillRectF(p_window->getRenderer(), &rect);
    }
  };

  void setColor(glm::vec4 p_color)
  {
    m_color = p_color;
  };

private:
  glm::vec4 m_color;
  Texture *m_texture = nullptr;
};