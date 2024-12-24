/*
** EPITECH PROJECT, 2024
** RType
** File description:
** Game
*/

#include "Game.hpp"
#include <memory>

void Game::load_component() {
  _ecs.register_component<Position>();
  _ecs.register_component<Velocity>();
  _ecs.register_component<Draw>();
  _ecs.register_component<Health>();
  _ecs.register_component<Control>();
  _ecs.register_component<EntityType>();
};

void Game::load_entity(std::shared_ptr<Queue> &queue) {
  auto enemy = create_entity<EntityType::Enemy>(
      _ecs, Position(800, 100), Velocity(0, -100), Health(),
      Draw({0, 255, 0, 255}, {150, 150, 150, 150}));
  auto enemy2 = create_entity<EntityType::Enemy>(
      _ecs, Position(700, 100), Velocity(0, -100), Health(),
      Draw({0, 255, 0, 255}, {150, 150, 150, 150}));
  auto enemy3 = create_entity<EntityType::Enemy>(
      _ecs, Position(600, 100), Velocity(0, -100), Health(),
      Draw({0, 255, 0, 255}, {150, 150, 150, 150}));
  auto enemy4 = create_entity<EntityType::Enemy>(
      _ecs, Position(500, 400), Velocity(0, -100), Health(),
      Draw({0, 255, 0, 255}, {150, 150, 150, 150}));

  Command *command = new Command();
  command->type = CommandType::CREATEENEMY;
  command->id = -10;
  command->createEnemy = new createEnemy();
  command->createEnemy->positionX = _ecs.get_components<Position>()[enemy]->x;
  command->createEnemy->positionY = _ecs.get_components<Position>()[enemy]->y;
  command->createEnemy->enemyId = enemy;
  queue->pushTcpQueue(command);

  Command *command2 = new Command();
  command2->type = CommandType::CREATEENEMY;
  command2->id = -10;
  command2->createEnemy = new createEnemy();
  command2->createEnemy->positionX = _ecs.get_components<Position>()[enemy2]->x;
  command2->createEnemy->positionY = _ecs.get_components<Position>()[enemy2]->y;
  command2->createEnemy->enemyId = enemy2;
  queue->pushTcpQueue(command2);

  Command *command3 = new Command();
  command3->type = CommandType::CREATEENEMY;
  command3->id = -10;
  command3->createEnemy = new createEnemy();
  command3->createEnemy->positionX = _ecs.get_components<Position>()[enemy3]->x;
  command3->createEnemy->positionY = _ecs.get_components<Position>()[enemy3]->y;
  command3->createEnemy->enemyId = enemy3;
  queue->pushTcpQueue(command3);

  Command *command4 = new Command();
  command4->type = CommandType::CREATEENEMY;
  command4->id = -10;
  command4->createEnemy = new createEnemy();
  command4->createEnemy->positionX = _ecs.get_components<Position>()[enemy4]->x;
  command4->createEnemy->positionY = _ecs.get_components<Position>()[enemy4]->y;
  command4->createEnemy->enemyId = enemy4;
  queue->pushTcpQueue(command4);
  return;
};

void Game::load() {
  load_component();
  return;
};

std::unique_lock<std::mutex> Game::lock_ecs() {
  return std::unique_lock<std::mutex>(ecsMutex);
};

void Game::loop(float deltaTime, std::shared_ptr<Queue> &queue) {
  std::lock_guard<std::mutex> lock(ecsMutex);

  enemy_system(queue);
  position_system(deltaTime, queue);
  return;
};

void Game::position_system(float deltaTime, std::shared_ptr<Queue> &queue) {
  auto &entityType = _ecs.get_components<EntityType>();
  auto &positions = _ecs.get_components<Position>();
  auto &health = _ecs.get_components<Health>();
  auto &velocities = _ecs.get_components<Velocity>();

  for (std::size_t i = 0; i < entityType.size(); ++i) {
    if (!entityType[i].has_value()) {
      std::cout << "[position system] Entity " << i << " not found !"
                << std::endl;
      continue;
    }
    if (entityType[i].has_value() && entityType[i] == EntityType::Enemy) {
      if (positions[i].has_value() && velocities[i].has_value()) {
        positions[i]->x += velocities[i]->x * deltaTime;
        positions[i]->y += velocities[i]->y * deltaTime;
        Command *command = new Command();
        command->type = CommandType::ENEMYMOVE;
        command->id = -10;
        command->enemyMove = new enemyMove();
        command->enemyMove->positionX = positions[i]->x;
        command->enemyMove->positionY = positions[i]->y;
        command->enemyMove->enemyId = i;
        queue->pushUdpQueue(command);
      }
    }
  }
}

void Game::enemy_system(std::shared_ptr<Queue> &queue) {
  auto &entityType = _ecs.get_components<EntityType>();
  auto &positions = _ecs.get_components<Position>();
  auto &health = _ecs.get_components<Health>();
  auto &velocities = _ecs.get_components<Velocity>();

  for (std::size_t i = 0; i < entityType.size(); ++i) {
    if (!entityType[i].has_value()) {
      std::cout << "[enemy system] Entity " << i << " not found !" << std::endl;
      continue;
    }
    if (entityType[i].has_value() && entityType[i] == EntityType::Enemy) {
      if (positions[i].has_value() && velocities[i].has_value()) {
        if (positions[i]->y < 0) {
          velocities[i]->y = 100;
        } else if (positions[i]->y > 1000) {
          velocities[i]->y = -100;
        }
        if (health[i]->hp <= 0) {
          _ecs.kill_entity(Entities(i));
        }
      }
    }
  }
}

Entities Game::create_player() {
  auto player = create_entity<EntityType::Player>(
      _ecs, Position(100, 100), Velocity(), Health(),
      Draw({0, 255, 0, 255}, {150, 150, 150, 150}));
  _players.push_back(player);
  return player;
};

bool Game::initialize() {
  // Implémentation de la méthode initialize
  return true;
}

void Game::run() {
  // Implémentation de la méthode run
}