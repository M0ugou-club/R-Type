/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Menu
*/

#include "Menu.hpp"

Menu::Menu() {
  _name = "Menu";
  _selectedButton = "";
}

Menu::~Menu() { _window->stopTextInput(); }

void Menu::init() {
  _window->addText("Cosmic Michou", 50, 50, 500, 50, 100,
                   "../src/graphical/assets/RTypefont.otf",
                   {255, 255, 255, 255});
  _window->addText("Vendetta", 60, 150, 500, 50, 50,
                   "../src/graphical/assets/RTypefont.otf",
                   {255, 255, 255, 255});
  _window->addButton(70, 200 + 100, 500, 50, "Heberger", "menu");
  _window->addButton(70, 200 + 200, 500, 50, "Rejoindre", "menu");
  _window->addButton(70, 200 + 300, 500, 50, "Parametres", "menu");
  _window->addButton(70, 200 + 400, 500, 50, "Quitter", "menu");
  _window->addDropdown(1000, 500, 500, 50, {"test1", "test2", "test3"},
                       "window");
  _window->setBackground(
      _window->loadTexture("../src/graphical/assets/menu.png"));
  auto entitie = _ecs.spawn_entity();
  _ecs.add_component<Position>(entitie, Position(700, 300));
  _ecs.add_component<Draw>(
      entitie,
      Draw({255, 255, 255, 255}, {700, 300, 887, 484},
           _window->loadTexture("../src/graphical/assets/CreateParty.svg")));
  _ecs.add_component<EntityType>(entitie, EntityType::Menu);
  _window->addInputText(500, 300, 400, 50,
                        "../src/graphical/assets/RTypefont.otf",
                        {255, 255, 255, 255}, "username");
  _window->startTextInput();
}

void Menu::setMenu(std::string selectedButton) {

  if (_selectedButton == selectedButton)
    return;

  _selectedButton = selectedButton;

  _window->deleteText(_menuTitle);
  if (_selectedButton == "Heberger") {
    _menuTitle = "Crée une partie";
    _window->addButton(730, 200 + 500, 830, 50, "Valider", "window",
                       {37, 37, 37, 70}, {37, 37, 37, 200},
                       {255, 255, 255, 255}, {255, 255, 255, 255});
  }
  if (_selectedButton == "Rejoindre") {
    _window->deleteButtons("window");
    _menuTitle = "Rejoindre une partie";
  }
  if (_selectedButton == "Parametres") {
    _menuTitle = "Settings";
  }
  _window->addText(_menuTitle, 720, 310, 500, 50, 37,
                   "../src/graphical/assets/RTypefont.otf", {0, 0, 0, 0});
}

std::string Menu::mouseHandler(float mouseX, float mouseY, eventType event) {
  _window->getMouseState(&mouseX, &mouseY);
  if (event == MOUSE_CLICK) {
    for (auto &button : _window->getButtons()) {
      if (button.isClicked(mouseX, mouseY)) {
        std::string menu = button.getText();
        setMenu(menu);
        return menu;
      }
    }
    for (auto &dropdown : _window->getDropdowns()) {
      if (dropdown->isClicked(mouseX, mouseY)) {
        dropdown->toggleOpen();
        return "";
      }
    }
    for (auto &input : _window->getInputTexts()) {
      if (input.isClicked(mouseX, mouseY)) {
        input.setSelected(true);
      } else {
        input.setSelected(false);
      }
      input.handleEvent(_window->catchEvent());
    }
  }
  return "";
}

void Menu::keyHandler(keyType key) {
  std::string result;

  for (auto &input : _window->getInputTexts()) {
    if (input.isSelected()) {
      static keyType lastKey = keyType::NONE;
      if (key != lastKey) {
        if (key == keyType::BACKSPACE) {
          if (!input.getText().empty()) {
            input.setText(
                input.getText().substr(0, input.getText().size() - 1));
          }
          input.draw();
          lastKey = key;
          return;
        }
        result = input.getNumber(key);
        input.setText(input.getText() + result);
        input.draw();
        lastKey = key;
      }
      return;
    }
  }
}

sceneType
Menu::loop(eventType event,
           std::chrono::time_point<std::chrono::steady_clock> deltaTime) {
  auto key = _window->catchKey();
  float mouseX, mouseY;

  auto &entityType = _ecs.get_components<EntityType>();
  auto &draw = _ecs.get_components<Draw>();
  auto &position = _ecs.get_components<Position>();

  auto button = mouseHandler(mouseX, mouseY, event);
  keyHandler(key);
  // if (button == "Heberger") {
  //   _window->deleteTexts();
  //   _window->deleteButtons();
  //   return sceneType::LOBBY;
  // }
  _window->drawBackground();
  _window->drawButton("menu");
  _window->createMenuPipe();

  if (_selectedButton != "") {
    for (std::size_t i = 0; i < entityType.size(); ++i) {
      if (entityType[i] == EntityType::Menu && draw[i].has_value()) {
        _window->draw(draw[i]->texture, draw[i]->rect);
      }
    }
  }
  _window->drawText();
  _window->drawButton("window");
  _window->drawDropdown();

  _window->drawInputTexts();
  _window->handleInputTextEvent(mouseX, mouseY, event);

  if (button == "Quitter") {
    _window->deleteTexts();
    _window->deleteButtons();
    return sceneType::LOBBY;
  }

  return sceneType::NO_SWITCH;
}
