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
  _selectedSpaceship = "";
  _selectedWeapon = "";
  _toUpdate = "_window";
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
  _window->setBackground(
      _window->loadTexture("../src/graphical/assets/menu.png"));
  auto entitie = _ecs.spawn_entity();
  _ecs.add_component<Position>(entitie, Position(700, 300));
  _ecs.add_component<Draw>(
      entitie,
      Draw({255, 255, 255, 255}, {700, 300, 887, 484},
           _window->loadTexture("../src/graphical/assets/CreateParty.svg")));
  _ecs.add_component<EntityType>(entitie, EntityType::Menu);
  auto entitie2 = _ecs.spawn_entity();
  _ecs.add_component<Position>(entitie2, Position(700, 300));
  _ecs.add_component<Draw>(
      entitie2,
      Draw({255, 255, 255, 255}, {710, 470, 686, 117},
           _window->loadTexture("../src/graphical/assets/dropshadow.svg")));
  _ecs.add_component<EntityType>(entitie2, EntityType::Menu);

  auto entitie3 = _ecs.spawn_entity();
  _ecs.add_component<Position>(entitie3, Position(700, 300));
  _ecs.add_component<Draw>(
      entitie3,
      Draw({255, 255, 255, 255}, {710, 580, 686, 117},
           _window->loadTexture("../src/graphical/assets/dropshadow.svg")));
  _ecs.add_component<EntityType>(entitie3, EntityType::Menu);
  _window->startTextInput();
}

void Menu::setMenu(const std::string &selectedMenu) {

  if (selectedMenu == "spaceship1" || selectedMenu == "spaceship2" ||
      selectedMenu == "spaceship3" || selectedMenu == "spaceship4") {
    _selectedSpaceship = selectedMenu;
    return;
  }

  if (selectedMenu == "weapon1" || selectedMenu == "weapon2" ||
      selectedMenu == "weapon3" || selectedMenu == "weapon4") {
    _selectedWeapon = selectedMenu;
    return;
  }

  if (selectedMenu == "1920x1080" || selectedMenu == "1664x936" ||
      selectedMenu == "1536x864") {

    if (selectedMenu == "1920x1080") {
      _window->setWindowSize(1920, 1080);
      return;
    }
    int width = std::stoi(selectedMenu.substr(0, 4));
    int height = std::stoi(selectedMenu.substr(5, 3));
    _window->setWindowSize(width, height);
    return;
  }

  if (_selectedMenu == selectedMenu)
    return;

  if (selectedMenu != "Heberger" && selectedMenu != "Rejoindre" &&
      selectedMenu != "Parametres" && selectedMenu != "menu") {
    return;
  }

  if (selectedMenu == "Heberger") {
    _window->deleteButtons(_toUpdate);
    _window->deletedropdowns(_toUpdate);
    _window->deleteInputTexts(_toUpdate);
    _window->deleteText(_menuTitle);
    _windowOpen = true;
    _toUpdate = selectedMenu + "_window";
    setupHostMenu();
  } else if (selectedMenu == "Rejoindre") {
    _window->deleteButtons(_toUpdate);
    _window->deletedropdowns(_toUpdate);
    _window->deleteInputTexts(_toUpdate);
    _toUpdate = selectedMenu + "_window";
    _window->deleteText(_menuTitle);
    setupJoinMenu();
  } else if (selectedMenu == "Parametres") {
    _window->deleteButtons(_toUpdate);
    _window->deletedropdowns(_toUpdate);
    _window->deleteInputTexts(_toUpdate);
    _toUpdate = selectedMenu + "_window";
    _window->deleteText(_menuTitle);
    setupSettingsMenu();
  }
  _selectedMenu = selectedMenu;
}

void Menu::setupHostMenu() {
  _windowOpen = true;
  _menuTitle = "Crée une partie";

  _window->addText(_menuTitle, 720, 310, 500, 50, 37,
                   "../src/graphical/assets/RTypefont.otf", {0, 0, 0, 0});

  _window->addButton(730, 200 + 500, 830, 50, "Hoster", "Heberger_window",
                     {37, 37, 37, 70}, {37, 37, 37, 200}, {255, 255, 255, 255},
                     {255, 255, 255, 255});

  _window->addDropdown(730, 380, 500, 50, {"Duel", "Histoire", "EndLess"},
                       "Heberger_window");

  addSpaceshipSelection("Heberger");
}

void Menu::setupJoinMenu() {
  _windowOpen = true;
  _menuTitle = "Rejoindre une partie";

  _window->addText(_menuTitle, 720, 310, 500, 50, 37,
                   "../src/graphical/assets/RTypefont.otf", {0, 0, 0, 0});

  _window->addInputText(730, 380, 250, 50,
                        "../src/graphical/assets/RTypefont.otf",
                        {255, 255, 255, 255}, "Rejoindre_window", "127.0.0.1");

  _window->addButton(730, 700, 830, 50, "Rejoindre la partie",
                     "Rejoindre_window", {37, 37, 37, 70}, {37, 37, 37, 200},
                     {255, 255, 255, 255}, {255, 255, 255, 255});

  addSpaceshipSelection("Rejoindre");
}

void Menu::setupSettingsMenu() {
  _menuTitle = "Settings";
  _windowOpen = true;

  _window->addText(_menuTitle, 720, 310, 500, 50, 37,
                   "../src/graphical/assets/RTypefont.otf", {0, 0, 0, 0});

  _window->addButton(730, 700, 220, 50, "1920x1080", "Parametres_window",
                     {37, 37, 37, 70}, {37, 37, 37, 200}, {255, 255, 255, 255},
                     {255, 255, 255, 255});
  _window->addButton(960, 700, 220, 50, "1664x936", "Parametres_window",
                     {37, 37, 37, 70}, {37, 37, 37, 200}, {255, 255, 255, 255},
                     {255, 255, 255, 255});
  _window->addButton(1190, 700, 220, 50, "1536x864", "Parametres_window",
                     {37, 37, 37, 70}, {37, 37, 37, 200}, {255, 255, 255, 255},
                     {255, 255, 255, 255});
}

void Menu::addSpaceshipSelection(std::string window) {

  std::string menu_window = window + "_window";
  _window->addButton(740, 590, 147, 93, "../src/graphical/assets/weapon1.png",
                     "../src/graphical/assets/weapon1.png", "weapon1",
                     menu_window);
  _window->addButton(897, 590, 147, 93, "../src/graphical/assets/weapon2.png",
                     "../src/graphical/assets/weapon2.png", "weapon2",
                     menu_window);
  _window->addButton(1054, 590, 147, 93, "../src/graphical/assets/weapon3.png",
                     "../src/graphical/assets/weapon3.png", "weapon3",
                     menu_window);
  _window->addButton(1211, 590, 147, 93, "../src/graphical/assets/weapon4.png",
                     "../src/graphical/assets/weapon4.png", "weapon4",
                     menu_window);
  _window->addButton(
      740, 480, 147, 93, "../src/graphical/assets/spaceship1_hover.png",
      "../src/graphical/assets/spaceship1.png", "spaceship1", menu_window);
  _window->addButton(897, 480, 147, 93,
                     "../src/graphical/assets/spaceship2.png",
                     "../src/graphical/assets/spaceship2_hover.png",
                     "spaceship2", menu_window);
  _window->addButton(1054, 480, 147, 93,
                     "../src/graphical/assets/spaceship3.png",
                     "../src/graphical/assets/spaceship3_hover.png",
                     "spaceship3", menu_window);

  _window->addButton(
      1211, 480, 147, 93, "../src/graphical/assets/spaceship4.png",
      "../src/graphical/assets/spaceship4.png", "spaceship4", menu_window);
}

std::string Menu::handleButtonClick(float mouseX, float mouseY) {
  for (auto &button : _window->getButtons()) {
    if (button.isClicked(mouseX, mouseY)) {
      std::string buttonText = button.getText();

      setMenu(buttonText);

      return buttonText;
    }
  }
  return "";
}

std::string Menu::mouseHandler(float mouseX, float mouseY, eventType event) {
  _window->getMouseState(&mouseX, &mouseY);

  if (event == MOUSE_CLICK) {
    std::string clickedButton = handleButtonClick(mouseX, mouseY);
    std::cout << clickedButton << std::endl;
    _window->setButtonTextureDirty(_toUpdate);
    if (clickedButton == "Hoster") {
      return "Hoster";
    }
    if (clickedButton == "Rejoindre la partie") {
      return "Rejoindre la partie";
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

  if (_selectedSpaceship != "" && _selectedWeapon != "") {
    if (button == "Hoster") {
      _window->deleteTexts();
      _window->deleteButtons();
      _window->deleteInputTexts();
      _params->ip = "127.0.0.1";
      std::size_t spaceId = std::stoi(_selectedSpaceship.substr(9));
      _params->spaceshipId = spaceId;
      std::size_t weaponId = std::stoi(_selectedWeapon.substr(6));
      _params->bulletId = weaponId;
      return sceneType::LOBBY;
    }
  }

  if (_selectedSpaceship != "" && _selectedWeapon != "") {
    if (button == "Rejoindre la partie") {
      _window->deleteTexts();
      _window->deleteButtons();
      _params->ip = _window->getInputTextValue("Rejoindre_window");
      _window->deleteInputTexts();
      std::size_t spaceId = std::stoi(_selectedSpaceship.substr(9));
      _params->spaceshipId = spaceId;
      std::size_t weaponId = std::stoi(_selectedWeapon.substr(6));
      _params->bulletId = weaponId;
      return sceneType::LOBBY;
    }
  }

  _window->drawBackground();
  _window->drawButton("menu");
  _window->createMenuPipe();

  if (_windowOpen) {
    for (std::size_t i = 0; i < entityType.size(); ++i) {
      if (entityType[i] == EntityType::Menu && draw[i].has_value()) {
        _window->draw(draw[i]->texture, draw[i]->rect);
      }
    }
  }
  _window->drawText();
  std::string menu_window = _selectedMenu + "_window";
  _window->drawButton(menu_window);
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
