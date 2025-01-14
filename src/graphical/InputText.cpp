/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** InputText
*/

#include "InputText.hpp"
#include <iostream>
#include <stdexcept>

InputText::InputText(float x, float y, float width, float height,
                     SDL_Renderer *renderer, const std::string &fontPath,
                     SDL_Color color, const std::string &tag,
                     const std::string &placeholder)
    : _x(x), _y(y), _width(width), _height(height), _renderer(renderer),
      _tag(tag), _isSelected(false),
      _text(placeholder, x, y, width, height, renderer, 40, fontPath, color) {
  _rect = {static_cast<float>(x), static_cast<float>(y), width, height};
  _currentText = placeholder;
}

InputText::~InputText() {}

void InputText::init() { _text.init(); }

void InputText::draw() {
  SDL_SetRenderDrawColor(_renderer, 37, 37, 37, 70);
  SDL_RenderFillRect(_renderer, &_rect);

  _text.drawText();
}

void InputText::handleEvent(const SDL_Event &event) {
  if (event.type == SDL_EVENT_TEXT_INPUT && _isSelected) {
    _currentText += event.text.text;
    _text.setColor({255, 255, 255, 255});
    _text.setPos(static_cast<int>(_x + 5), static_cast<int>(_y + 5));
    _text.setText(_currentText);
  } else if (event.type == SDL_EVENT_KEY_DOWN && _isSelected) {
    if (event.key.key == SDL_SCANCODE_BACKSPACE && !_currentText.empty()) {
      _currentText.pop_back();
      _text.setText(_currentText);
    }
  }
}

bool InputText::isClicked(float mouseX, float mouseY) const {
  return mouseX >= _x && mouseX <= _x + _width && mouseY >= _y &&
         mouseY <= _y + _height;
}

void InputText::setSelected(bool selected) { _isSelected = selected; }

const std::string &InputText::getText() const { return _currentText; }

void InputText::setText(const std::string &text) {
  _currentText = text;
  std::cout << "text: " << text << std::endl;
  _text.setText(text);
}

const std::string &InputText::getTag() const { return _tag; }

std::string InputText::getNumber(keyType key) {
  switch (key) {
  case keyType::ZERO:
    return "0";
  case keyType::ONE:
    return "1";
  case keyType::TWO:
    return "2";
  case keyType::THREE:
    return "3";
  case keyType::FOUR:
    return "4";
  case keyType::FIVE:
    return "5";
  case keyType::SIX:
    return "6";
  case keyType::SEVEN:
    return "7";
  case keyType::EIGHT:
    return "8";
  case keyType::NINE:
    return "9";
  case keyType::PERIOD:
    return ".";
  default:
    return "";
  }
}
