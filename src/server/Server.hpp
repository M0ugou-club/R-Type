/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Server
*/

#pragma once

#include "Queue.hpp"
#include "game/Game.hpp"
#include "tcp/Tcp.hpp"
#include "udp/UDP.hpp"
#include <map>

class Server {
public:
  Server(std::size_t tcpPort, std::string tcpIp, std::size_t udpPort,
         std::string udpIp);
  ~Server();

  void listen(std::unique_ptr<IProtocol> &protocol);

  void start();

  void initCommandMapHandle();
  void initCommandMapSend();
  void initCommandMapGame();

  void connectCommandHandle(std::vector<uint8_t> buffer,
                            std::unique_ptr<IProtocol> &protocol);
  void disconnectCommandHandle(std::vector<uint8_t> buffer,
                               std::unique_ptr<IProtocol> &protocol);
  void moveCommandHandle(std::vector<uint8_t> buffer,
                         std::unique_ptr<IProtocol> &protocol);
  void shootCommandHandle(std::vector<uint8_t> buffer,
                          std::unique_ptr<IProtocol> &protocol);

  void connectCommandSend(Command *command,
                          std::unique_ptr<IProtocol> &protocol);
  void disconnectCommandSend(Command *command,
                             std::unique_ptr<IProtocol> &protocol);
  void newPlayerCommandSend(Command *command,
                            std::unique_ptr<IProtocol> &protocol);
  void moveCommandSend(Command *command, std::unique_ptr<IProtocol> &protocol);
  void shootCommandSend(Command *command, std::unique_ptr<IProtocol> &protocol);
  void mapCommandSend(Command *command, std::unique_ptr<IProtocol> &protocol);
  void enemyMoveCommandSend(Command *command,
                            std::unique_ptr<IProtocol> &protocol);
  void createEnemyCommandSend(Command *command,
                              std::unique_ptr<IProtocol> &protocol);
  void killEnemyCommandSend(Command *command,
                            std::unique_ptr<IProtocol> &protocol);

  void connectCommandGame(Command *command);
  void disconnectCommandGame(Command *command);
  void moveCommandGame(Command *command);
  void killEnemyCommandGame(Command *command);

  void game_loop();
  void world_update();

private:
  std::unique_ptr<IProtocol> _tcp;
  std::unique_ptr<IProtocol> _udp;
  Game _game;
  std::map<uint8_t, std::function<void(std::vector<uint8_t>,
                                       std::unique_ptr<IProtocol> &)>>
      _commandsHandle;
  std::map<CommandType,
           std::function<void(Command *, std::unique_ptr<IProtocol> &)>>
      _commandsSend;
  std::map<CommandType, std::function<void(Command *)>> _commandsGame;

  std::shared_ptr<Queue> _queue;
};
