/*
** EPITECH PROJECT, 2024
** RType
** File description:
** Draw
*/

#include <SDL3/SDL.h>

#ifndef DRAW_HPP
#define DRAW_HPP

struct Draw {
  SDL_Rect rect;
  SDL_Color color;
  SDL_Texture *texture;

  Draw(SDL_Color col, SDL_Rect size, SDL_Texture *tex = nullptr)
      : rect(size), color(col), texture(tex) {}
};

#endif // DRAW_HPP
