/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Commands
*/

#pragma once

#include "../ecs/Registry.hpp"
#include "Components/Control.hpp"
#include "Components/Draw.hpp"
#include "Components/Health.hpp"
#include "Components/Position.hpp"
#include "Components/Velocity.hpp"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <cstring>
#include <map>
#include <sstream>
#include <vector>

std::vector<std::string> my_strToWordArray(const std::string &str,
                                           char delimiter);

void connectCommand(std::string buffer, Registry &registry,
                    SDL_Renderer *renderer);

void moveEntity(std::string buffer, Registry &registry, SDL_Renderer *renderer);

void createEntity(std::string buffer, Registry &registry,
                  SDL_Renderer *renderer);

void killEntity(std::string buffer, Registry &registry, SDL_Renderer *renderer);