#pragma once

#include <iostream>
#include <glm/glm.hpp>

#include "RenderWindow.hpp"

const glm::vec2 DEFAULT_AXIS = glm::vec2(1.f, -1.f);

class Camera
{
public:
  Camera(RenderWindow *p_window) : m_window(p_window) {}
  ~Camera() {}

  void setPosition(glm::vec2 p_position)
  {
    m_position = p_position;
  }

  void setSize(glm::vec2 p_size)
  {
    m_size = p_size;
  }

  glm::vec2 getPosition()
  {
    return m_position;
  }

  glm::vec2 getSize()
  {
    return m_size;
  }

  void update(float deltaTime = 0.0f)
  {
    // for when the camera will follow the character, move on it's own
    // it probably should do that tho
  }

  glm::vec2 screenToWorldPosition(glm::vec2 p_screen_position)
  {
    glm::vec2 screen_size = m_window->getWindowSize();
    glm::vec2 screen_position_relative = (glm::vec2(p_screen_position.x, screen_size.y - p_screen_position.y) / screen_size) * 2.f - glm::vec2(1.0f);

    glm::vec2 world_position_relative = screen_position_relative * (m_size / 2.f);

    glm::vec2 world_position = world_position_relative + m_position;

    return world_position;
  }

  glm::vec2 worldToScreenPosition(glm::vec2 p_world_position)
  {
    glm::vec2 screen_size = m_window->getWindowSize();
    glm::vec2 camera_top_left = m_position - (m_size / 2.f) * glm::vec2(1.f, -1.f);

    return ((p_world_position - camera_top_left) / m_size) * screen_size * glm::vec2(1.f, -1.f);
  }

private:
  RenderWindow *m_window = nullptr;
  glm::vec2 m_position = glm::vec2(0.f, 0.f);

  // size of the screen in world units
  glm::vec2 m_size = glm::vec2(40.f, 22.5f);
};