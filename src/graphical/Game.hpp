/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Game
*/

#pragma once

#include "Components/Control.hpp"
#include "Components/Draw.hpp"
#include "Components/Health.hpp"
#include "Components/Position.hpp"
#include "Components/Velocity.hpp"
#include "../ecs/SparseArray.hpp"
#include "../ecs/EntitiesGestion.hpp"


void enemy_system(Registry &registry, Entities &enemy) {
    if (registry.get_components<Position>()[enemy]->y < 0) {
        registry.get_components<Velocity>()[enemy]->y = 100;
    } else if (registry.get_components<Position>()[enemy]->y > 600) {
        registry.get_components<Velocity>()[enemy]->y = -100;
    }
}

void collision_system(Registry &registry, Entities &enemy, Entities &player) {
    auto &positions = registry.get_components<Position>();
    auto &drawables = registry.get_components<Draw>();
    auto &controls = registry.get_components<Control>();

    for (std::size_t i = 0; i < positions.size(); ++i) {
        if (positions[i] && drawables[i]) {
            if (i == enemy || i == player) {
                continue;
            }
            if (positions[i]->x < positions[enemy]->x + drawables[enemy]->rect.w &&
                positions[i]->x + drawables[i]->rect.w > positions[enemy]->x &&
                positions[i]->y < positions[enemy]->y + drawables[enemy]->rect.h &&
                positions[i]->y + drawables[i]->rect.h > positions[enemy]->y) {
                std::cout << "Touché" << std::endl;
            }
        }
    }
}

void handle_shoot(Registry &registry, Entities &entity) {
    auto &positions = registry.get_components<Position>();
    auto &drawables = registry.get_components<Draw>();

    auto projectile = registry.spawn_entity();
    registry.add_component<Position>(projectile, Position(positions[entity]->x + 50, positions[entity]->y + 20));
    registry.add_component<Velocity>(projectile, Velocity(400, 0));
    registry.add_component<Draw>(projectile, Draw({0, 0, 255, 255}, {10, 10, 10, 10}));

}

void get_space_event(Registry &registry, Entities &entity) {
    const bool *keyState = SDL_GetKeyboardState(NULL);
    
    if (keyState[SDL_SCANCODE_SPACE]) {
        handle_shoot(registry, entity);
    }
}

