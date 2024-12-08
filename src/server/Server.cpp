/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Server
*/

#include "Server.hpp"
#include <iostream>
#include <thread>

Server::Server(std::size_t tcpPort, std::string tcpIp, std::size_t udpPort,
               std::string udpIp) {
  _tcp = std::make_unique<Tcp>(tcpPort, tcpIp);
  _udp = std::make_unique<UDP>(udpPort, udpIp);
  _ecs = std::make_unique<Registry>();
}

Server::~Server() {}

void Server::start() {
  if (!_tcp->initializeSocket() || !_tcp->bindSocket()) {
    throw std::runtime_error("Failed to initialize TCP.");
  }

  if (!_udp->initializeSocket() || !_udp->bindSocket()) {
    throw std::runtime_error("Failed to initialize UDP.");
  }

  std::thread tcpThread([this]() { _tcp->listenSocket(); });
  std::thread udpThread([this]() { _udp->listenSocket(); });

  tcpThread.join();
  udpThread.join();
}