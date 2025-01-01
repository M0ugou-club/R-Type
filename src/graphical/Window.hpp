/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Window
*/

#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <cstddef>
#include "Utils.hpp"

class Window {
public:
  Window();
  ~Window();

  void init();

  bool checkingCloseWindow();

  void delay(int time);
  void destroyWindow();

  SDL_Texture *loadTexture(const char *path);

  void draw(SDL_Texture *texture, SDL_Rect rect);

  void render();

  void clear();

  void setBackground(SDL_Texture *texture);

  void drawBackground();

  keyType catchKey();

private:
  SDL_Window *_window;
  SDL_Renderer *_renderer;
  SDL_Event _event;
  SDL_Texture *_background;
};
