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
    glm::vec4 this_bounds = this->getBounds();
    glm::vec4 other_bounds = p_other->getBounds();

    if (this_bounds.x < other_bounds.x + other_bounds.z && this_bounds.x + this_bounds.z > other_bounds.x &&
        this_bounds.y < other_bounds.y + other_bounds.w && this_bounds.y + this_bounds.w > other_bounds.y)
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  // using the Liang-Barsky algorithm
  bool intersectsLine(glm::vec2 p_start, glm::vec2 p_end)
  {
    float t0 = 0.0;
    float t1 = 1.0;
    glm::vec2 delta = p_end - p_start;

    glm::vec4 bounds = getBounds();
    std::array<float, 4> p = {-delta.x, delta.x, -delta.y, delta.y};
    std::array<float, 4> q = {p_start.x - bounds.x, bounds.x + bounds.z - p_start.x, p_start.y - bounds.y, bounds.y + bounds.w - p_start.y};

    for (int i = 0; i < 4; i++)
    {
      if (p[i] == 0.0f && q[i] < 0.0f)
        return false;
      if (p[i] < 0.0f)
      {
        float t = q[i] / p[i];
        if (t > t1)
          return false;
        else if (t > t0)
          t0 = t;
      }
      else if (p[i] > 0.0f)
      {
        float t = q[i] / p[i];
        if (t < t0)
          return false;
        else if (t < t1)
          t1 = t;
      }
    }

    return true;
  }
};