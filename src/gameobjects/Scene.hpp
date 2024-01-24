#pragma once

#include <iostream>
#include <vector>
#include <glm/glm.hpp>

#include "../render/Camera.hpp"
#include "GameObject.hpp"

class Scene
{
public:
  Scene(Camera *p_camera) : m_camera(p_camera) {}
  virtual ~Scene() {}

  virtual void update(float deltaTime = 0.0f)
  {
    // todo: first update the camera
    // then update non-kinematic objects
    // then update kinematic objects

    float dt = float(deltaTime) / 1000.0f;
    for (int i = 0; i < m_gameObjects.size(); i++)
    {
      m_gameObjects[i]->update(this, dt);
    }
  }

  virtual void draw()
  {
    for (int i = 0; i < m_gameObjects.size(); i++)
    {
      m_gameObjects[i]->draw(m_camera);
    }
  }

  virtual void addGameObject(GameObject *p_gameObject)
  {
    m_gameObjects.push_back(p_gameObject);
  }

  virtual void removeGameObject(GameObject *p_gameObject)
  {
    for (int i = 0; i < m_gameObjects.size(); i++)
    {
      if (m_gameObjects[i] == p_gameObject)
      {
        m_gameObjects.erase(m_gameObjects.begin() + i);
        break;
      }
    }
  }

  virtual void clearGameObjects()
  {
    m_gameObjects.clear();
  }

  std::vector<GameObject *> *getGameObjects()
  {
    return &m_gameObjects;
  }

protected:
  std::vector<GameObject *> m_gameObjects;
  Camera *m_camera;
};