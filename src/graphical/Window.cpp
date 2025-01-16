/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Window
*/

#include "Window.hpp"
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

Window::Window() { _allowToInteract = false; }

Window::~Window() {}

void Window::init() {
  SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
    exit(84);
  }

  if (!SDL_Init(SDL_INIT_AUDIO)) {
    std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
    exit(84);
  }

  if (Mix_Init(MIX_INIT_MP3) == 0) {
    std::cerr << "Mix_Init Error: " << SDL_GetError() << std::endl;
    exit(84);
  }

  if (!Mix_OpenAudio(0, NULL)) {
    std::cerr << "Mix_OpenAudio Error: " << SDL_GetError() << std::endl;
    exit(84);
  }

  if (!TTF_Init()) {
    std::cerr << "TTF_Init Error: " << SDL_GetError() << std::endl;
    exit(84);
  }
  SDL_DisplayID displayID = SDL_GetPrimaryDisplay();
  const SDL_DisplayMode *currentMode = SDL_GetCurrentDisplayMode(displayID);

  // int windowWidth = static_cast<int>(currentMode->w * 0.9);
  // int windowHeight = static_cast<int>(currentMode->h * 0.8);

  int windowWidth = 1200;
  int windowHeight = 800;

  _windowWidth = windowWidth;
  _windowHeight = windowHeight;

  _window = SDL_CreateWindow("R-Type", windowWidth, windowHeight, 0);
  if (!_window) {
    std::cerr << "Erreur lors de la création de la fenêtre : " << SDL_GetError()
              << std::endl;
    SDL_Quit();
    exit(84);
  }

  _renderer = SDL_CreateRenderer(_window, nullptr);
  if (!_renderer) {
    std::cerr << "Erreur lors de la création du renderer : " << SDL_GetError()
              << std::endl;
    destroyWindow();
    exit(84);
  }

  addSound("../src/graphical/assets/sounds/shot.mp3", BULLET_SOUND, 15);
  addSound("../src/graphical/assets/sounds/shot.mp3", BULLET_SOUND, 15);
  addSound("../src/graphical/assets/sounds/un.mp3", WAVE1, 45);
  addSound("../src/graphical/assets/sounds/deux.mp3", WAVE2, 45);
  addSound("../src/graphical/assets/sounds/trois.mp3", WAVE3, 45);
  addSound("../src/graphical/assets/sounds/nouvelleVague.mp3", NEWWAVE, 45);
  addSound("../src/graphical/assets/sounds/shot.mp3", BULLET_SOUND, 15);
  addSound("../src/graphical/assets/sounds/endless.mp3", ENDLESS_MUSIC, 50);
  addSound("../src/graphical/assets/sounds/Michou_croute_et_Elsa_2.mp3",
           MICHOU_ET_ELSA_2, 100);
}

void Window::destroyWindow() {
  SDL_DestroyWindow(_window);
  Mix_CloseAudio();
  TTF_Quit();
  SDL_Quit();
  Mix_Quit();
}

void Window::delay(int time) { SDL_Delay(time); }

eventType Window::updateEvents() {
  while (SDL_PollEvent(&_event)) {
    if (_event.type == SDL_EVENT_QUIT) {
      return CLOSE_WINDOW;
    }
    if (_event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
      return MOUSE_CLICK;
    }
  }
  return NO_EVENT;
}

void Window::draw(SDL_Texture *texture, SDL_Rect rect) {
  SDL_FRect rec = {static_cast<float>(rect.x), static_cast<float>(rect.y),
                   static_cast<float>(rect.w), static_cast<float>(rect.h)};
  SDL_RenderTexture(_renderer, texture, nullptr, &rec);
}

void Window::drawText() {
  for (auto &text : _texts) {
    text.drawText();
  }
}

void Window::drawButton() {
  for (auto &button : _buttons) {
    button.drawButton();
  }
}

void Window::drawButton(const std::string &tag) {
  for (auto &button : _buttons) {
    if (button.getTag() == tag) {
      button.drawButton();
    }
  }
}

void Window::drawDropdown() {
  for (auto &dropdown : _dropdowns) {
    dropdown->draw();
  }
}

void Window::addText(std::string text, int x, int y, int w, int h, int size,
                     std::string fontPath, SDL_Color color) {
  _texts.emplace_back(text, x, y, w, h, _renderer, size, fontPath, color);
  _texts.back().init();
}

void Window::addButton(float x, float y, float w, float h,
                       const std::string &text, const std::string &tag,
                       SDL_Color normalColor, SDL_Color hoverColor,
                       SDL_Color normalTextColor, SDL_Color hoverTextColor) {
  Button myButton = Button(x, y, w, h, _renderer, text, normalColor, hoverColor,
                           normalTextColor, hoverTextColor, tag);
  myButton.init();
  _buttons.push_back(myButton);
}

void Window::addDropdown(float x, float y, float width, float height,
                         std::vector<std::string> options, std::string tag) {
  _dropdowns.push_back(
      std::make_unique<Dropdown>(x, y, width, height, options, _renderer, tag));
  _dropdowns.back()->init();
}

void Window::render() { SDL_RenderPresent(_renderer); }

void Window::clear() { SDL_RenderClear(_renderer); }

SDL_Texture *Window::loadTexture(const char *path) {
  return IMG_LoadTexture(_renderer, path);
}

void Window::setBackground(SDL_Texture *texture) {
  _background = texture;
  _background2 = texture;
  ;
}

void Window::moveBackground() {
  if (!_background)
    return;

  float bgWidth = 0.f;
  float bgHeight = 0.f;
  SDL_GetTextureSize(_background, &bgWidth, &bgHeight);

  _bgOffset -= _bgScrollSpeed;

  if (_bgOffset <= -bgWidth)
    _bgOffset = 0.f;
}

void Window::drawBackground() {
  if (!_background)
    return;

  float bgWidth = 0.f;
  float bgHeight = 0.f;
  SDL_GetTextureSize(_background, &bgWidth, &bgHeight);

  if (!_isBackgroundScrolling) {
    SDL_RenderTexture(_renderer, _background, nullptr, nullptr);
  } else {
    SDL_FRect destRect1 = {_bgOffset, 0.f, bgWidth, bgHeight};
    SDL_RenderTexture(_renderer, _background, nullptr, &destRect1);

    SDL_FRect destRect2 = {_bgOffset + bgWidth, 0.f, bgWidth, bgHeight};
    SDL_RenderTexture(_renderer, _background, nullptr, &destRect2);
  }
}

keyType Window::catchKeyOnce() {
  static std::vector<bool> prevKeyState(512, false);
  const bool *keyState = SDL_GetKeyboardState(NULL);

  std::vector<std::pair<SDL_Scancode, keyType>> keys = {
      {SDL_SCANCODE_UP, UP},         {SDL_SCANCODE_RIGHT, RIGHT},
      {SDL_SCANCODE_DOWN, DOWN},     {SDL_SCANCODE_LEFT, LEFT},
      {SDL_SCANCODE_ESCAPE, ESCAPE}, {SDL_SCANCODE_SPACE, SPACE}};

  for (const auto &key : keys) {
    SDL_Scancode scancode = key.first;
    keyType action = key.second;

    if (keyState[scancode] && !prevKeyState[scancode]) {
      prevKeyState[scancode] = true;
      return action;
    }

    if (!keyState[scancode]) {
      prevKeyState[scancode] = false;
    }
  }

  return NONE;
}

std::vector<keyType> Window::catchKey() {
  const bool *keyState = SDL_GetKeyboardState(NULL);
  std::vector<keyType> keys;
  static const std::unordered_map<SDL_Scancode, keyType> keyMap = {
      {SDL_SCANCODE_ESCAPE, ESCAPE},
      {SDL_SCANCODE_SPACE, SPACE},
      {SDL_SCANCODE_RETURN, ENTER},
      {SDL_SCANCODE_BACKSPACE, BACKSPACE},
      {SDL_SCANCODE_PERIOD, PERIOD},
      {SDL_SCANCODE_1, ONE},
      {SDL_SCANCODE_2, TWO},
      {SDL_SCANCODE_3, THREE},
      {SDL_SCANCODE_4, FOUR},
      {SDL_SCANCODE_5, FIVE},
      {SDL_SCANCODE_6, SIX},
      {SDL_SCANCODE_7, SEVEN},
      {SDL_SCANCODE_8, EIGHT},
      {SDL_SCANCODE_9, NINE},
      {SDL_SCANCODE_0, ZERO},
      {SDL_SCANCODE_A, Q},
      {SDL_SCANCODE_B, B},
      {SDL_SCANCODE_C, C},
      {SDL_SCANCODE_D, D},
      {SDL_SCANCODE_E, E},
      {SDL_SCANCODE_F, F},
      {SDL_SCANCODE_G, G},
      {SDL_SCANCODE_H, H},
      {SDL_SCANCODE_I, I},
      {SDL_SCANCODE_J, J},
      {SDL_SCANCODE_K, K},
      {SDL_SCANCODE_L, L},
      {SDL_SCANCODE_SEMICOLON, M},
      {SDL_SCANCODE_N, N},
      {SDL_SCANCODE_O, O},
      {SDL_SCANCODE_P, P},
      {SDL_SCANCODE_Q, A},
      {SDL_SCANCODE_R, R},
      {SDL_SCANCODE_S, S},
      {SDL_SCANCODE_T, T},
      {SDL_SCANCODE_U, U},
      {SDL_SCANCODE_V, V},
      {SDL_SCANCODE_W, Z},
      {SDL_SCANCODE_X, X},
      {SDL_SCANCODE_Y, Y},
      {SDL_SCANCODE_Z, W}};

  for (const auto &[scancode, key] : keyMap) {
    if (keyState[scancode]) {
      keys.push_back(key);
    }
  }

  if (keys.empty())
    keys.push_back(NONE);
  return keys;
}

std::vector<keyType> Window::catchMovementKey() {
  const bool *keyState = SDL_GetKeyboardState(NULL);
  std::vector<keyType> keys;

  if (keyState[SDL_SCANCODE_UP])
    keys.push_back(UP);
  if (keyState[SDL_SCANCODE_RIGHT])
    keys.push_back(RIGHT);
  if (keyState[SDL_SCANCODE_DOWN])
    keys.push_back(DOWN);
  if (keyState[SDL_SCANCODE_LEFT])
    keys.push_back(LEFT);

  if (keys.empty())
    keys.push_back(NONE);
  return keys;
}

SDL_Event Window::catchEvent() { return _event; }

void Window::createMenuPipe() {
  SDL_Renderer *renderer = getRenderer();
  SDL_FRect pipeRect;

  pipeRect.x = 0.02 * _windowWidth;
  pipeRect.y = 0.2 * _windowHeight;
  pipeRect.w = 5;
  pipeRect.h = 400;

  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderFillRect(renderer, &pipeRect);
}

int Window::getMouseState(float *x, float *y) {
  return SDL_GetMouseState(x, y);
}

void Window::deleteTexts() {
  for (auto &text : _texts) {
    text.destroyText();
  }
  _texts.clear();
}

void Window::deleteButtons(const std::string &tag) {
  if (tag.empty()) {
    _buttons.clear();
  } else {
    _buttons.erase(std::remove_if(_buttons.begin(), _buttons.end(),
                                  [&tag](const Button &button) {
                                    return button.getTag() == tag;
                                  }),
                   _buttons.end());
  }
}

void Window::deleteText(std::string text) {
  for (auto &t : _texts) {
    if (t.getText() == text) {
      t.destroyText();
      _texts.erase(
          std::remove_if(_texts.begin(), _texts.end(),
                         [&text](Text &t) { return t.getText() == text; }),
          _texts.end());
    }
  }
}

void Window::setTextPos(std::string text, int x, int y) {
  for (auto &t : _texts) {
    if (t.getText() == text) {
      t.setPos(x, y);
    }
  }
}

void Window::playSound(soundType type, int loop) {
  for (auto &sound : _sounds) {
    if (sound->getSoundType() == type) {
      sound->playSound(loop);
    }
  }
}

void Window::addSound(std::string soundPath, soundType type, int volume) {
  _sounds.push_back(std::make_unique<Sound>(soundPath, type, volume));
}

void Window::stopAllSound() {
  for (auto &sound : _sounds) {
    sound->stopSound();
  }
}

void Window::stopSound(soundType type) {
  for (auto &sound : _sounds) {
    if (sound->getSoundType() == type) {
      sound->stopSound();
    }
  }
}

SDL_Texture *Window::loadText(std::string text, int size, std::string fontPath,
                              SDL_Color color) {
  TTF_Font *font = TTF_OpenFont(fontPath.c_str(), size);

  SDL_Surface *surface =
      TTF_RenderText_Blended(font, text.c_str(), text.length(), color);

  SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, surface);

  SDL_DestroySurface(surface);
  return texture;
}

void Window::drawRect(SDL_FRect rect, SDL_Color color) {
  SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
  SDL_RenderFillRect(_renderer, &rect);
}

void Window::deletedropdowns(const std::string &tag) {
  if (tag.empty()) {
    _dropdowns.clear();
  } else {
    _dropdowns.erase(std::remove_if(_dropdowns.begin(), _dropdowns.end(),
                                    [&tag](const std::unique_ptr<Dropdown> &d) {
                                      return d->getTag() == tag;
                                    }),
                     _dropdowns.end());
  }
}

void Window::deleteInputTexts(const std::string &tag) {
  if (tag.empty()) {
    _inputTexts.clear();
  } else {
    _inputTexts.erase(std::remove_if(_inputTexts.begin(), _inputTexts.end(),
                                     [&tag](const InputText &input) {
                                       return input.getTag() == tag;
                                     }),
                      _inputTexts.end());
  }
}

void Window::addInputText(float x, float y, float width, float height,
                          const std::string &fontPath, SDL_Color color,
                          const std::string &tag,
                          const std::string &placeholder) {
  InputText input = InputText(x, y, width, height, _renderer, fontPath, color,
                              tag, placeholder);
  input.init();

  _inputTexts.push_back(input);
}

void Window::drawInputTexts() {
  for (auto &input : _inputTexts) {
    input.draw();
  }
}

void Window::addButton(float x, float y, float w, float h,
                       const char *normalSpritePath,
                       const char *hoverSpritePath,
                       const char *selectedSpritePath, const std::string &text,
                       const std::string &tag) {
  _buttons.emplace_back(x, y, w, h, _renderer, normalSpritePath,
                        hoverSpritePath, selectedSpritePath, text, tag);
  _buttons.back().init();
}

void Window::setButtonTextureDirty(const std::string &tag) {
  for (auto &button : _buttons) {
    if (button.getTag() == tag) {
      button.markTexturesDirty();
    }
  }
}

std::string Window::getInputTextValue(const std::string &placeholder) {
  for (auto &input : _inputTexts) {
    if (input.getPlaceholder() == placeholder) {
      return input.getText();
    }
  }
  return "";
}

void Window::setSelectedButton(std::string text) {
  for (auto &button : _buttons) {
    if (button.getText() == text) {
      std::cout << text << std::endl;
      button.setSelected(true);
    }
  }
}

void Window::unSelectButton(std::string tag) {
  for (auto &button : _buttons) {
    if (button.getText() == tag) {
      std::cout << tag << std::endl;
      button.setSelected(false);
    }
  }
}
