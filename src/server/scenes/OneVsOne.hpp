/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** OneVsOne
*/

#pragma once

#include "AScene.hpp"
#include "../commandSystem/CommandGame.hpp"

class OneVsOne : public AScene {
public:
  OneVsOne();
  ~OneVsOne();

  sceneType
  loop(std::chrono::time_point<std::chrono::steady_clock> deltaTime) override;

  void init() override;

private:
  CommandGame commandGame;
  bool _startCooldown;
  int _coolDown;
  bool _firstRound;
  std::chrono::time_point<std::chrono::steady_clock> _next;
};
