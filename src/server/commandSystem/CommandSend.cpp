/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** CommandSend
*/

#include "CommandSend.hpp"

CommandSend::CommandSend() {
  _commandMap[CommandType::REPCONNECT] = [this](Command command,
                                                IProtocol *protocol) {
    connect(command, protocol);
  };
  _commandMap[CommandType::SHOOT] = [this](Command command,
                                           IProtocol *protocol) {
    shoot(command, protocol);
  };
  _commandMap[CommandType::MOVE] =
      [this](Command command, IProtocol *protocol) { move(command, protocol); };
  _commandMap[CommandType::CREATEENEMY] = [this](Command command,
                                                 IProtocol *protocol) {
    createEnemy(command, protocol);
  };
  _commandMap[CommandType::KILLENEMY] = [this](Command command,
                                               IProtocol *protocol) {
    killEnemy(command, protocol);
  };
  _commandMap[CommandType::NEWPLAYER] = [this](Command command,
                                               IProtocol *protocol) {
    newPlayer(command, protocol);
  };
  _commandMap[CommandType::CREATEPLAYER] = [this](Command command,
                                                  IProtocol *protocol) {
    createPlayer(command, protocol);
  };
  _commandMap[CommandType::STARTGAME] = [this](Command command,
                                               IProtocol *protocol) {
    startGame(command, protocol);
  };
}

CommandSend::~CommandSend() {}

void CommandSend::executeCommandSend(Command command, IProtocol *protocol) {
  if (_commandMap.find(command.type) != _commandMap.end()) {
    _commandMap[command.type](command, protocol);
  } else {
    std::cout << "Invalid command type! [Send]" << std::endl;
  }
}

void CommandSend::connect(Command command, IProtocol *protocol) {
    std::vector<uint8_t> binaryData;
    binaryData.push_back(0x01);

    binaryData.push_back(static_cast<uint8_t>(command.repConnect.id));

    uint8_t *positionXBytes = reinterpret_cast<uint8_t *>(&command.repConnect.positionX);
    binaryData.insert(binaryData.end(), positionXBytes, positionXBytes + sizeof(float));

    uint8_t *positionYBytes = reinterpret_cast<uint8_t *>(&command.repConnect.positionY);
    binaryData.insert(binaryData.end(), positionYBytes, positionYBytes + sizeof(float));

    protocol->sendData(command.id, binaryData);
}


void CommandSend::disconnect(Command command, IProtocol *protocol) {
  std::cout << "Disconnect command" << std::endl;
  std::string response;

  response = "disconnect OK"; // ici faut faire la commande disconnect si un
                              // joeur dans la partie c'est deconnecté

  // _protocol->sendData(command.id, binaryData);
}

void CommandSend::move(Command command, IProtocol *protocol) {
  std::vector<uint8_t> binaryData;

  binaryData.push_back(0x03);

  binaryData.push_back(static_cast<uint8_t>(command.move.entityId));

  uint8_t *positionXBytes = reinterpret_cast<uint8_t *>(&command.move.positionX);
  binaryData.insert(binaryData.end(), positionXBytes, positionXBytes + sizeof(float));

  uint8_t *positionYBytes = reinterpret_cast<uint8_t *>(&command.move.positionY);
  binaryData.insert(binaryData.end(), positionYBytes, positionYBytes + sizeof(float));

  protocol->sendDataToAllExceptOne(command.id, binaryData);
}

void CommandSend::shoot(Command command, IProtocol *protocol) {
  std::cout << "Shoot command" << std::endl;
  std::string response;

  response =
      "Shoot OK"; // ici faut faire la commande shoot si le mec a le droit tiré

  // protocol->sendData(response);
}

void CommandSend::map(Command command, IProtocol *protocol) {
  std::cout << "Map command" << std::endl;
  // std::vector<uint8_t> binaryData;

  // binaryData.push_back(0x04);

  // uint32_t playerId = command.move.playerId;

  // protocol->sendData(command.id, binaryData);
}

void CommandSend::createEnemy(Command command, IProtocol *protocol) {
  std::vector<uint8_t> binaryData;

  binaryData.push_back(0x06);

  binaryData.push_back(static_cast<uint8_t>(command.createEnemy.enemyId));

  uint8_t *positionXBytes = reinterpret_cast<uint8_t *>(&command.createEnemy.positionX);
  binaryData.insert(binaryData.end(), positionXBytes, positionXBytes + sizeof(float));

  uint8_t *positionYBytes = reinterpret_cast<uint8_t *>(&command.createEnemy.positionY);
  binaryData.insert(binaryData.end(), positionYBytes, positionYBytes + sizeof(float));

  protocol->sendData(command.id, binaryData);
}

void CommandSend::killEnemy(Command command, IProtocol *protocol) {
  std::vector<uint8_t> binaryData;

  binaryData.push_back(0x07);

  binaryData.push_back(static_cast<uint8_t>(command.killEnemy.enemyId));

  protocol->sendDataToAll(binaryData);
}

void CommandSend::newPlayer(Command command, IProtocol *protocol) {
  std::vector<uint8_t> binaryData;

  binaryData.push_back(0x08);
  
  binaryData.push_back(static_cast<uint8_t>(command.newPlayer.id));

  uint8_t *positionXBytes = reinterpret_cast<uint8_t *>(&command.newPlayer.positionX);
  binaryData.insert(binaryData.end(), positionXBytes, positionXBytes + sizeof(float));

  uint8_t *positionYBytes = reinterpret_cast<uint8_t *>(&command.newPlayer.positionY);
  binaryData.insert(binaryData.end(), positionYBytes, positionYBytes + sizeof(float));

  binaryData.push_back(static_cast<uint8_t>(command.newPlayer.Nickname.size()));
  std::string playerName = command.newPlayer.Nickname;
  for (auto &c : playerName)
    binaryData.push_back(static_cast<uint8_t>(c));

  protocol->sendDataToAllExceptOne(command.id, binaryData);
}

void CommandSend::createPlayer(Command command, IProtocol *protocol) {
  std::vector<uint8_t> binaryData;

  binaryData.push_back(0x08);

  std::string playerName = command.createPlayer.Nickname;

  binaryData.push_back(static_cast<uint8_t>(command.createPlayer.id));

  uint8_t *positionXBytes = reinterpret_cast<uint8_t *>(&command.createPlayer.positionX);
  binaryData.insert(binaryData.end(), positionXBytes, positionXBytes + sizeof(float));

  uint8_t *positionYBytes = reinterpret_cast<uint8_t *>(&command.createPlayer.positionY);
  binaryData.insert(binaryData.end(), positionYBytes, positionYBytes + sizeof(float));

  binaryData.push_back(static_cast<uint8_t>(command.createPlayer.Nickname.size()));

  for (auto &c : playerName)
    binaryData.push_back(static_cast<uint8_t>(c));

  protocol->sendData(command.id, binaryData);
}

void CommandSend::startGame(Command command, IProtocol *protocol) {
  std::vector<uint8_t> binaryData;

  binaryData.push_back(0x09);

  std::string response = "\r\n";

  for (auto &c : response) {
    binaryData.push_back(static_cast<uint8_t>(c));
  }

  protocol->sendDataToAll(binaryData);
}
