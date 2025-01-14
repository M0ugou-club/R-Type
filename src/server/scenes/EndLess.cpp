/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** EndLess
*/

#include "EndLess.hpp"

EndLess::EndLess() {
  _name = "EndLess";
  _startCooldown = true;
  _firstRound = true;
  _coolDown = 4;
}

EndLess::~EndLess() {}

void EndLess::init() { _wave = Wave(_ecs); }

bool EndLess::waveIsClear() {
  auto &entityType = _ecs->get_components<EntityType>();

  for (std::size_t i = 0; i < entityType.size(); i++) {
    if (entityType[i] == EntityType::Enemy) {
      return false;
    }
  }
  return true;
}

void EndLess::waveGestion() {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 9);
  int random = dis(gen);

  if (waveIsClear()) {
    std::cout << "load " << random << " wave" << std::endl;
    _wave.load(classicWave[random], *_queue);
  }
}

sceneType
EndLess::loop(std::chrono::time_point<std::chrono::steady_clock> deltaTime) {
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
      _wave.load(classicWave[0], *_queue);
    }
    if (now > deltaTime) {
      waveGestion();
      enemy_system(_ecs);
      position_system_net(1, _ecs, _queue, _nextCorrectPosition);
      collision_system(_ecs, _queue);
      if (now > _nextCorrectPosition)
        _nextCorrectPosition =
            std::chrono::steady_clock::now() + std::chrono::milliseconds(500);
    }
  }
  return sceneType::NO_SWITCH;
}