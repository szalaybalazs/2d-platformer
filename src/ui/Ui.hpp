#pragma once

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>

#include "../render/RenderWindow.hpp"
#include "../utils/logging.h"
#include "./UiPanel.hpp"

/**
 * @brief UI class
 *
 * This class is responsible for drawing the UI
 * A UI component is always drawn on top of the game
 * and is not affected by the camera
 *
 * The size of the UI is always the same as the window size
 */
class Ui
{
public:
  Ui(RenderWindow *window) : m_window(window){};
  ~Ui(){};

  void addChild(UiPanel *p_child)
  {
    m_children.push_back(p_child);
  };

  void draw(float delta_time = 0.0f)
  {
    t_window_size = m_window->getWindowSize();
    t_mouse_pos = m_window->getMousePos();

    for (auto &child : m_children)
    {
      child->draw(m_window->getRenderer(), m_position, t_window_size);
    }
  };

  void setPosition(glm::vec2 p_position)
  {
    m_position = p_position;
  };

private:
  RenderWindow *m_window = nullptr;
  glm::vec2 m_position = glm::vec2(0.0f, 0.0f);

  glm::vec2 t_window_size = glm::vec2(0.0f, 0.0f);
  glm::vec2 t_mouse_pos = glm::vec2(0.0f, 0.0f);

  std::vector<UiPanel *> m_children;
};