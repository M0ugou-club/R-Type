/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** AScene
*/

#pragma once

#include "../../ecs/Registry.hpp"
#include "../../game/Components/Components.hpp"
#include "../../game/gestion/EntitiesGestion.hpp"
#include "../../game/systems/enemy/EnemySystems.hpp"
#include "../../game/systems/global/GlobalSystem.hpp"
#include "IScene.hpp"
#include "utils/Wave.hpp"

class AScene : public IScene {
public:
  AScene();
  ~AScene();

  std::string getName() const override;

  void setEcs(Registry *ecs) override;

  void setQueue(Queue *queue) override;

  void setGamemode(int gamemode) override;

  void setLevel(std::string level) override;

protected:
  std::string _name;
  Registry *_ecs;
  Queue *_queue;
  Wave _wave;
  std::chrono::time_point<std::chrono::steady_clock> _nextCorrectPosition;
  int _gamemode;
  std::string _level;
};
