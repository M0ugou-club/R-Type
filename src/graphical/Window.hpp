/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Window
*/

#pragma once

#include "Button.hpp"
#include "Dropdown.hpp"
#include "InputText.hpp"
#include "Text.hpp"
#include "Utils.hpp"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <cstddef>
#include <memory>
#include <vector>

class Window {
public:
  Window();
  ~Window();

  void init();

  eventType updateEvents();

  void delay(int time);
  void destroyWindow();

  SDL_Texture *loadTexture(const char *path);

  void draw(SDL_Texture *texture, SDL_Rect rect);

  void drawText();

  void drawButton();

  void drawButton(const std::string &tag);

  void drawDropdown();

  void addText(std::string text, int x, int y, int w, int h, int size,
               std::string fontPath, SDL_Color color);

  void addButton(float x, float y, float w, float h, const std::string &text,
                 const std::string &tag = "",
                 SDL_Color normalColor = {0, 0, 0, 0},
                 SDL_Color hoverColor = {255, 255, 255, 255},
                 SDL_Color normalTextColor = {255, 255, 255, 255},
                 SDL_Color hoverTextColor = {0, 0, 0, 0});

  void addButton(float x, float y, float w, float h,
                 const char *normalSpritePath, const char *hoverSpritePath,
                 const char *selectedSpritePath, const std::string &text,
                 const std::string &tag = "");

  void addDropdown(float x, float y, float width, float height,
                   std::vector<std::string> options, std::string tag);

  const std::vector<std::unique_ptr<Dropdown>> &getDropdowns() const {
    return _dropdowns;
  }

  std::vector<Button> getButtons() { return _buttons; }

  void render();

  void clear();

  void setBackground(SDL_Texture *texture);

  void drawBackground();

  std::vector<keyType> catchKey();

  std::vector<keyType> catchMovementKey();

  keyType catchKeyOnce();

  SDL_Event catchEvent();

  SDL_Renderer *getRenderer() { return _renderer; }

  void createMenuPipe();

  int getMouseState(float *x, float *y);

  void deleteTexts();

  void deleteButtons(const std::string &tag = "");

  void deleteText(std::string text);

  int getNumberText() { return _texts.size(); }

  void setTextPos(std::string text, int x, int y);

  void setAllowToInteract(bool allow) { _allowToInteract = allow; }

  bool getAllowToInteract() { return _allowToInteract; }

  void addInputText(float x, float y, float width, float height,
                    const std::string &fontPath, SDL_Color color,
                    const std::string &tag, const std::string &placeholder);

  void startTextInput();

  void stopTextInput();

  void drawInputTexts();

  void deleteInputTexts(const std::string &tag = "");

  void deletedropdowns(const std::string &tag = "");

  void handleInputTextEvent(float mouseX, float mouseY, eventType event);

  void setButtonTextureDirty(const std::string &tag = "");

  std::vector<InputText> &getInputTexts() { return _inputTexts; }

  std::string getInputTextValue(const std::string &placeholder);

  void setWindowSize(int width, int height);

  int getWindowWidth() { return _windowWidth; }

  int getWindowHeight() { return _windowHeight; }

  void setSelectedButton(std::string text);

  void unSelectButton(std::string tag);

private:
  SDL_Window *_window;
  SDL_Renderer *_renderer;
  SDL_Event _event;
  SDL_Texture *_background;
  std::vector<Text> _texts;
  std::vector<Button> _buttons;
  std::vector<std::unique_ptr<Dropdown>> _dropdowns;
  std::vector<InputText> _inputTexts;
  bool _allowToInteract;
  int _windowWidth;
  int _windowHeight;
};
