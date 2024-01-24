#pragma once

#include <iostream>
#include <glm/glm.hpp>

#include "GameObject.hpp"

/*
 * @brief Get the overlap of 2 rectangles
 * @param p_rect1 The first rectangle
 * @param p_rect2 The second rectangle
 * @return The overlap of the 2 rectangles
 * Returns 0 if there is no overlap
 *
 * The bounds are in the format of:
 * x, y, width, height
 * where x and y are the bottom left corner of the rectangle
 */
glm::vec4 getOverlap(glm::vec4 p_rect1, glm::vec4 p_rect2)
{
  // Calculate overlap in the x-axis
  float x_overlap_point = std::max(p_rect1.x, p_rect2.x);
  float x_overlap_length = std::min(p_rect1.x + p_rect1.z, p_rect2.x + p_rect2.z) - x_overlap_point;

  // Apply sign based on relative side to rect1
  float x_overlap_length_signed = p_rect2.x <= p_rect1.x ? -std::abs(x_overlap_length) : std::abs(x_overlap_length);

  // Calculate overlap in the y-axis
  float y_overlap_point = std::max(p_rect1.y, p_rect2.y);
  float y_overlap_length = std::min(p_rect1.y + p_rect1.w, p_rect2.y + p_rect2.w) - y_overlap_point;

  // Apply sign based on relative side to rect1
  float y_overlap_length_signed = p_rect2.y <= p_rect1.y ? -std::abs(y_overlap_length) : std::abs(y_overlap_length);

  if (x_overlap_length < 0.0f || y_overlap_length < 0.0f)
  {
    // No overlap.
    return glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
  }
  else
  {
    // Overlapping rectangle (x, y, signed w, signed h).
    return glm::vec4(x_overlap_point, y_overlap_point, x_overlap_length_signed, y_overlap_length_signed);
  }
}

class BoxCollider : public GameObject
{
public:
  BoxCollider(glm::vec2 p_position, glm::vec2 p_size) : GameObject(p_position, p_size) {}
  ~BoxCollider() {}

  bool intersectsAABB(BoxCollider *p_other)
  {
    if (this->m_bounds.x<p_other->m_bounds.x + p_other->m_bounds.z &&this->m_bounds.x + this->m_bounds.z> p_other->m_bounds.x &&
        this->m_bounds.y<p_other->m_bounds.y + p_other->m_bounds.w &&this->m_bounds.y + this->m_bounds.w> p_other->m_bounds.y)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
};