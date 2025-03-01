/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Window
*/

#include "Window.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

Window::Window() { _allowToInteract = false; }

Window::~Window() {}

void Window::init() {
  SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
    exit(84);
  }

  if (!SDL_Init(SDL_INIT_CAMERA)) {
    std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
    exit(84);
  }

  if (!SDL_Init(SDL_INIT_AUDIO)) {
    std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
  }

  if (Mix_Init(MIX_INIT_MP3) == 0) {
    std::cerr << "Mix_Init Error: " << SDL_GetError() << std::endl;
  }

  if (!Mix_OpenAudio(0, NULL)) {
    std::cerr << "Mix_OpenAudio Error: " << SDL_GetError() << std::endl;
  }

  if (!TTF_Init()) {
    std::cerr << "TTF_Init Error: " << SDL_GetError() << std::endl;
    exit(84);
  }
  SDL_DisplayID displayID = SDL_GetPrimaryDisplay();
  const SDL_DisplayMode *currentMode = SDL_GetCurrentDisplayMode(displayID);

  _windowWidth = 1200;
  _windowHeight = 800;

  _window = SDL_CreateWindow("R-Type", _windowWidth, _windowHeight, 0);
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

  _spell = loadTexture("../src/graphical/assets/freezeSpell.png");
  _spellDisable = loadTexture("../src/graphical/assets/freezeSpellDisable.png");
  _freezeOverlay = loadTexture("../src/graphical/assets/freezeOverlay.png");
  _deathBackground = loadTexture("../src/graphical/assets/deathBackground.png");
  _winBackground = loadTexture("../src/graphical/assets/winBackground.png");
  _death = false;
  _win = false;
  _rectCam = {1040, 0, 160, 120};

  int cameraCount = 0;
  SDL_CameraID *cameraIDs = SDL_GetCameras(&cameraCount);

  if (!cameraIDs || cameraCount == 0) {
    std::cerr << "No available cameras found!" << std::endl;
  }

  SDL_CameraID cameraID = cameraIDs[0];
  _camera = SDL_OpenCamera(cameraID, NULL);
  if (!_camera) {
    std::cerr << "SDL_OpenCamera Error: " << SDL_GetError() << std::endl;
  }

  addSound("../src/graphical/assets/sounds/shot.mp3", BULLET_SOUND, 5);
  addSound("../src/graphical/assets/sounds/un.mp3", WAVE1, 45);
  addSound("../src/graphical/assets/sounds/deux.mp3", WAVE2, 45);
  addSound("../src/graphical/assets/sounds/trois.mp3", WAVE3, 45);
  addSound("../src/graphical/assets/sounds/nouvelleVague.mp3", NEWWAVE, 45);
  addSound("../src/graphical/assets/sounds/shot.mp3", BULLET_SOUND, 15);
  addSound("../src/graphical/assets/sounds/endless.mp3", ENDLESS_MUSIC, 70);
  addSound("../src/graphical/assets/sounds/Michou_croute_et_Elsa_2.mp3",
           MICHOU_ET_ELSA_2, 70);
  addSound("../src/graphical/assets/sounds/Michou_Elsa_remix_winterzuuko.mp3",
           MICHOU_REMIX_WINTERZUUKO, 70);
  addSound("../src/graphical/assets/sounds/hit.mp3", HURT, 50);
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
    if (_event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
      return MOUSE_RELEASE;
    }
    if (_event.type == SDL_EVENT_KEY_DOWN) {
      SDL_Keymod modState = SDL_GetModState();
      char keycode = static_cast<char>(_event.key.key);
      if ((modState & SDL_KMOD_SHIFT) || (modState & SDL_KMOD_CAPS))
        keycode = toupper(keycode);
      updateTextInput(_event.key.scancode, keycode);
      return KEY_DOWN;
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
  for (auto &t : _texts) {
    if (t.getText() == text && text != "Nickname") {
      return;
    }
  }
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
      {SDL_SCANCODE_UP, UP},
      {SDL_SCANCODE_RIGHT, RIGHT},
      {SDL_SCANCODE_DOWN, DOWN},
      {SDL_SCANCODE_LEFT, LEFT},
      {SDL_SCANCODE_ESCAPE, ESCAPE},
      {SDL_SCANCODE_SPACE, SPACE},
      {SDL_SCANCODE_C, C}};

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

  if (keyState[SDL_SCANCODE_ESCAPE])
    keys.push_back(ESCAPE);
  if (keyState[SDL_SCANCODE_SPACE])
    keys.push_back(SPACE);
  if (keyState[SDL_SCANCODE_F])
    keys.push_back(F);
  if (keyState[SDL_SCANCODE_C])
    keys.push_back(C);
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

SDL_Event &Window::catchEvent() { return _event; }

void Window::createMenuPipe() {
  SDL_Renderer *renderer = getRenderer();
  SDL_FRect pipeRect;

  pipeRect.x = 45;
  pipeRect.y = 275;
  pipeRect.w = 5;
  pipeRect.h = 400;

  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor(renderer, 37, 37, 37, 70);
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

void Window::setTextContent(std::string text, std::string content) {
  for (auto &t : _texts) {
    if (t.getText() == text) {
      t.setText(content);
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

bool Window::isSoundFinished(soundType type) {
  for (auto &sound : _sounds) {
    if (sound->getSoundType() == type) {
      return sound->isFinished();
    }
  }
  return false;
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

void Window::drawSpell() {
  SDL_FRect spellRect = {550, 675, 100, 100};
  if (_spellIsEnable)
    SDL_RenderTexture(_renderer, _spell, nullptr, &spellRect);
  else
    SDL_RenderTexture(_renderer, _spellDisable, nullptr, &spellRect);
}

void Window::changeSpellStatus(bool enable) { _spellIsEnable = enable; }

bool &Window::getSpellEnable() { return _spellIsEnable; }

void Window::drawFreezeOverlay() {
  SDL_FRect freezeRect = {0, 0, 1200, 800};
  if (_freezeIsEnable)
    SDL_RenderTexture(_renderer, _freezeOverlay, nullptr, &freezeRect);
}

void Window::changeFreezeStatus(bool enable) { _freezeIsEnable = enable; }

bool &Window::getFreezeEnable() { return _freezeIsEnable; }

void Window::addTextInput(std::string text, int x, int y, int size,
                          int backgroundW) {
  _textInputs.push_back(
      std::make_unique<TextInput>(text, size, x, y, _renderer, backgroundW));
}

void Window::drawTextInput() {
  for (auto &textInput : _textInputs) {
    textInput->drawTextInput(_renderer);
  }
}

void Window::updateTextInput(SDL_Scancode scancode, SDL_Keycode keycode) {
  for (auto &textInput : _textInputs) {
    textInput->updateTextInput(scancode, keycode);
  }
}

void Window::selectTextInput(eventType event) {
  for (auto &textInput : _textInputs) {
    bool resp = textInput->selectTextInput(event);
    if (resp) {
      for (auto &otherTextInput : _textInputs) {
        if (otherTextInput != textInput) {
          otherTextInput->setIsSelected(false);
        }
      }
      textInput->setIsSelected(true);
      break;
    }
  }
}

void Window::setIsVisible(int menu, bool isVisible) {
  _textInputs[menu]->setIsVisible(isVisible);
}

std::string Window::getTextInput(int menu) {
  return _textInputs[menu]->getTextInput();
}

void Window::setDeath(bool death) { _death = death; }

void Window::drawDeathBackground() {
  if (_death) {
    SDL_FRect deathRect = {0, 0, 1200, 800};
    SDL_RenderTexture(_renderer, _deathBackground, nullptr, &deathRect);
  }
}

void Window::setWin(bool win) { _win = win; }

bool Window::getWin() { return _win; }

void Window::drawWinBackground() {
  if (_win) {
    SDL_FRect winRect = {0, 0, 1200, 800};
    SDL_RenderTexture(_renderer, _winBackground, nullptr, &winRect);
  }
}

void Window::displayCameraFeed() {
  if (!_isCameraFeed)
    return;
  if (!_camera) {
    std::cerr << "Error: Camera not initialized!" << std::endl;
    return;
  }

  int permission = SDL_GetCameraPermissionState(_camera);
  if (permission == 0) {
    std::cerr << "Waiting for camera permission..." << std::endl;
    return;
  }
  if (permission == -1) {
    std::cerr << "Camera access denied!" << std::endl;
    return;
  }

  SDL_Surface *surfaceCamera = SDL_AcquireCameraFrame(_camera, NULL);
  if (!surfaceCamera) {

    SDL_RenderTexture(_renderer, _textureCamera, NULL, &_rectCam);
    SDL_SetRenderDrawColor(_renderer, 0, 255, 0, 255);
    SDL_RenderRect(_renderer, &_rectCam);
    return;
  }

  static bool logOnce = true;
  if (logOnce) {
    std::cout << "Camera Frame: " << surfaceCamera->w << "x" << surfaceCamera->h
              << " Format: " << SDL_GetPixelFormatName(surfaceCamera->format)
              << std::endl;
    logOnce = false;
  }

  static int frameDropCount = 0;
  if (frameDropCount < 10) {
    frameDropCount++;
    SDL_ReleaseCameraFrame(_camera, surfaceCamera);
    return;
  }

  if (!_textureCamera || surfaceCamera->w != _textureCamWidth ||
      surfaceCamera->h != _textureCamHeight) {
    if (_textureCamera) {
      SDL_DestroyTexture(_textureCamera);
    }
    _textureCamera = SDL_CreateTexture(_renderer, surfaceCamera->format,
                                       SDL_TEXTUREACCESS_STREAMING,
                                       surfaceCamera->w, surfaceCamera->h);
    if (!_textureCamera) {
      std::cerr << "Error: Failed to create camera texture: " << SDL_GetError()
                << std::endl;
      SDL_ReleaseCameraFrame(_camera, surfaceCamera);
      return;
    }

    _textureCamWidth = surfaceCamera->w;
    _textureCamHeight = surfaceCamera->h;
  }

  SDL_UpdateTexture(_textureCamera, NULL, surfaceCamera->pixels,
                    surfaceCamera->pitch);

  SDL_RenderTexture(_renderer, _textureCamera, NULL, &_rectCam);
  SDL_SetRenderDrawColor(_renderer, 0, 255, 0, 255);
  SDL_RenderRect(_renderer, &_rectCam);
  SDL_ReleaseCameraFrame(_camera, surfaceCamera);
}
void Window::createCutscene(std::string soundPath, std::string texturePath,
                            int x, int y, int width, int height) {
  _cutscenes.push_back(
      Cutscene(_renderer, soundPath, texturePath, x, y, width, height));
}

void Window::playCutscene() {
  for (auto &cutscene : _cutscenes) {
    cutscene.playCutscene();
  }
}

void Window::setPlayingCutscene() {
  for (auto &cutscene : _cutscenes) {
    cutscene.setIsPlaying();
  }
}

void Window::stopCutScenes() {
  for (auto &cutscene : _cutscenes) {
    cutscene.stopCutscene();
  }
}

void Window::initFireAnimation(bool is1V1) {
  FireAnimation fireAnimation(_renderer, is1V1);

  if (is1V1) {
    _fireAnimations1V1.push_back(fireAnimation);
  } else {
    _fireAnimations.push_back(fireAnimation);
  }
}

void Window::drawFireAnimation(float x, float y) {
  for (auto &fireAnimation : _fireAnimations) {
    fireAnimation.drawFireAnimation(x, y);
  }
}

void Window::drawFireAnimation1V1(float x, float y) {
  for (auto &fireAnimation : _fireAnimations1V1) {
    fireAnimation.drawFireAnimation(x, y);
  }
}

void Window::destroyFireAnimation() {
  for (auto &fireAnimation : _fireAnimations) {
    fireAnimation.destroyFireAnimation();
  }
  for (auto &fireAnimation : _fireAnimations1V1) {
    fireAnimation.destroyFireAnimation();
  }
  _fireAnimations.clear();
  _fireAnimations1V1.clear();
}

void Window::changeFireAnimation() {
  for (auto &fireAnimation : _fireAnimations) {
    fireAnimation.changeFireAnimation();
  }
  for (auto &fireAnimation : _fireAnimations1V1) {
    fireAnimation.changeFireAnimation();
  }
}