/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** UDP
*/

#pragma once

#include "../AProtocol.hpp"

class UDP : public AProtocol {
public:
  UDP(std::size_t port = 4242, std::string ip = "0.0.0.0");
  ~UDP();

  bool initializeSocket() override;
  bool bindSocket() override;
  bool sendData(const std::string &data, const std::string &destIp,
                std::size_t destPort) override;
  std::string receiveData() override;
  void closeSocket() override;
  int getSocket() override;
  bool listenSocket(int backlog = 5) override;
  int acceptConnection() override;

    private:
        std::size_t _port;
        std::string _ip;
        sockaddr_in _addr;
        int _socket;
};
