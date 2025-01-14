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

  void addSpaceshipSelection(std::string window);

  std::string handleButtonClick(float mouseX, float mouseY);

private:
  std::string _selectedMenu;
  std::string _selectedButton;
  std::string _menuTitle;
  std::string _selectedSpaceship;
  std::string _selectedWeapon;
  std::string _toUpdate;
  bool _windowOpen;
};
