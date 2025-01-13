#ifndef ENTITIESGESTION_HPP
#define ENTITIESGESTION_HPP

#include <random>
#include "../Components/Components.hpp"
#include "../../ecs/Entities.hpp"
#include "../../ecs/Registry.hpp"

enum class EntityType { Player, Enemy, Projectile, Menu };
enum class EnemyType { Pion, Balourd, Zinzolin, Boss, BigBoss};
enum class AiType { Aggressive, Passive, Balzy, Boss };

Entities create_player_entity(Registry &r, Position position, Velocity velocity,
                              Health health, Draw draw,
                              std::optional<Control> control = std::nullopt,
                              std::optional<std::size_t> id = std::nullopt);

Entities create_enemy_entity(Registry &r, Position position, Velocity velocity,
                             Health health, Draw draw,
                              AiType type = AiType::Aggressive, std::optional<std::size_t> id = std::nullopt);

Entities create_projectile_entity(Registry &r, Position position,
                                  Velocity velocity, Draw draw,
                                  std::optional<std::size_t> id = std::nullopt);


template <EntityType T, typename... Args>
Entities create_entity(Registry &r, Args &&...args) {
  if constexpr (T == EntityType::Player) {
    return create_player_entity(r, std::forward<Args>(args)...);
  }
  if constexpr (T == EntityType::Enemy) {
    return create_enemy_entity(r, std::forward<Args>(args)...);
  }
  if constexpr (T == EntityType::Projectile) {
    return create_projectile_entity(r, std::forward<Args>(args)...);
  }
}

template <EnemyType T>
Entities create_enemy(Registry &r, AiType type, SDL_Texture *enemyTexture) {
  static constexpr int y_min = -300;
  static constexpr int y_max = 300;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(y_min, y_max);

  int random_y = distrib(gen);
  std::cout << random_y << std::endl;

  if constexpr (T == EnemyType::Pion) {
    return create_entity<EntityType::Enemy>(r, Position(800, 0), Velocity(), Health(30), Draw({}, {}, enemyTexture), type);
  }
  if constexpr (T == EnemyType::Balourd) {
    return create_entity<EntityType::Enemy>(r, Position(800, 15), Velocity(), Health(50), Draw({}, {}, enemyTexture), type);
  }
  if constexpr (T == EnemyType::Zinzolin) {
    return create_entity<EntityType::Enemy>(r, Position(800, 30), Velocity(), Health(25), Draw({}, {}, enemyTexture), type);
  }
  if constexpr (T == EnemyType::Boss) {
    return create_entity<EntityType::Enemy>(r, Position(800, 45), Velocity(), Health(100), Draw({}, {}, enemyTexture), type);
  }
  if constexpr (T == EnemyType::BigBoss) {
    return create_entity<EntityType::Enemy>(r, Position(800, 60), Velocity(), Health(300), Draw({}, {}, enemyTexture), type);
  }
}

#endif // ENTITIESGESTION_HPP