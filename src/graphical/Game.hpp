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

void collision_system(Registry &registry) {
    auto &positions = registry.get_components<Position>();
    auto &drawables = registry.get_components<Draw>();

    for (std::size_t i = 0; i < positions.size(); ++i) {
        if (!positions[i] || !drawables[i])
            continue;
        Draw *enemyDraw = drawables[i].operator->();
        if (enemyDraw->color.r == 255 && enemyDraw->color.g == 0 && enemyDraw->color.b == 0) {
            float ex = positions[i]->x;
            float ey = positions[i]->y;
            float ew = (float)enemyDraw->rect.w;
            float eh = (float)enemyDraw->rect.h;

            for (std::size_t j = 0; j < positions.size(); ++j) {
                if (!positions[j] || !drawables[j])
                    continue;
                Draw *projDraw = drawables[j].operator->();
                if (projDraw->color.r == 0 && projDraw->color.g == 0 && projDraw->color.b == 255) {
                    float px = positions[j]->x;
                    float py = positions[j]->y;
                    float pw = (float)projDraw->rect.w;
                    float ph = (float)projDraw->rect.h;

                    bool collision = (px < ex + ew && px + pw > ex && py < ey + eh && py + ph > ey);
                    if (collision) {
                        std::cout << "Touché" << std::endl;
                    }
                }
            }
        }
    }
}

void handle_shoot(Registry &registry, Entities &entity) {
    auto &positions = registry.get_components<Position>();
    auto &drawables = registry.get_components<Draw>();

    auto projectile = registry.spawn_entity();
    registry.add_component<Position>(projectile, Position(positions[entity]->x + 50, positions[entity]->y + 20));
    registry.add_component<Velocity>(projectile, Velocity(200, 0));
    registry.add_component<Draw>(projectile, Draw({0, 0, 255, 255}, {10, 10, 10, 10}));

}

void get_space_event(Registry &registry, Entities &entity) {
    const bool *keyState = SDL_GetKeyboardState(NULL);
    
    if (keyState[SDL_SCANCODE_SPACE]) {
        handle_shoot(registry, entity);
    }
}

