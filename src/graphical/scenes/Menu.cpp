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

Menu::~Menu() {}

void Menu::init() {
  _windowHeight = _window->getWindowHeight();
  _windowWidth = _window->getWindowWidth();

  _window->addText("Cosmic Michou", 50, 50, 500, 50, 100,
                   "../src/graphical/assets/RTypefont.otf",
                   {255, 255, 255, 255});
  _window->addText("Vendetta", 60, 150, 500, 50, 50,
                   "../src/graphical/assets/RTypefont.otf",
                   {255, 255, 255, 255});
  _window->addButton(0.03 * _windowWidth, 0.27 * _windowHeight, 320, 50,
                     "Heberger", "menu");
  _window->addButton(0.03 * _windowWidth, 0.37 * _windowHeight, 320, 50,
                     "Rejoindre", "menu");
  _window->addButton(0.03 * _windowWidth, 0.46 * _windowHeight, 320, 50,
                     "Parametres", "menu");
  _window->addButton(0.03 * _windowWidth, 0.55 * _windowHeight, 320, 50,
                     "Quitter", "menu");
  _window->setBackground(
      _window->loadTexture("../src/graphical/assets/menu.png"));

  auto entitie = _ecs->spawn_entity();
  _ecs->add_component<Position>(
      entitie, Position(0.35 * _windowWidth, 0.27 * _windowHeight));
  _ecs->add_component<Draw>(
      entitie,
      Draw({255, 255, 255, 255},
           {static_cast<int>(0.32 * _windowWidth),
            static_cast<int>(0.27 * _windowHeight), 770, 484},
           _window->loadTexture("../src/graphical/assets/CreateParty.svg")));
  _ecs->add_component<EntityType>(entitie, EntityType::Menu);

  auto entitie2 = _ecs->spawn_entity();

  _ecs->add_component<Position>(entitie2, Position(700, 300));
  _ecs->add_component<Draw>(
      entitie2,
      Draw({255, 255, 255, 255},
           {static_cast<int>(0.35 * _windowWidth),
            static_cast<int>(0.43 * _windowHeight), 686, 117},
           _window->loadTexture("../src/graphical/assets/dropshadow.svg")));
  _ecs->add_component<EntityType>(entitie2, EntityType::Menu);

  auto entitie3 = _ecs->spawn_entity();
  _ecs->add_component<Position>(entitie3, Position(700, 300));
  _ecs->add_component<Draw>(
      entitie3,
      Draw({255, 255, 255, 255},
           {static_cast<int>(0.35 * _windowWidth),
            static_cast<int>(0.57 * _windowHeight), 686, 117},
           _window->loadTexture("../src/graphical/assets/dropshadow.svg")));
  _ecs->add_component<EntityType>(entitie3, EntityType::Menu);
}

void Menu::setupHostMenu() {
  _windowOpen = true;
  _menuTitle = "Crée une partie";

  addSpaceshipSelection("Heberger");

  _window->addText(_menuTitle, static_cast<int>(0.367 * _windowWidth),
                   static_cast<int>(0.282 * _windowHeight), 500, 50, 37,
                   "../src/graphical/assets/RTypefont.otf", {0, 0, 0, 0});

  _window->addButton(static_cast<int>(0.358 * _windowWidth),
                     static_cast<int>(0.72 * _windowHeight), 670, 50, "Hoster",
                     "Heberger_window", {37, 37, 37, 70}, {37, 37, 37, 200},
                     {255, 255, 255, 255}, {255, 255, 255, 255});

  _window->addDropdown(static_cast<int>(0.358 * _windowWidth),
                       static_cast<int>(0.355 * _windowHeight), 350, 50,
                       {"Duel", "Histoire", "EndLess"}, "Heberger_window");

  _window->addInputText(static_cast<int>(0.7 * _windowWidth),
                        static_cast<int>(0.355 * _windowHeight), 260, 50,
                        "../src/graphical/assets/RTypefont.otf",
                        {255, 255, 255, 255}, "Heberger_window", "PSEUDO");
}

void Menu::setupJoinMenu() {
  _windowOpen = true;
  _menuTitle = "Rejoindre une partie";
  addSpaceshipSelection("Rejoindre");

  _window->addButton(static_cast<int>(0.358 * _windowWidth),
                     static_cast<int>(0.72 * _windowHeight), 670, 50,
                     "Rejoindre la partie", "Rejoindre_window",
                     {37, 37, 37, 70}, {37, 37, 37, 200}, {255, 255, 255, 255},
                     {255, 255, 255, 255});

  _window->addText(_menuTitle, static_cast<int>(0.367 * _windowWidth),
                   static_cast<int>(0.282 * _windowHeight), 500, 50, 37,
                   "../src/graphical/assets/RTypefont.otf", {0, 0, 0, 0});

  _window->addInputText(static_cast<int>(0.358 * _windowWidth),
                        static_cast<int>(0.351 * _windowHeight), 250, 50,
                        "../src/graphical/assets/RTypefont.otf",
                        {255, 255, 255, 255}, "Rejoindre_window", "127.0.0.1");

  _window->addInputText(static_cast<int>(0.7 * _windowWidth),
                        static_cast<int>(0.355 * _windowHeight), 260, 50,
                        "../src/graphical/assets/RTypefont.otf",
                        {255, 255, 255, 255}, "Rejoindre_window", "PSEUDO");
}

void Menu::setupSettingsMenu() {
  _menuTitle = "Settings";
  _windowOpen = true;

  _window->addText(_menuTitle, static_cast<int>(0.367 * _windowWidth),
                   static_cast<int>(0.282 * _windowHeight), 500, 50, 37,
                   "../src/graphical/assets/RTypefont.otf", {0, 0, 0, 0});

  _window->addButton(static_cast<int>(0.365 * _windowWidth),
                     static_cast<int>(0.72 * _windowHeight), 220, 50,
                     "1920x1080", "Parametres_window", {37, 37, 37, 70},
                     {37, 37, 37, 200}, {255, 255, 255, 255},
                     {255, 255, 255, 255});
  _window->addButton(static_cast<int>(0.55 * _windowWidth),
                     static_cast<int>(0.72 * _windowHeight), 220, 50,
                     "1664x936", "Parametres_window", {37, 37, 37, 70},
                     {37, 37, 37, 200}, {255, 255, 255, 255},
                     {255, 255, 255, 255});
  _window->addButton(static_cast<int>(0.74 * _windowWidth),
                     static_cast<int>(0.72 * _windowHeight), 220, 50,
                     "1536x864", "Parametres_window", {37, 37, 37, 70},
                     {37, 37, 37, 200}, {255, 255, 255, 255},
                     {255, 255, 255, 255});
}

void Menu::addSpaceshipSelection(std::string window) {

  std::string menu_window = window + "_window";
  _window->addButton(static_cast<int>(0.38 * _windowWidth),
                     static_cast<int>(0.585 * _windowHeight), 147, 93,
                     "../src/graphical/assets/menu/weapon1_hover.png",
                     "../src/graphical/assets/menu/weapon1.png",
                     "../src/graphical/assets/menu/weapon1_selected.png",
                     "weapon1", menu_window);
  _window->addButton(static_cast<int>(0.51 * _windowWidth),
                     static_cast<int>(0.585 * _windowHeight), 147, 93,
                     "../src/graphical/assets/menu/weapon2_hover.png",
                     "../src/graphical/assets/menu/weapon2.png",
                     "../src/graphical/assets/menu/weapon2_selected.png",
                     "weapon2", menu_window);
  _window->addButton(static_cast<int>(0.64 * _windowWidth),
                     static_cast<int>(0.585 * _windowHeight), 147, 93,
                     "../src/graphical/assets/menu/weapon3_hover.png",
                     "../src/graphical/assets/menu/weapon3.png",
                     "../src/graphical/assets/menu/weapon3_selected.png",
                     "weapon3", menu_window);
  _window->addButton(static_cast<int>(0.77 * _windowWidth),
                     static_cast<int>(0.585 * _windowHeight), 147, 93,
                     "../src/graphical/assets/menu/weapon4_hover.png",
                     "../src/graphical/assets/menu/weapon4.png",
                     "../src/graphical/assets/menu/weapon4_selected.png",
                     "weapon4", menu_window);
  _window->addButton(static_cast<int>(0.38 * _windowWidth),
                     static_cast<int>(0.444 * _windowHeight), 147, 93,
                     "../src/graphical/assets/menu/spaceship1.png",
                     "../src/graphical/assets/menu/spaceship1_hover.png",
                     "../src/graphical/assets/menu/spaceship1_selected.png",
                     "spaceship1", menu_window);
  _window->addButton(static_cast<int>(0.51 * _windowWidth),
                     static_cast<int>(0.444 * _windowHeight), 147, 93,
                     "../src/graphical/assets/menu/spaceship2_hover.png",
                     "../src/graphical/assets/menu/spaceship2.png",
                     "../src/graphical/assets/menu/spaceship2_selected.png",
                     "spaceship2", menu_window);
  _window->addButton(static_cast<int>(0.64 * _windowWidth),
                     static_cast<int>(0.444 * _windowHeight), 147, 93,
                     "../src/graphical/assets/menu/spaceship3_hover.png",
                     "../src/graphical/assets/menu/spaceship3.png",
                     "../src/graphical/assets/menu/spaceship3_selected.png",
                     "spaceship3", menu_window);

  _window->addButton(static_cast<int>(0.77 * _windowWidth),
                     static_cast<int>(0.444 * _windowHeight), 147, 93,
                     "../src/graphical/assets/menu/spaceship4_hover.png",
                     "../src/graphical/assets/menu/spaceship4.png",
                     "../src/graphical/assets/menu/spaceship4_selected.png",
                     "spaceship4", menu_window);
}
void Menu::setMenu(const std::string &selectedMenu) {
  if (isSpaceship(selectedMenu)) {
    handleSpaceshipSelection(selectedMenu);
    return;
  }

  if (isWeapon(selectedMenu)) {
    handleWeaponSelection(selectedMenu);
    return;
  }

  if (_selectedMenu == selectedMenu) {
    return;
  }

  if (!isValidMenu(selectedMenu)) {
    return;
  }

  updateMenu(selectedMenu);
}

bool Menu::isSpaceship(const std::string &menu) const {
  return menu == "spaceship1" || menu == "spaceship2" || menu == "spaceship3" ||
         menu == "spaceship4";
}

void Menu::handleSpaceshipSelection(const std::string &spaceship) {
  _window->unSelectButton(_selectedSpaceship);
  _selectedSpaceship = spaceship;
  _window->setSelectedButton(spaceship);
}

bool Menu::isWeapon(const std::string &menu) const {
  return menu == "weapon1" || menu == "weapon2" || menu == "weapon3" ||
         menu == "weapon4";
}

void Menu::handleWeaponSelection(const std::string &weapon) {
  _window->unSelectButton(_selectedWeapon);
  _selectedWeapon = weapon;
  _window->setSelectedButton(weapon);
}

bool Menu::isValidMenu(const std::string &menu) const {
  return menu == "Heberger" || menu == "Rejoindre" || menu == "menu";
}

void Menu::updateMenu(const std::string &menu) {
  _toUpdate = menu + "_window";
  if (menu == "Heberger") {
    setupMenus();
    setupHostMenu();
  } else if (menu == "Rejoindre") {
    setupMenus();
    setupJoinMenu();
  } else if (menu == "Parametres") {
    setupMenus();
    setupSettingsMenu();
  }
  _selectedMenu = menu;
}

void Menu::setupMenus() {
  _window->deleteButtons(_toUpdate);
  _window->deletedropdowns();
  _window->deleteInputTexts();
  _window->deleteText(_menuTitle);
  _windowOpen = true;
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
    _window->setButtonTextureDirty(_toUpdate);
    _window->deleteText(_menuTitle);
    _window->addText(_menuTitle, static_cast<int>(0.367 * _windowWidth),
                     static_cast<int>(0.282 * _windowHeight), 500, 50, 37,
                     "../src/graphical/assets/RTypefont.otf", {0, 0, 0, 0});
    return processMouseClick(clickedButton, mouseX, mouseY);
  }

  return "";
}

std::string Menu::processMouseClick(const std::string &clickedButton,
                                    float mouseX, float mouseY) {
  if (clickedButton == "Hoster" || clickedButton == "Rejoindre la partie" ||
      clickedButton == "Quitter") {
    return clickedButton;
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

  return "";
}

void Menu::keyHandler(keyType key) {
  for (auto &input : _window->getInputTexts()) {
    if (input.isSelected()) {
      handleTextInput(key, input);
      return;
    }
  }
}

void Menu::handleTextInput(keyType key, InputText &input) {
  static keyType lastKey = keyType::NONE;
  if (key != lastKey) {
    if (key == keyType::BACKSPACE) {
      handleBackspace(input);
    } else {
      appendKeyToInput(key, input);
    }
    lastKey = key;
  }
}

void Menu::handleBackspace(InputText &input) {
  if (!input.getText().empty()) {
    input.setText(input.getText().substr(0, input.getText().size() - 1));
  }
  input.draw();
}

void Menu::appendKeyToInput(keyType key, InputText &input) {
  std::string result = input.getNumber(key);
  input.setText(input.getText() + result);
  input.draw();
}

sceneType
Menu::loop(eventType event,
           std::chrono::time_point<std::chrono::steady_clock> deltaTime) {
  auto key = _window->catchKey();
  float mouseX, mouseY;

  auto button = mouseHandler(mouseX, mouseY, event);

  handleKeyInput(key);

  sceneType sceneChange = processButtonActions(button);
  if (sceneChange != sceneType::NO_SWITCH) {
    return sceneChange;
  }

  renderMenu();

  return sceneType::NO_SWITCH;
}

void Menu::handleKeyInput(std::vector<keyType> &key) {
  keyHandler(key[0]);
  key.erase(key.begin());
}

sceneType Menu::processButtonActions(const std::string &button) {
  if (_selectedSpaceship != "" && _selectedWeapon != "") {
    if (button == "Hoster") {
      prepareLobby("127.0.0.1", _window->getInputTextValue("PSEUDO"));
      return sceneType::LOBBY;
    }
    if (button == "Rejoindre la partie") {
      prepareLobby(_window->getInputTextValue("127.0.0.1"),
                   _window->getInputTextValue("PSEUDO"));
      return sceneType::LOBBY;
    }
  }

  if (button == "Quitter") {
    _window->deleteTexts();
    _window->deleteButtons();
    _window->deletedropdowns();
    return sceneType::QUIT;
  }

  return sceneType::NO_SWITCH;
}

void Menu::prepareLobby(const std::string &ip, const std::string &pseudo) {
  _window->deleteTexts();
  _window->deleteButtons();
  _window->deleteInputTexts();
  _params->ip = ip;
  std::cout << "Pseudo: " << pseudo << std::endl;
  std::size_t spaceId = std::stoi(_selectedSpaceship.substr(9));
  _params->spaceshipId = spaceId;
  std::size_t weaponId = std::stoi(_selectedWeapon.substr(6));
  _params->bulletId = weaponId;
}

void Menu::renderMenu() {
  _window->drawBackground();
  _window->drawButton("menu");
  _window->createMenuPipe();

  if (_windowOpen) {
    auto &entityType = _ecs->get_components<EntityType>();
    auto &draw = _ecs->get_components<Draw>();

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
}
