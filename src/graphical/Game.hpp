/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Game
*/

#pragma once

#include "../ecs/Registry.hpp"
#include "Components/Control.hpp"
#include "Components/Draw.hpp"
#include "Components/Health.hpp"
#include "Components/Position.hpp"
#include "Components/Velocity.hpp"

void bullet_system(Registry &registry, float deltaTime);
void handle_bullet_shooting(Registry &registry, const Position &player_position);
void position_system(Registry &registry, float deltaTime);
void control_system(Registry &registry);
