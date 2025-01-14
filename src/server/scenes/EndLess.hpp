/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** EndLess
*/

#pragma once

#include "../../game/systems/enemy/EnemySystems.hpp"
#include "../commandSystem/CommandGame.hpp"
#include "AScene.hpp"
#include "utils/Wave.hpp"
#include <map>

const std::string classicPath = "../src/game/config/endless/classic/";
const std::string miniBossPath = "../src/game/config/endless/mini_boss/";
const std::string bossPath = "../src/game/config/endless/boss/";

const std::string classicWave[] = {
    classicPath + "classic_wave_1.json",
    classicPath + "classic_wave_2.json",
    classicPath + "classic_wave_3.json",
    classicPath + "classic_wave_4.json",
    classicPath + "classic_wave_5.json",
    classicPath + "classic_wave_6.json",
    classicPath + "classic_wave_7.json",
    classicPath + "classic_wave_8.json",
    classicPath + "classic_wave_9.json",
    classicPath + "classic_wave_10.json"
};

const std::string miniBossWave[] = {
    miniBossPath + "mini_boss_wave_1.json",
    miniBossPath + "mini_boss_wave_2.json",
    miniBossPath + "mini_boss_wave_3.json",
};

const std::string bossWave[] = {
    bossPath + "boss_wave_1.json",
    bossPath + "boss_wave_2.json",
};

class EndLess : public AScene {
public:
  EndLess();
  ~EndLess();

  sceneType
  loop(std::chrono::time_point<std::chrono::steady_clock> deltaTime) override;

  bool waveIsClear();
  void waveGestion();
  void init() override;

private:
  Wave _wave;
  CommandGame _commandGame;
  bool _startCooldown;
  int _coolDown;
  bool _firstRound;
  std::chrono::time_point<std::chrono::steady_clock> _next;
};
