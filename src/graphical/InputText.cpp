/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** InputText
*/

#include "InputText.hpp"
#include <iostream>
#include <stdexcept>
#include <unordered_map>

InputText::InputText(float x, float y, float width, float height,
                     SDL_Renderer *renderer, const std::string &fontPath,
                     SDL_Color color, const std::string &tag,
                     const std::string &placeholder)
    : _x(x), _y(y), _width(width), _height(height), _renderer(renderer),
      _tag(tag), _isSelected(false), _placeholder(placeholder),
      _text(placeholder, x, y, width, height, renderer, 40, fontPath, color) {
  _rect = {static_cast<float>(x), static_cast<float>(y), width, height};
  _currentText = placeholder;
}

InputText::~InputText() {}

void InputText::init() { _text.init(); }

void InputText::draw() {
  if (_isSelected) {
    SDL_SetRenderDrawColor(_renderer, 37, 37, 37, 200);
  } else {
    SDL_SetRenderDrawColor(_renderer, 37, 37, 37, 70);
  }
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
  _text.setText(text);
}

const std::string &InputText::getTag() const { return _tag; }

std::string InputText::getNumber(keyType key) {
  static const std::unordered_map<keyType, std::string> keyMap = {
      {keyType::ZERO, "0"},
      {keyType::ONE, "1"},
      {keyType::TWO, "2"},
      {keyType::THREE, "3"},
      {keyType::FOUR, "4"},
      {keyType::FIVE, "5"},
      {keyType::SIX, "6"},
      {keyType::SEVEN, "7"},
      {keyType::EIGHT, "8"},
      {keyType::NINE, "9"},
      {keyType::PERIOD, "."},
      {keyType::UP, "Up"},
      {keyType::DOWN, "Down"},
      {keyType::LEFT, "Left"},
      {keyType::RIGHT, "Right"},
      {keyType::SPACE, "Space"},
      {keyType::ENTER, "Enter"},
      {keyType::ESCAPE, "Escape"},
      {keyType::BACKSPACE, "Backspace"},
      {keyType::A, "A"},
      {keyType::B, "B"},
      {keyType::C, "C"},
      {keyType::D, "D"},
      {keyType::E, "E"},
      {keyType::F, "F"},
      {keyType::G, "G"},
      {keyType::H, "H"},
      {keyType::I, "I"},
      {keyType::J, "J"},
      {keyType::K, "K"},
      {keyType::L, "L"},
      {keyType::M, "M"},
      {keyType::N, "N"},
      {keyType::O, "O"},
      {keyType::P, "P"},
      {keyType::Q, "Q"},
      {keyType::R, "R"},
      {keyType::S, "S"},
      {keyType::T, "T"},
      {keyType::U, "U"},
      {keyType::V, "V"},
      {keyType::W, "W"},
      {keyType::X, "X"},
      {keyType::Y, "Y"},
      {keyType::Z, "Z"},
      {keyType::NONE, ""}};

  auto it = keyMap.find(key);
  return it != keyMap.end() ? it->second : "";
}
