/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** History
*/

#include "History.hpp"

History::History() {
  _name = "History";
  _startCooldown = true;
  _firstRound = true;
  _coolDown = 4;
  _nextCorrectPosition = std::chrono::steady_clock::now();
}

History::~History() {}

void History::init() { _wave = Wave(_ecs); }

sceneType
History::loop(std::chrono::time_point<std::chrono::steady_clock> deltaTime) {
  Command command;
  std::chrono::time_point<std::chrono::steady_clock> now =
      std::chrono::steady_clock::now();

  command = _queue->popGameQueue();
  if (command.type != EMPTY)
    _commandGame.executeCommandGame(command, _queue, _ecs);

  if (_startCooldown && now > _next) {
    _next = std::chrono::steady_clock::now() + std::chrono::seconds(1);
    if (_coolDown <= 3) {
      Command cmd;
      cmd.type = CommandType::COOLDOWN;
      cmd.cooldown.time = _coolDown;
      _queue->pushTcpQueue(cmd);
    }
    if (_coolDown == 0)
      _startCooldown = false;
    _coolDown--;
  }

  if (!_startCooldown) {
    if (_firstRound) {
      _firstRound = false;
      std::string path =
          "../src/game/config/endless/classic/classic_wave_1.json";
      _wave.load(path, *_queue);
    }
    if (now > deltaTime) {
      enemy_system(_ecs, false);
      position_system_net(1, _ecs, _queue, _nextCorrectPosition);
      if (now > _nextCorrectPosition)
        _nextCorrectPosition =
            std::chrono::steady_clock::now() + std::chrono::milliseconds(500);
      collision_system(_ecs, _queue);
    }
  }
  return sceneType::NO_SWITCH;
}
