/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Game
*/

#pragma once

#include "Utils.hpp"
#include "Window.hpp"
#include "network/IClient.hpp"
#include "network/Tcp.hpp"
#include "network/Udp.hpp"
#include "scenes/EndLess.hpp"
#include "scenes/History.hpp"
#include "scenes/IScene.hpp"
#include "scenes/Menu.hpp"
#include "scenes/OneVsOne.hpp"
#include "../ecs/Registry.hpp"
#include "Components/Control.hpp"
#include "Components/Draw.hpp"
#include "Components/Health.hpp"
#include "Components/Position.hpp"
#include "Components/Velocity.hpp"
#include "../ecs/EntitiesGestion.hpp"
#include <iostream>
#include <map>
#include <memory>

class Game {
public:
  Game();
  ~Game();

  void load_component() {
    _ecs.register_component<Position>();
    _ecs.register_component<Velocity>();
    _ecs.register_component<Draw>();
    _ecs.register_component<Health>();
    _ecs.register_component<Control>();
    _ecs.register_component<EntityType>();
  };

  void loadScene(sceneType sceneName);
  std::string getCurrentSceneName();

  void listen(IClient &protocol);

  void init();
  void game();

private:
  std::map<sceneType, std::shared_ptr<IScene>> _scenes;
  sceneType _currentScene;

  std::shared_ptr<Window> _window;

  std::shared_ptr<IClient> _tcp;
  std::shared_ptr<IClient> _udp;

  Registry _ecs;
};
