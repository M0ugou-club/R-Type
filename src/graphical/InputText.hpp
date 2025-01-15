/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** InputText
*/

#pragma once

#include "Text.hpp"
#include "Utils.hpp"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

class InputText {
public:
  InputText(float x, float y, float width, float height, SDL_Renderer *renderer,
            const std::string &fontPath, SDL_Color color,
            const std::string &tag, const std::string &placeholder);
  ~InputText();

  void init();
  void draw();
  void handleEvent(const SDL_Event &event);
  bool isClicked(float mouseX, float mouseY) const;
  void setSelected(bool selected);
  const std::string &getText() const;
  void setText(const std::string &text);
  const std::string &getTag() const;
  const std::string &getPlaceholder() { return _placeholder; };
  bool isSelected() const { return _isSelected; };
  std::string getNumber(keyType key);

private:
  float _x, _y, _width, _height;
  SDL_FRect _rect;
  bool _isSelected;
  std::string _tag;
  std::string _currentText;
  SDL_Renderer *_renderer;
  Text _text;
  std::string _placeholder;
};
