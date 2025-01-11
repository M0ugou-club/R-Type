/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Text
*/

#include "Text.hpp"

Text::Text(std::string text, int x, int y, int w, int h, SDL_Renderer *renderer,
           int size, const std::string &fontPath, SDL_Color color)
    : _text(text), _renderer(renderer), _color(color) {
  _rect.x = x;
  _rect.y = y;
  _rect.w = w;
  _rect.h = h;
  _font = TTF_OpenFont(fontPath.c_str(), size);
}

Text::~Text() {
  // if (_font) {
  //   std::cout << "destroying font" << std::endl;
  //   TTF_CloseFont(_font);
  //   _font = nullptr;
  // }
}

void Text::init() {
  if (!_font) {
    throw std::runtime_error("Font not loaded. Ensure TTF_OpenFont succeeded.");
  }
  SDL_Surface *surface =
      TTF_RenderText_Blended(_font, _text.c_str(), _text.length(), _color);
  if (!surface) {
    throw std::runtime_error(std::string("Failed to create text surface: ") +
                             SDL_GetError());
  }

  _texture = SDL_CreateTextureFromSurface(_renderer, surface);
  if (!_texture) {
    SDL_DestroySurface(surface);
    throw std::runtime_error(std::string("Failed to create texture: ") +
                             SDL_GetError());
  }

  _rect.w = surface->w;
  _rect.h = surface->h;

  SDL_DestroySurface(surface);
}

void Text::drawText() {
  SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);
  SDL_RenderTexture(_renderer, _texture, nullptr, &_rect);
}

void Text::destroyText() {
  SDL_DestroyTexture(_texture);
  if (_font) {
    TTF_CloseFont(_font);
    _font = nullptr;
  }
}

void Text::setColor(SDL_Color color) {
  if (_color.r == color.r && _color.g == color.g && _color.b == color.b &&
      _color.a == color.a) {
    return;
  }
  _color = color;

  if (_texture) {
    SDL_DestroyTexture(_texture);
    _texture = nullptr;
  }

  SDL_Surface *surface =
      TTF_RenderText_Blended(_font, (_text).c_str(), (_text).length(), _color);
  _texture = SDL_CreateTextureFromSurface(_renderer, surface);
  SDL_DestroySurface(surface);
}

std::string Text::getText() { return _text; }

void Text::setPos(int x, int y) {
  if (_rect.x == x && _rect.y == y) {
    return;
  }
  _rect.x = x;
  _rect.y = y;
  if (_texture) {
    SDL_DestroyTexture(_texture);
    _texture = nullptr;
  }
  SDL_Surface *surface =
      TTF_RenderText_Blended(_font, (_text).c_str(), (_text).length(), _color);
  _texture = SDL_CreateTextureFromSurface(_renderer, surface);
  SDL_DestroySurface(surface);
}

void Text::setText(std::string text) {
  _text = text;
  if (_texture) {
    SDL_DestroyTexture(_texture);
    _texture = nullptr;
  }

  SDL_Surface *surface =
      TTF_RenderText_Blended(_font, (_text).c_str(), (_text).length(), _color);
  _texture = SDL_CreateTextureFromSurface(_renderer, surface);
  SDL_DestroySurface(surface);
}