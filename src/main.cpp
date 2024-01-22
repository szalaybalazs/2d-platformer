#include <iostream>

#include "utils/logging.h"

#include "RenderWindow.hpp"

int main()
{
  LOG("Hello World!");

  RenderWindow *window = new RenderWindow("Game v0.0.1", 800, 600);

  window->prepare();
  while (window->isOpen())
  {
    window->pollEvents();
    window->clear();

    std::cout << window->getDeltaTime() << std::endl;
    window->draw();
  }

  delete window;

  return 0;
}