/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Protocol
*/

#include "Protocol.hpp"

Protocol::Protocol()
{
    initCommandMap();
}

Protocol::~Protocol()
{
}

void Protocol::initCommandMap()
{
    _commands[0x01] = [this](std::vector<uint8_t> buffer, std::unique_ptr<Registry> &reg) {
        connectCommand(buffer, reg);
    };
    _commands[0x02] = [this](std::vector<uint8_t> buffer, std::unique_ptr<Registry> &reg) {
        disconnectCommand(buffer, reg);
    };
    _commands[0x03] = [this](std::vector<uint8_t> buffer, std::unique_ptr<Registry> &reg) {
        moveCommand(buffer, reg);
    };
    _commands[0x04] = [this](std::vector<uint8_t> buffer, std::unique_ptr<Registry> &reg) {
        hitCommand(buffer, reg);
    };
    _commands[0x07] = [this](std::vector<uint8_t> buffer, std::unique_ptr<Registry> &reg) {
        killCommand(buffer, reg);
    };
}

void Protocol::connectCommand(std::vector<uint8_t> buffer, std::unique_ptr<Registry> &reg)
{

}

void Protocol::disconnectCommand(std::vector<uint8_t> buffer, std::unique_ptr<Registry> &reg)
{
    
}

void Protocol::moveCommand(std::vector<uint8_t> buffer, std::unique_ptr<Registry> &reg)
{
    int entityId = buffer[1];
    reg->get_components<Position>()[entityId]->x = buffer[2];
    reg->get_components<Position>()[entityId]->y = buffer[3];
}

void Protocol::hitCommand(std::vector<uint8_t> buffer, std::unique_ptr<Registry> &reg)
{
    int entityId = buffer[1];
    reg->get_components<Health>()[entityId]->hp -= buffer[2];
}

void Protocol::killCommand(std::vector<uint8_t> buffer, std::unique_ptr<Registry> &reg)
{
    int entityId = buffer[1];
    reg->kill_entity(Entities (entityId));
}
