#pragma once

#include <functional>
#include <SDL2/SDL.h>

#include "UiPanel.hpp"
#include "../render/RenderWindow.hpp"

bool isPointInsideBBox(glm::vec2 point, glm::vec4 bbox)
{
  return (point.x >= bbox.x) &&
         (point.y >= bbox.y) &&
         (point.x < (bbox.x + bbox.z)) &&
         (point.y < (bbox.y + bbox.w));
}

class UiButton : public UiPanel
{
public:
  UiButton(glm::vec2 p_position, glm::vec2 p_size, UiPanelAnchor p_anchor = TOP_LEFT) : UiPanel(p_position, p_size, p_anchor){};
  ~UiButton(){};

  virtual void drawSelf(RenderWindow *p_window)
  {
    UiPanel::drawSelf(p_window);
  };

  virtual void update(RenderWindow *p_window, glm::vec2 p_ref_position, glm::vec2 p_ref_size)
  {
    UiPanel::update(p_window, p_ref_position, p_ref_size);

    bool is_hovered = isPointInsideBBox(p_window->getMousePos(), glm::vec4(m_screen_position, m_screen_size));

    Uint32 mouse_state = p_window->getMouseState();
    bool is_clicked = mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT);

    if (is_clicked && !m_is_clicked && is_hovered)
    {
      m_click_handler();
    }

    if (is_hovered && !m_is_hovered)
    {
      m_enter_handler();
    }
    else if (!is_hovered && m_is_hovered)
    {
      m_leave_handler();
    }

    m_is_hovered = is_hovered;
    m_is_clicked = is_clicked;
  }

  void onClick(std::function<void()> p_click_handler)
  {
    m_click_handler = p_click_handler;
  }

  void onEnter(std::function<void()> p_enter_handler)
  {
    m_enter_handler = p_enter_handler;
  }

  void onLeave(std::function<void()> leave_handler)
  {
    m_leave_handler = leave_handler;
  }

private:
  std::function<void()> m_click_handler = nullptr;
  std::function<void()> m_enter_handler = nullptr;
  std::function<void()> m_leave_handler = nullptr;

  bool m_is_hovered = false;
  bool m_is_clicked = false;
};