/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** IScene
*/

#pragma once

#include "../../ecs/Registry.hpp"
#include "../../graphical/Utils.hpp"
#include "../../queue/Queue.hpp"
#include <iostream>

class IScene {
public:
  IScene() = default;
  ~IScene() = default;

  virtual std::string getName() const = 0;

  virtual sceneType loop(float deltaTime) = 0;

  virtual void setEcs(Registry *ecs) = 0;

  virtual void setQueue(Queue *queue) = 0;

  virtual void init() = 0;

protected:
};
