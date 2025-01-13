/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Utils
*/

#pragma once
#include <unordered_map>
#include <array>
#include <string>
#include <stdint.h>
#include <SDL3/SDL.h>

#include <iostream>

enum sceneType {
  MENU,
  HISTORY,
  ENDLESS,
  ONE_VS_ONE,
  LOBBY,
  NO_SWITCH,
};

enum keyType {
  UP,
  DOWN,
  LEFT,
  RIGHT,
  SPACE,
  ENTER,
  ESCAPE,
  NUMBER,
  BACKSPACE,
  PERIOD,
  ONE,
  TWO,
  THREE,
  FOUR,
  FIVE,
  SIX,
  SEVEN,
  EIGHT,
  NINE,
  ZERO,
  NONE,
};

enum eventType { MOUSE_CLICK, CLOSE_WINDOW, NO_EVENT };

struct ChoosingParams {
  std::string ip;
  int spaceshipId;
  int bulletId;
};
