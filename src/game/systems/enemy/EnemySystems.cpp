/*
** EPITECH PROJECT, 2025
** RType
** File description:
** EnemySystems
*/

#include "EnemySystems.hpp"

void call_enemy_ai(Registry *ecs, AiType type, std::size_t enemy) {
  const std::map<AiType, std::function<void()>> type_map = {
      {AiType::Aggressive, [&]() { aggresive_ai(ecs, enemy); }},
      {AiType::Passive, [&]() { passive_ai(ecs, enemy); }},
      {AiType::Balzy, [&]() { balzy_ai(ecs, enemy); }},
      {AiType::Boss, [&]() { boss_ai(ecs, enemy); }}};
  auto it = type_map.find(type);
  if (it != type_map.end()) {
    it->second();
  } else {
    std::cout << "Unknown enemy type" << std::endl;
    return;
  }
}

void enemy_system(Registry *ecs, bool nextWave) {
  auto &entityType = ecs->get_components<EntityType>();
  auto &aiType = ecs->get_components<AiType>();
  auto &velocity = ecs->get_components<Velocity>();
  static int entry_distance = 0;

  if (nextWave) {
    entry_distance = 0;
  }
  entry_distance += 10;
  for (std::size_t i = 0; i < entityType.size(); i++) {
    if (entityType[i] == EntityType::Enemy) {
      if (entry_distance < 750) {
        velocity[i]->x = -10;
        velocity[i]->y = 0;
        continue;
      }
      velocity[i]->x = 0;
      if (aiType[i] == AiType::Aggressive) {
        call_enemy_ai(ecs, AiType::Aggressive, i);
      }
      if (aiType[i] == AiType::Passive) {
        call_enemy_ai(ecs, AiType::Passive, i);
      }
      if (aiType[i] == AiType::Balzy) {
        call_enemy_ai(ecs, AiType::Balzy, i);
      }
      if (aiType[i] == AiType::Boss) {
        call_enemy_ai(ecs, AiType::Boss, i);
      }
    }
  }
}