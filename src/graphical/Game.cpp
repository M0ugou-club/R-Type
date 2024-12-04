/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Game
*/

#include "Game.hpp"

void bullet_system(Registry &registry, float deltaTime)
{
    auto &positions = registry.get_components<Position>();
    auto &velocities = registry.get_components<Velocity>();

    for (std::size_t i = 0; i < positions.size(); ++i)
    {
        if (positions[i] && velocities[i])
        {
            positions[i]->x += velocities[i]->x * deltaTime;
            positions[i]->y += velocities[i]->y * deltaTime;
        }
    }
}

void handle_bullet_shooting(Registry &registry, const Position &player_position)
{
    const bool *keyState = SDL_GetKeyboardState(NULL);

    static bool spaceWasPressed = false;

    if (keyState[SDL_SCANCODE_SPACE])
    {
        if (!spaceWasPressed)
        {
            auto bullet = registry.spawn_entity();
            registry.add_component<Position>(bullet, Position(player_position.x + 50, player_position.y + 20));
            registry.add_component<Velocity>(bullet, Velocity(200, 0));
            registry.add_component<Draw>(bullet, Draw({255, 255, 255, 255}, {0, 0, 10, 10}));

            spaceWasPressed = true;
        }
    }
    else
    {
        spaceWasPressed = false;
    }
}

void position_system(Registry &registry, float deltaTime)
{
    auto &positions = registry.get_components<Position>();
    auto &velocities = registry.get_components<Velocity>();

    for (std::size_t i = 0; i < positions.size(); ++i)
    {
        if (positions[i] && velocities[i])
        {
            positions[i]->x += velocities[i]->x * deltaTime;
            positions[i]->y += velocities[i]->y * deltaTime;
        }
    }
}

void control_system(Registry &registry)
{
    const bool *keyState = SDL_GetKeyboardState(NULL);

    auto &controllables = registry.get_components<Control>();
    auto &velocities = registry.get_components<Velocity>();

    for (std::size_t i = 0; i < controllables.size(); ++i)
    {
        if (controllables[i] && velocities[i])
        {
            velocities[i]->x = 0;
            velocities[i]->y = 0;

            if (keyState[SDL_SCANCODE_UP])
                velocities[i]->y = -100;
            if (keyState[SDL_SCANCODE_DOWN])
                velocities[i]->y = 100;
            if (keyState[SDL_SCANCODE_LEFT])
                velocities[i]->x = -100;
            if (keyState[SDL_SCANCODE_RIGHT])
                velocities[i]->x = 100;

            controllables[i]->reset();
        }
    }
}