/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Connexion
*/

#pragma once

#include "IProtocol.hpp"
#include "TcpClient.hpp"
#include "UdpClient.hpp"
#include <arpa/inet.h>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <stdexcept>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>
#include <vector>

class Connexion {
public:
  Connexion(const std::string &ip_udp, int port_udp, const std::string &ip_tcp,
            int port_tcp);
  ~Connexion();

  void listen(std::unique_ptr<IProtocol> &protocol);

private:
  std::unique_ptr<IProtocol> _tcp;
  std::unique_ptr<IProtocol> _udp;
};
