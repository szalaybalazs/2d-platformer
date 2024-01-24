#pragma once

#include <iostream>
#include <glm/glm.hpp>

#include "BoxCollider.hpp"

class Solid : public BoxCollider
{
public:
  Solid(glm::vec2 p_position, glm::vec2 p_size) : BoxCollider(p_position, p_size) {}
  ~Solid() {}
};