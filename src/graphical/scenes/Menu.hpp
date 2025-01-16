/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Menu
*/

#pragma once

#include "AScene.hpp"
#include <cassert>
#include <string>

class Menu : public AScene {
public:
  Menu();
  ~Menu();

  void init() override;

  sceneType
  loop(eventType event,
       std::chrono::time_point<std::chrono::steady_clock> deltaTime) override;

  std::string mouseHandler(float mouseX, float mouseY, eventType event);

  void keyHandler(keyType key);

  void setMenu(const std::string &selectedButton);

  void setupHostMenu();

  void setupJoinMenu();

  void setupSettingsMenu();

  void setupMenus();

  void addSpaceshipSelection(std::string window);

  std::string handleButtonClick(float mouseX, float mouseY);

  void handleKeyInput(std::vector<keyType> &key);

  sceneType processButtonActions(const std::string &button);

  void prepareLobby(const std::string &ip, const std::string &pseudo);

  void renderMenu();

  void handleSpaceshipSelection(const std::string &spaceship);

  bool isSpaceship(const std::string &menu) const;

  bool isWeapon(const std::string &menu) const;

  bool isValidMenu(const std::string &menu) const;

  void handleWeaponSelection(const std::string &weapon);

  void updateMenu(const std::string &menu);

  std::string processMouseClick(const std::string &clickedButton, float mouseX,
                                float mouseY);

  void handleTextInput(keyType key, InputText &input);

  void handleBackspace(InputText &input);

  void appendKeyToInput(keyType key, InputText &input);

private:
  std::string _selectedMenu;
  std::string _selectedButton;
  std::string _menuTitle;
  std::string _selectedSpaceship;
  std::string _selectedWeapon;
  std::string _toUpdate;

  int _windowWidth;
  int _windowHeight;

  bool _windowOpen;
};
