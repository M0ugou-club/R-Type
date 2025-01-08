/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Lobby
*/

#include "Lobby.hpp"

Lobby::Lobby() { _name = "Lobby"; }

Lobby::~Lobby() {}

void Lobby::init() {}

sceneType Lobby::loop(float deltaTime) {
  Command command;

  command = _queue->popGameQueue();
  if (command.type != EMPTY) {
    if (command.type == CommandType::STARTGAME) {
      return sceneType::HISTORY;
    }
    _commandGame.executeCommandGame(command, _queue, _ecs);
  }

  // intercepter le signal pour lancer la game

  return sceneType::NO_SWITCH;
}
