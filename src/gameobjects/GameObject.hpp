#pragma once

#define DRAW_BOUNDS 1

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>

#include "../render/Camera.hpp"
#include "Scene.hpp"

class Scene;
class GameObject
{
public:
  GameObject(glm::vec2 p_position, glm::vec2 p_size) : m_position(p_position), m_size(p_size)
  {
    _updateBounds();
  };
  virtual ~GameObject(){};

  glm::vec2 getPosition()
  {
    return m_position;
  }

  glm::vec2 getSize()
  {
    return m_size;
  }

  glm::vec4 getBounds()
  {
    return m_bounds;
  }

  void setPosition(glm::vec2 p_position)
  {
    m_position = p_position;
    _updateBounds();
  }

  void setSize(glm::vec2 p_size)
  {
    m_size = p_size;
    _updateBounds();
  }

  void addChild(GameObject *p_child)
  {
    m_children.push_back(p_child);
  }

  void removeChild(GameObject *p_child)
  {
    for (int i = 0; i < m_children.size(); i++)
    {
      if (m_children[i] == p_child)
      {
        m_children.erase(m_children.begin() + i);
        break;
      }
    }
  }

  void clearChildren()
  {
    m_children.clear();
  }

  virtual void update(Scene *p_scene, float deltaTime)
  {
    for (int i = 0; i < m_children.size(); i++)
    {
      m_children[i]->update(p_scene, deltaTime);
    }

    _updateBounds();
  };

  virtual void draw(Camera *p_camera, glm::vec2 p_ref_position = glm::vec2(0.0f))
  {
    glm::vec4 screen_bounds = p_camera->worldToScreenBounds(m_bounds - (glm::vec4(p_ref_position, glm::vec2(0.0f))));

    for (int i = 0; i < m_children.size(); i++)
    {
      m_children[i]->draw(p_camera, m_position);
    }

#if DRAW_BOUNDS
    SDL_FRect rect = {
        screen_bounds.x,
        screen_bounds.y,
        screen_bounds.z,
        screen_bounds.w};

    SDL_SetRenderDrawColor(p_camera->getWindow()->getRenderer(), 255, 0, 0, 255);
    SDL_RenderDrawRectF(p_camera->getWindow()->getRenderer(), &rect);
#endif
  };

protected:
  glm::vec2 m_position;
  glm::vec2 m_size;
  glm::vec4 m_bounds;

  std::vector<GameObject *> m_children;

  void _updateBounds()
  {
    m_bounds = glm::vec4((m_position - m_size / 2.0f), m_size);
  }
};