/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Utils
*/

#pragma once

#include <iostream>

enum sceneType {
  MENU,
  HISTORY,
  ENDLESS,
  ONE_VS_ONE,
  LOBBY,
  LOBBY1V1,
  QUIT,
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
  A,
  B,
  C,
  D,
  E,
  F,
  G,
  H,
  I,
  J,
  K,
  L,
  M,
  N,
  O,
  P,
  Q,
  R,
  S,
  T,
  U,
  V,
  W,
  X,
  Y,
  Z,
  NONE,
};

enum eventType { MOUSE_CLICK, CLOSE_WINDOW, NO_EVENT };

struct ChoosingParams {
  std::string ip;
  int spaceshipId;
  int bulletId;
  int gamemode;
  std::string nickname;
};

enum soundType {
  BULLET_SOUND,
  ENDLESS_MUSIC,
  MICHOU_ET_ELSA_2,
  WAVE1,
  WAVE2,
  WAVE3,
  NEWWAVE,
  MICHOU_REMIX_WINTERZUUKO,
};
