/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** UDP
*/

#include "UDP.hpp"
#include <arpa/inet.h>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <unistd.h>

UDP::UDP(std::size_t port, std::string ip) {
  _port = port;
  _ip = ip;
}

UDP::~UDP() { closeSocket(); }

bool UDP::initializeSocket() {
  _socket = socket(AF_INET, SOCK_DGRAM, 0);
  if (_port <= 0 || _ip.empty() || _socket < 0) {
    throw std::runtime_error("Failed to create UDP socket.");
    return false;
  }

  _addr.sin_family = AF_INET;
  _addr.sin_port = htons(_port);

  if (inet_pton(AF_INET, _ip.c_str(), &_addr.sin_addr) <= 0) {
    throw std::runtime_error("Invalid IP address.");
    return false;
  }

  std::cout << "[DEBUG] UDP socket initialized on " << _ip << ":" << _port
            << std::endl;
  return true;
}

bool UDP::bindSocket() {
  if (bind(_socket, (sockaddr *)&_addr, sizeof(_addr)) < 0) {
    perror("Bind failed");
    throw std::runtime_error("Failed to bind UDP socket.");
    return false;
  }
  std::cout << "[DEBUG] UDP socket bound to " << _ip << ":" << _port
            << std::endl;
  return true;
}

bool UDP::sendData(const std::string &data, const std::string &destIp,
                   std::size_t destPort) {
  sockaddr_in destAddr{};
  destAddr.sin_family = AF_INET;
  destAddr.sin_port = htons(destPort);

  if (inet_pton(AF_INET, destIp.c_str(), &destAddr.sin_addr) <= 0) {
    throw std::runtime_error("Invalid destination IP address.");
    return false;
  }

  ssize_t sentBytes = sendto(_socket, data.c_str(), data.size(), 0,
                             (sockaddr *)&destAddr, sizeof(destAddr));
  if (sentBytes < 0) {
    perror("Sendto failed");
    throw std::runtime_error("Failed to send data over UDP.");
    return false;
  }

  return true;
}

std::vector<uint8_t> UDP::receiveData() {
  sockaddr_in senderAddr{};
  socklen_t senderAddrLen = sizeof(senderAddr);
  uint8_t buffer[1024];
  std::memset(buffer, 0, sizeof(buffer));

  ssize_t bytesReceived = recvfrom(_socket, buffer, sizeof(buffer) - 1, 0,
                                   (sockaddr *)&senderAddr, &senderAddrLen);
  if (bytesReceived < 0) {
    perror("Recvfrom failed");
    throw std::runtime_error("Failed to receive data over UDP.");
  }

  std::string senderIp = inet_ntoa(senderAddr.sin_addr);
  std::vector<uint8_t> data(buffer, buffer + bytesReceived);
  std::cout << "[UDP] Received data from " << senderIp << ":"
            << ntohs(senderAddr.sin_port) << std::endl;
  std::cout << "[UDP] Data size: " << std::endl;
  std::cout << "[UDP] Data: " << std::string(data.begin(), data.end())
            << std::endl;

  try {
    std::string deserialized_data = deserialize_connect(data);
    std::cout << "Deserialized data: " << deserialized_data << std::endl;
  } catch (const std::runtime_error &e) {
    std::cerr << "Failed to deserialize data: " << e.what() << std::endl;
  }

  return data;
}

std::string UDP::deserialize_connect(const std::vector<uint8_t> &data) {
  if (data.size() < 3 || data[0] != 0x01) {
    throw std::runtime_error("Invalid connect packet.");
  }

  uint16_t payload_size = ntohs((data[1] << 8) | data[2]);
  if (data.size() < 3 + payload_size) {
    throw std::runtime_error("Incomplete connect packet.");
  }

  std::string deserialized_data(data.begin() + 3,
                                data.begin() + 3 + payload_size);
  return deserialized_data;
}

bool UDP::listenSocket(int backlog) {
  while (true) {
    sockaddr_in clientAddr{};
    socklen_t clientAddrLen = sizeof(clientAddr);
    std::vector<uint8_t> completeMessage;

    while (true) {
      uint8_t buffer[1024];
      std::memset(buffer, 0, sizeof(buffer));

      ssize_t bytesReceived = recvfrom(_socket, buffer, sizeof(buffer) - 1, 0,
                                       (sockaddr *)&clientAddr, &clientAddrLen);
      if (bytesReceived > 0) {
        completeMessage.insert(completeMessage.end(), buffer,
                               buffer + bytesReceived);
        if (bytesReceived < static_cast<ssize_t>(sizeof(buffer))) {
          break;
        }
      } else {
        break;
      }
    }

    if (!completeMessage.empty()) {
      std::string senderIp = inet_ntoa(clientAddr.sin_addr);
      std::cout << "[UDP INFO] Received data from " << senderIp << ":"
                << ntohs(clientAddr.sin_port) << std::endl;

      if (completeMessage[0] == 0x03) {
        std::cout << "Move" << std::endl;
        std::cout << std::string(completeMessage.begin(), completeMessage.end())
                  << std::endl;
      }

      std::string response =
          "Acknowledged: " +
          std::string(completeMessage.begin(), completeMessage.end());
      sendto(_socket, response.c_str(), response.size(), 0,
             (sockaddr *)&clientAddr, clientAddrLen);
    }
  }
}

int UDP::acceptConnection() { return 0; }

void UDP::closeSocket() {
  if (_socket >= 0) {
    close(_socket);
    _socket = -1;
    std::cout << "[DEBUG] UDP socket closed." << std::endl;
  }
}
