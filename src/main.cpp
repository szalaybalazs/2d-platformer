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
#include "ui/UiButton.hpp"

#include "gameobjects/Scene.hpp"
#include "gameobjects/GameObject.hpp"
#include "gameobjects/BoxCollider.hpp"
#include "gameobjects/Solid.hpp"
#include "gameobjects/RigidBody.hpp"

int main()
{
  // glm::vec4 overlap = getOverlap(glm::vec4(2, 0, 3, 2), glm::vec4(0, 1, 3, 2));

  // std::cout << "Overlap: " << overlap.x << ", " << overlap.y << ", " << overlap.z << ", " << overlap.w << std::endl;
  // return 0;

  RenderWindow *window = new RenderWindow("Game v0.0.1", 1280, 720);

  Texture *texture = new Texture(window, "../assets/kitten.jpg");
  texture->setOpacity(0.5f);

  Camera *camera = new Camera(window);

  Font *font = new Font(window, "../assets/fonts/visitor.ttf", 24.f);
  font->setStyle(TTF_STYLE_BOLD);
  Font *pixel = new Font(window, "../assets/fonts/pixel.ttf", 24.f);
  // pixel->setStyle(TTF_STYLE_NORMAL);
  Font *pixelTitle = new Font(window, "../assets/fonts/pixel.ttf", 36.f);
  // pixelTitle->setStyle(TTF_STYLE_NORMAL);
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

  UiButton *button = new UiButton(glm::vec2(12.0f), glm::vec2(120.f, 48.f), TOP_RIGHT);
  UiRect *buttonRect = new UiRect(glm::vec2(0.0f), glm::vec2(INFINITY), TOP_RIGHT, glm::vec4(1.1f, 1.0f, 0.0f, 1.0f));
  UiText *buttonText = new UiText(pixel, glm::vec2(0.0f), glm::vec2(INFINITY), MIDDLE_CENTER);
  buttonText->setText("Hello World!");

  button->addChild(buttonRect);
  button->addChild(buttonText);

  button->onEnter([buttonRect]()
                  { 
                    std::cout << "Mouse entered" << std::endl;
                    buttonRect->setColor(glm::vec4(1.0, 0.0, 0.0, 1.0f)); });
  button->onLeave([buttonRect]()
                  { std::cout << "Mouse left" << std::endl;
                    buttonRect->setColor(glm::vec4(1.1f, 1.0f, 0.0f, 1.0f)); });
  button->onClick([]()
                  { std::cout << "Mouse Click" << std::endl; });

  ui->addChild(title);
  ui->addChild(debugPanel);
  // Remove footer for now
  // ui->addChild(footer);
  ui->addChild(button);

  Scene *scene = new Scene(camera);

  GameObject *go = new GameObject(glm::vec2(0.0f), glm::vec2(1.0f));
  GameObject *child = new GameObject(glm::vec2(0.0f, 0.5f), glm::vec2(0.5f));
  go->addChild(child);
  scene->addGameObject(go);

  Solid *floor = new Solid(glm::vec2(0.0f, -8.75f), glm::vec2(36.0f, 1.0f));
  scene->addGameObject(floor);

  BoxCollider *cube = new BoxCollider(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f));
  scene->addGameObject(cube);

  RigidBody *rb = new RigidBody(glm::vec2(0.0f, 2.0f), glm::vec2(1.0f));
  scene->addGameObject(rb);
  rb->setVelocity(glm::vec2(5.0f, 10.0f));
  // rb->setAcceleration(glm::vec2(1000.0f, 0.0f));

  window->prepare();
  while (window->isOpen())
  {
    window->pollEvents();
    window->clear();

    cube->setPosition(camera->screenToWorldPosition(window->getMousePos()));

    scene->update(window->getDeltaTime());

    scene->draw();

    fps->setText(std::to_string(cube->intersectsAABB(floor)) + " | FPS: " + std::to_string(static_cast<int>(window->getFps())) + " | Lifetime: " + std::to_string(static_cast<int>(window->getLifeTime() / 1000.0f)));
    ui->draw(window->getDeltaTime());

    window->draw();
  }

  delete window;

  return 0;
}