#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>

class RenderWindow
{
public:
  RenderWindow(const char *p_title, int p_w, int p_h)
  {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
      std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
    }
    m_window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (m_window == nullptr)
    {
      std::cout << "Error creating window: " << SDL_GetError() << std::endl;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (m_renderer == nullptr)
    {
      std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
    }

    SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);

#ifdef __APPLE__
    // SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
#endif
  };

  ~RenderWindow()
  {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
  };

  void prepare()
  {
    SDL_PumpEvents();
  }

  /**
   * @brief Clear the renderer
   * Clear the renderer with the background color
   */
  void clear(glm::vec4 p_color = glm::vec4(0.4f, 0.4f, 0.4f, 1.0f))
  {
    glm::vec4 bg_color = p_color * 255.0f;

    SDL_RenderClear(m_renderer);
    SDL_SetRenderDrawColor(m_renderer, bg_color.r, bg_color.g, bg_color.b, bg_color.a);
    SDL_RenderClear(m_renderer);
  };

  /**
   * @brief Draw the current frame
   * Draw the content of the renderer to the screen
   */
  void draw()
  {
    SDL_RenderPresent(m_renderer);

    m_current_frame_time = SDL_GetTicks();
    if (m_last_frame_time > 0.0f)
    {
      m_delta_time = (float)(m_current_frame_time - m_last_frame_time);
    }
    m_last_frame_time = m_current_frame_time;
  };

  /**
   * @brief Poll events
   * Poll events and set the isOpen flag to false if the user wants to close the window
   */
  void pollEvents()
  {
    m_updateWindowState();
    while (SDL_PollEvent(&m_event) != 0)
    {
      if (m_event.type == SDL_QUIT)
      {
        m_isOpen = false;
      }
    }
  }

  /**
   * @brief Poll events
   * Poll events and set the isOpen flag to false if the user wants to close the window
   * @param lambda A lambda function that takes a SDL_Event as parameter
   * @example
   * window->pollEvents([](SDL_Event &event) {
   *  if (event.type == SDL_KEYDOWN)
   *  {
   *    // Do something
   *  }
   * });
   */
  void pollEvents(const std::function<void(SDL_Event *)> &lambda)
  {
    m_updateWindowState();
    while (SDL_PollEvent(&m_event) != 0)
    {
      if (m_event.type == SDL_QUIT)
      {
        m_isOpen = false;
      }
      lambda(&m_event);
    }
  }

  bool isOpen()
  {
    return m_isOpen;
  }

  /**
   * @brief Get the Delta Time object
   * Returns the time in seconds between the last two frames
   */
  float getDeltaTime()
  {
    return m_delta_time;
  }

  /**
   * @brief Get the Window Size object
   * Returns the size of the window
   */
  glm::vec2 getWindowSize()
  {
    return m_window_size;
  }

  /**
   * @brief Get the cursor position
   * Returns the position of the cursor in the window, in pixels, counted from the top left corner
   */
  glm::vec2 getMousePos()
  {
    return m_mouse_pos;
  }

  SDL_Renderer *getRenderer()
  {
    return m_renderer;
  }

private:
  SDL_Window *m_window;
  SDL_Renderer *m_renderer;
  SDL_Event m_event;

  bool m_isOpen = true;

  float m_current_frame_time = 0;
  float m_last_frame_time = 0;
  float m_delta_time = 0;
  Uint32 m_mouse_state = 0;

  glm::vec2 m_window_size;
  glm::vec2 m_mouse_pos;

  void m_updateWindowState()
  {
    int x, y;
    SDL_GetWindowSize(m_window, &x, &y);
    m_window_size = glm::vec2(x, y);
    m_mouse_state = SDL_GetMouseState(&x, &y);
    m_mouse_pos = glm::vec2(x, y);
  }
};