#pragma once

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

#include "../render/RenderWindow.hpp"

#define DRAW_BOUNDS 0

enum UiPanelAnchor
{
  TOP_LEFT,
  TOP_CENTER,
  TOP_RIGHT,
  MIDDLE_LEFT,
  MIDDLE_CENTER,
  MIDDLE_RIGHT,
  BOTTOM_LEFT,
  BOTTOM_CENTER,
  BOTTOM_RIGHT
};

class UiPanel
{
public:
  UiPanel(glm::vec2 p_position, glm::vec2 p_size, UiPanelAnchor p_anchor = TOP_LEFT) : m_position(p_position), m_size(p_size), m_anchor(p_anchor){};
  ~UiPanel(){};

  void addChild(UiPanel *p_child)
  {
    m_children.push_back(p_child);
  };

  void setPosition(glm::vec2 p_position)
  {
    m_position = p_position;
  };

  void setSize(glm::vec2 p_size)
  {
    m_size = p_size;
  };

  void setAnchor(UiPanelAnchor p_anchor)
  {
    m_anchor = p_anchor;
  };

  virtual void update(RenderWindow *p_window, glm::vec2 p_ref_position, glm::vec2 p_ref_size)
  {
    m_screen_size.x = m_size.x == INFINITY ? p_ref_size.x : m_size.x < 0 ? p_ref_size.x + m_size.x
                                                                         : m_size.x;
    m_screen_size.y = m_size.y == INFINITY ? p_ref_size.y : m_size.y < 0 ? p_ref_size.y + m_size.y
                                                                         : m_size.y;

    m_screen_position = p_ref_position + m_position;
    if (m_anchor == BOTTOM_LEFT || m_anchor == BOTTOM_CENTER || m_anchor == BOTTOM_RIGHT)
    {
      m_screen_position.y = p_ref_position.y + p_ref_size.y - m_position.y - m_screen_size.y;
    }
    if (m_anchor == MIDDLE_LEFT || m_anchor == MIDDLE_CENTER || m_anchor == MIDDLE_RIGHT)
    {
      m_screen_position.y = p_ref_position.y + (p_ref_size.y / 2.0f) - (m_screen_size.y / 2.0f);
    }
    if (m_anchor == TOP_CENTER || m_anchor == MIDDLE_CENTER || m_anchor == BOTTOM_CENTER)
    {
      m_screen_position.x = p_ref_position.x + (p_ref_size.x / 2.0f) - (m_screen_size.x / 2.0f);
    }
    if (m_anchor == TOP_RIGHT || m_anchor == MIDDLE_RIGHT || m_anchor == BOTTOM_RIGHT)
    {
      m_screen_position.x = p_ref_position.x + p_ref_size.x - m_position.x - m_screen_size.x;
    }

    for (auto &child : m_children)
    {
      child->update(p_window, m_screen_position, m_screen_size);
    }
  }

  virtual void drawSelf(RenderWindow *p_window)
  {
#if DRAW_BOUNDS
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_FRect rect = {m_screen_position.x, m_screen_position.y, m_screen_size.x, m_screen_size.y};
    SDL_RenderDrawRectF(renderer, &rect);
#endif
  };

  virtual void draw(RenderWindow *p_window)
  {
    drawSelf(p_window);

    for (auto &child : m_children)
    {
      child->draw(p_window);
    }
  };

protected:
  glm::vec2 m_position = glm::vec2(0.0f, 0.0f);
  glm::vec2 m_size = glm::vec2(0.0f, 0.0f);

  glm::vec2 m_screen_position = glm::vec2(0.0f, 0.0f);
  glm::vec2 m_screen_size = glm::vec2(0.0f, 0.0f);

  UiPanelAnchor m_anchor = TOP_LEFT;

  std::vector<UiPanel *> m_children;
};