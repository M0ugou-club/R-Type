/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Lobby
*/

#include "Lobby.hpp"

Lobby::Lobby() {
  _name = "Lobby";
  commandGame = CommandGame();
}

Lobby::~Lobby() {}

void Lobby::init() { _window->addButton(100, 100, 200, 50, "Start"); }

sceneType
Lobby::loop(eventType event,
            std::chrono::time_point<std::chrono::steady_clock> deltaTime) {
  auto &entityType = _ecs.get_components<EntityType>();
  Command command;
  auto key = _window->catchKey();
  float mouseX, mouseY;

  command = _queue->popGameQueue();
  if (command.type != EMPTY) {
    if (command.type == CommandType::STARTGAME) {
      _window->deleteTexts();
      _window->deleteButtons();
      for (std::size_t i = 0; i < entityType.size(); ++i) {
        if (entityType[i].has_value()) {
          if (entityType[i] && entityType[i] == EntityType::Player) {
            _ecs.kill_entity(Entities(i));
          }
        }
      }
      return sceneType::HISTORY;
    }
    commandGame.executeCommandGame(command, _queue, &_ecs, _window);
  }

  _window->getMouseState(&mouseX, &mouseY);
  if (event == MOUSE_CLICK) {
    for (auto &button : _window->getButtons()) {
      if (button.isClicked(mouseX, mouseY)) {
        if (button.getText() == "Start") {
          Command command;
          std::cout << "Start game" << std::endl;
          command.type = CommandType::STARTGAME;
          _queue->pushTcpQueue(command);
        }
      }
    }
  }

  _window->drawBackground();
  _window->drawButton();
  _window->drawText();
  return sceneType::NO_SWITCH;
}
