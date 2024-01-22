#include <iostream>
#include <SDL2/SDL_syswm.h>

extern "C" void SetWindowRatio(void *window);

#include "utils/logging.h"

#include "Texture.hpp"

#include "render/RenderWindow.hpp"
#include "render/Camera.hpp"

#include "ui/Font.hpp"
#include "ui/Ui.hpp"
#include "ui/UiPanel.hpp"
#include "ui/UiRect.hpp"
#include "ui/UiText.hpp"

int main()
{
  RenderWindow *window = new RenderWindow("Game v0.0.1", 800, 600);

  Texture *texture = new Texture(window, "../assets/kitten.jpg");
  texture->setOpacity(0.5f);

  Camera *camera = new Camera(window);

  Font *font = new Font(window, "../assets/fonts/visitor.ttf", 24.f);
  font->setStyle(TTF_STYLE_BOLD);
  Font *pixel = new Font(window, "../assets/fonts/pixel.ttf", 24.f);
  pixel->setStyle(TTF_STYLE_NORMAL);
  Font *pixelTitle = new Font(window, "../assets/fonts/pixel.ttf", 36.f);
  pixelTitle->setStyle(TTF_STYLE_NORMAL);
  // pixelTitle->setOutline(1);

  Ui *ui = new Ui(window);
  UiPanel *debugPanel = new UiPanel(glm::vec2(12.f, 12.f), glm::vec2(240.0f, 100.0f), TOP_LEFT);
  UiText *fps = new UiText(pixel, glm::vec2(0.0f, 0.0f), glm::vec2(-48.0f, 100.0f), TOP_LEFT);
  fps->setText("FPS: 60");
  fps->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
  debugPanel->addChild(fps);

  UiRect *footer = new UiRect(glm::vec2(0.0f, 24.0f), glm::vec2(-48.0f, 100.0f), BOTTOM_CENTER, texture);
  UiText *title = new UiText(pixelTitle, glm::vec2(0.0f, 12.0f));
  title->setAnchor(TOP_CENTER);
  title->setText("Hello World!");
  title->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

  ui->addChild(title);
  ui->addChild(debugPanel);
  ui->addChild(footer);

  window->prepare();
  while (window->isOpen())
  {
    window->pollEvents();
    window->clear();

    fps->setText("FPS: " + std::to_string(static_cast<int>(window->getFps())) + " | Lifetime: " + std::to_string(static_cast<int>(window->getLifeTime() / 1000.0f)));
    ui->draw(window->getDeltaTime());

    window->draw();
  }

  delete window;

  return 0;
}