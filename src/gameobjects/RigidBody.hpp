/*
 * RigidBody.hpp
 * Basic rigid body physics
 * The basic implementation of a physics rigid body
 * the code is pretty barebone; there is no true inertia or friction
 * but it is a good starting point
 *
 * The collision detection is pretty buggy
 * however there is a basic phase-through check, the body can still jump through objects
 * These edge cases should be fixed in the future
 */

#pragma once

#define GRAVITY 9.81f
#define MAX_VELOCITY 100.f

#define DRAW_FORCES 1

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>

#include "BoxCollider.hpp"
#include "GameObject.hpp"
#include "../render/Camera.hpp"

class Scene;

class RigidBody : public BoxCollider
{
public:
  RigidBody(glm::vec2 p_position, glm::vec2 p_size) : BoxCollider(p_position, p_size) {}
  ~RigidBody() {}

  virtual void update(Scene *p_scene, float deltaTime = 0.0f) override
  {
    // if the delta time is 0, we don't want to update the rigid body
    // We can assume that there were no changes in the scene
    if (deltaTime == 0.0f)
    {
      return;
    }

    m_prev_position = m_position;
    m_acceleration -= glm::vec2(0.0f, GRAVITY);
    m_velocity += m_acceleration * deltaTime;
    m_position += m_velocity * deltaTime;

    m_acceleration = glm::vec2(0.f, 0.f);

    BoxCollider::update(p_scene, deltaTime);

    _calculateCollisions(p_scene, deltaTime);
  }

  virtual void draw(Camera *p_camera, glm::vec2 p_ref_position = glm::vec2(0.0f)) override
  {
    BoxCollider::draw(p_camera, p_ref_position);

#if DRAW_FORCES
    p_camera->getWindow()->drawLine(p_camera->worldToScreenPosition(m_position), p_camera->worldToScreenPosition(m_position + m_velocity), glm::vec3(0.f, 1.f, 0.f));
    p_camera->getWindow()->drawLine(p_camera->worldToScreenPosition(m_position), p_camera->worldToScreenPosition(m_position + m_acceleration), glm::vec3(0.f, 1.f, 0.f));
#endif
  }

  void applyForce(glm::vec2 p_force)
  {
    m_acceleration += p_force / m_mass;
  }

  void setMass(float p_mass)
  {
    m_mass = p_mass;
  }

  float getMass()
  {
    return m_mass;
  }

  void setVelocity(glm::vec2 p_velocity)
  {
    m_velocity = p_velocity;
  }

  glm::vec2 getVelocity()
  {
    return m_velocity;
  }

  void setAcceleration(glm::vec2 p_acceleration)
  {
    m_acceleration = p_acceleration;
  }

  glm::vec2 getAcceleration()
  {
    return m_acceleration;
  }

protected:
  glm::vec2 m_prev_position = glm::vec2(0.f, 0.f);
  glm::vec2 m_velocity = glm::vec2(0.f, 0.f);
  glm::vec2 m_acceleration = glm::vec2(0.f, 0.f);
  float m_mass = 1.f;

  void _calculateCollisions(Scene *p_scene, float deltaTime)
  {
    std::vector<GameObject *> *gameobjects = p_scene->getGameObjects();

    for (GameObject *obj : *gameobjects)
    {
      BoxCollider *collider = dynamic_cast<BoxCollider *>(obj);

      if (collider != nullptr && collider != this)
      {

        if (collider->intersectsAABB(this))
        {
          // std::cout << "Collision detected" << std::endl;
          // std::cout << "--> Position: " << m_position.x << ", " << m_position.y << std::endl;
          // std::cout << "--> Other Position: " << collider->getPosition().x << ", " << collider->getPosition().y << std::endl;

          glm::vec4 overlap = getOverlap(getBounds(), collider->getBounds());

          if (std::abs(overlap.z) < std::abs(overlap.w))
          {
            m_position.x -= overlap.z;
            m_velocity.x = 0.0f;
          }
          else
          {
            m_position.y -= overlap.w;
            m_velocity.y = 0.0f;
          }
        }

        // checking if the object phased through the other object
        // only checking the center positions for now. In the future may need to connect all 4 corners and check if any of them intersect
        if (collider->intersectsLine(m_prev_position, m_position))
        {
          glm::vec2 direction = glm::normalize(m_position - m_prev_position);

          // since there is no easy way to calculate the intersection point, we can just clamp the position based on the direction and the bounds of the other object
          glm::vec4 other_bounds = collider->getBounds();
          if (direction.x > 0.0f)
          {
            m_position.x = other_bounds.x - m_size.x / 2.0f;
          }
          else if (direction.x < 0.0f)
          {
            m_position.x = other_bounds.x + other_bounds.z + m_size.x / 2.0f;
          }
          else if (direction.y > 0.0f)
          {
            m_position.y = other_bounds.y - m_size.y / 2.0f;
          }
          else if (direction.y < 0.0f)
          {
            m_position.y = other_bounds.y + other_bounds.w + m_size.y / 2.0f;
          }
        }
      }
    }
  }
};