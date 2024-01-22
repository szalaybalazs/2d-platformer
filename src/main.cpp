#include <iostream>

#include "utils/logging.h"

#include "render/RenderWindow.hpp"

#include "ui/Ui.hpp"
#include "ui/UiPanel.hpp"

int main()
{
  LOG("Hello World!");

  RenderWindow *window = new RenderWindow("Game v0.0.1", 800, 600);

  Ui *ui = new Ui(window);
  UiPanel *panel = new UiPanel(glm::vec2(0.0f, 0.0f), glm::vec2(100.0f, 100.0f), MIDDLE_CENTER);
  UiPanel *childPanel = new UiPanel(glm::vec2(0.0f), glm::vec2(-20.0f, 50.0f), MIDDLE_CENTER);

  UiPanel *footer = new UiPanel(glm::vec2(0.0f, 24.0f), glm::vec2(-48.0f, 100.0f), BOTTOM_CENTER);

  panel->addChild(childPanel);
  ui->addChild(panel);
  ui->addChild(footer);

  window->prepare();
  while (window->isOpen())
  {
    window->pollEvents();
    window->clear();

    ui->draw();

    std::cout << window->getDeltaTime() << "ms, w: " << window->getWindowSize().x << ", h: " << window->getWindowSize().y << ", x: " << window->getMousePos().x << ", y: " << window->getMousePos().y << std::endl;
    window->draw();
  }

  delete window;

  return 0;
}