/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** EndLess
*/

#include "EndLess.hpp"

EndLess::EndLess() {
  _name = "Endless";
  commandGame = CommandGame();
  _nextBullet = std::chrono::steady_clock::now() + std::chrono::seconds(1);
}

EndLess::~EndLess() {}

void EndLess::init() {
  _window->setBackground(
      _window->loadTexture("../src/graphical/assets/level1.png"));
  Command command;
  command.type = CommandType::CONNECT;
  command.connect.Nickname = "Player";
  _queue->pushTcpQueue(command);
  _window->playSound(MICHOU_REMIX_WINTERZUUKO, -1);
  _window->setBackgroundScrolling(true);
}

void EndLess::cam_system(keyType key) {
  if (key == C) {
    _window->setCameraFeed();
  }
}

sceneType
EndLess::loop(eventType event,
              std::chrono::time_point<std::chrono::steady_clock> deltaTime) {
  auto &positions = _ecs->get_components<Position>();
  auto &draw = _ecs->get_components<Draw>();
  auto &nicknames = _ecs->get_components<Nickname>();
  auto &entities = _ecs->get_components<EntityType>();
  auto &lifebars = _ecs->get_components<LifeBar>();
  auto &health = _ecs->get_components<Health>();
  auto &control = _ecs->get_components<Control>();

  Command command;
  std::chrono::time_point<std::chrono::steady_clock> now =
      std::chrono::steady_clock::now();

  command = _queue->popGameQueue();
  if (command.type != EMPTY) {
    commandGame.executeCommandGame(command, _queue, _ecs, _window);
  }

  std::vector<keyType> keys = _window->catchKey();
  auto movementKeys = _window->catchMovementKey();
  keyType keyOnce = _window->catchKeyOnce();

  if (now > deltaTime) {
    cam_system(keyOnce);
    _window->moveBackground();
    if (_window->getAllowToInteract()) {
      now = std::chrono::steady_clock::now();
      _window->deleteText("0");
      control_system(movementKeys, *_ecs);
      shoot_system(keys, *_ecs, _queue, _nextBullet);
      if (now >= _nextBullet) {
        _nextBullet = now + std::chrono::milliseconds(150);
      }
      position_system_graphic(1, *_ecs, _queue);
      enemy_system(_ecs.get());
      display_infos(_ecs.get());
    }
  }
  _window->drawBackground();
  _window->drawText();
  for (std::size_t i = 0; i < draw.size(); ++i) {
    if (!draw[i].has_value())
      continue;
    _window->draw(draw[i]->texture, draw[i]->rect);
    if (nicknames[i].has_value()) {
      _window->draw(nicknames[i]->texture, nicknames[i]->rect);
    }
    if (lifebars[i].has_value() && control[i].has_value()) {
      _window->drawRect(lifebars[i]->bar, lifebars[i]->color);
    }
  }
  _window->displayCameraFeed();
  return sceneType::NO_SWITCH;
}
