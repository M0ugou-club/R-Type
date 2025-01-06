/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** CommandGame
*/

#include "CommandGame.hpp"

CommandGame::CommandGame() {
  _commandMap[CommandType::REPCONNECT] = [this](Command command, Queue *queue,
                                                Registry *ecs, Window *window) {
    std::cout  << "CommandGame REPCONNECT" << std::endl;
    connect(command, queue, ecs, window);
  };
  _commandMap[CommandType::DISCONNECT] = [this](Command command, Queue *queue,
                                                Registry *ecs, Window *window) {
    disconnect(command, queue, ecs, window);
  };
  _commandMap[CommandType::MOVE] = [this](Command command, Queue *queue,
                                          Registry *ecs, Window *window) {
    move(command, queue, ecs, window);
  };
  _commandMap[CommandType::KILLENEMY] = [this](Command command, Queue *queue,
                                               Registry *ecs, Window *window) {
    killEnemy(command, queue, ecs, window);
  };
  _commandMap[CommandType::CREATEENEMY] =
      [this](Command command, Queue *queue, Registry *ecs, Window *window) {
        createEnemy(command, queue, ecs, window);
      };
  _commandMap[CommandType::ENEMYMOVE] = [this](Command command, Queue *queue,
                                               Registry *ecs, Window *window) {
    enemyMove(command, queue, ecs, window);
  };
}

CommandGame::~CommandGame() {}

void CommandGame::executeCommandGame(Command command, Queue *queue,
                                     Registry *ecs, Window *window) {
  std::cout << "Execute command game" << std::endl;
  if (_commandMap.find(command.type) != _commandMap.end()) {
    _commandMap[command.type](command, queue, ecs, window);
  } else {
    std::cout << "Invalid command type! [Game]" << std::endl;
  }
}

void CommandGame::connect(Command command, Queue *queue, Registry *ecs,
                          Window *window) {
  SDL_Texture *playerTexture =
      window->loadTexture("../src/graphical/assets/michou.png");

  std::cout << "connect command game !!!!!!!!!!!!" << std::endl;
  std::cout << "player game id : " << command.repConnect.id << std::endl;
  std::cout << "player game positionX : " << command.repConnect.positionX << std::endl;
  std::cout << "player game positionY : " << command.repConnect.positionY << std::endl;

  auto player = create_entity<EntityType::Player>(
      *ecs,
      Position(command.repConnect.positionX, command.repConnect.positionY),
      Velocity(), Health(1),
      Draw({0, 255, 0, 255}, {100, 150, 50, 50}, playerTexture),
      std::optional<Control>(Control()),
      std::optional<std::size_t>(command.repConnect.id));
}

void CommandGame::disconnect(Command command, Queue *queue, Registry *ecs,
                             Window *window) {
  std::cout << "disconnect command" << std::endl;
}

void CommandGame::move(Command command, Queue *queue, Registry *ecs,
                       Window *window) {
  std::cout << "move command" << std::endl;
}

void CommandGame::killEnemy(Command command, Queue *queue, Registry *ecs,
                            Window *window) {
  std::cout << "killEnemy command" << std::endl;
}

void CommandGame::createEnemy(Command command, Queue *queue, Registry *ecs,
                              Window *window) {
  SDL_Texture *enemyTexture =
      window->loadTexture("../src/graphical/assets/enemy.png");

  auto enemy = create_entity<EntityType::Enemy>(
      *ecs,
      Position(command.createEnemy.positionX, command.createEnemy.positionY),
      Velocity(0, -50), Health(1),
      Draw({0, 255, 0, 255}, {100, 150, 50, 50}, enemyTexture),
      std::optional<std::size_t>(command.createEnemy.enemyId));
}

void CommandGame::enemyMove(Command command, Queue *queue, Registry *ecs,
                            Window *window) 
{
  std::cout << "enemyMove command Dans le game" << std::endl;
  auto &entities = ecs->get_components<EntityType>();
  auto &positions = ecs->get_components<Position>();

  for (std::size_t i = 0; i < entities.size(); ++i) {
    if (entities[i] == EntityType::Enemy && positions[i].has_value()) {
      std::cout << "Enemy trouvé dans le move " << std::endl;
      positions[i]->x = command.enemyMove.positionX;
      positions[i]->y = command.enemyMove.positionY;
    }
  }
}