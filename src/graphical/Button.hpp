/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Button
*/

#pragma once

#include "Text.hpp"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <memory>
#include <string>

class Button {
public:
  Button(float x, float y, float w, float h, SDL_Renderer *renderer,
         const std::string &text, SDL_Color normalColor = {0, 0, 0, 0},
         SDL_Color hoverColor = {255, 255, 255, 255},
         SDL_Color normalTextColor = {255, 255, 255, 255},
         SDL_Color hoverTextColor = {0, 0, 0, 0}, const std::string &tag = "");

  Button(float x, float y, float w, float h, SDL_Renderer *renderer,
         const char *normalSpritePath, const char *hoverSpritePath,
         const char *_selectedSpritePath, const std::string &text,
         const std::string &tag = "");

  ~Button();

  bool isMouseOver() const;

  bool isClicked(float mouseX, float mouseY) const;

  void init();

  void drawButton();

  std::string getText() { return _text.getText(); };

  std::string getTag() const { return _tag; };

  void setPos(float x, float y);

  SDL_FRect *getRect() { return _rect; }

  void setSelected(bool selected) { _selected = selected; }

  void markTexturesDirty();

private:
  SDL_Renderer *_renderer;
  SDL_FRect *_rect;
  float _mouseX;
  float _mouseY;
  std::string _textButton;
  Text _text;
  std::string _tag;

  const char *_normalSpritePath;
  const char *_hoverSpritePath;
  const char *_selectedSpritePath;

  SDL_Color _normalColor;
  SDL_Color _hoverColor;
  SDL_Color _normalTextColor;
  SDL_Color _hoverTextColor;

  SDL_Texture *_normalTexture;
  SDL_Texture *_hoverTexture;
  SDL_Texture *_selectedTexture;

  bool _useTextures = false;

  bool _texturesDirty = false;

  bool _selected = false;
  SDL_FRect *_outlinerect;
};
