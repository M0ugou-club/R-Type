/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Protocol
*/

#pragma once

#include <map>
#include "../ecs/Registry.hpp"
#include "Game.hpp"
#include "Components/Position.hpp"
#include "Components/Health.hpp"


class Protocol {
    public:
        Protocol();
        ~Protocol();

        void initCommandMap();
        void connectCommand(std::vector<uint8_t> buffer, std::unique_ptr<Registry> &reg);
        void disconnectCommand(std::vector<uint8_t> buffer, std::unique_ptr<Registry> &reg);
        void moveCommand(std::vector<uint8_t> buffer, std::unique_ptr<Registry> &reg);
        void hitCommand(std::vector<uint8_t> buffer, std::unique_ptr<Registry> &reg);
        void killCommand(std::vector<uint8_t> buffer, std::unique_ptr<Registry> &reg);

    protected:
    private:

    std::map<uint8_t, std::function<void(std::vector<uint8_t>, std::unique_ptr<Registry> &)>> _commands;
};
