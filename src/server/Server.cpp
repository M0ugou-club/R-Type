/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Server
*/

#include "Server.hpp"
#include "../graphical/Components/Position.hpp"
#include <iostream>
#include <thread>

Server::Server(std::size_t tcpPort, std::string tcpIp, std::size_t udpPort,
               std::string udpIp) {
  _tcp = std::make_unique<Tcp>(tcpPort, tcpIp);
  _udp = std::make_unique<UDP>(udpPort, udpIp);
  _queue = std::make_unique<Queue>();
  initCommandMapHandle();
  initCommandMapSend();
  initCommandMapGame();
}

Server::~Server() {}

void Server::listen(std::unique_ptr<IProtocol> &protocol) {
  while (true) {
    if (protocol->listenSocket()) {
      std::vector<uint8_t> buffer = protocol->getBuffer();
      std::vector<std::string> parsedBuffer;

      std::cout << "[" << protocol->getType() << "] "
                << std::string(buffer.begin(), buffer.end()) << std::endl;
      parsedBuffer = parseCommandBuffer(buffer);
      if (_commandsHandle.find(buffer[0]) != _commandsHandle.end()) {
        _commandsHandle[buffer[0]](parsedBuffer, protocol);
      } else {
        std::cout << "Code invalide !" << std::endl;
      }
    }
  }
}

void Server::world_update(){};

void Server::game_loop() {
  while (true) {
    Command *command = _queue->popGameQueue();
    if (!command) {
      continue;
    }
    if (_commandsGame.find(command->type) != _commandsGame.end()) {
      _commandsGame[command->type](command);
    }
    world_update();
  }
};

void Server::start() {
  if (!_tcp->initializeSocket() || !_tcp->bindSocket()) {
    throw std::runtime_error("Failed to initialize TCP.");
  }

  if (!_udp->initializeSocket() || !_udp->bindSocket()) {
    throw std::runtime_error("Failed to initialize UDP.");
  }

  std::thread tcpThread([this]() { listen(_tcp); });
  std::thread udpThread([this]() { listen(_udp); });
  std::thread gameThread([this]() { game_loop(); });

  tcpThread.join();
  udpThread.join();
  gameThread.join();
}
