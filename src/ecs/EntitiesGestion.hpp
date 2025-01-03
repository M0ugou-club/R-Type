#ifndef ENTITIESGESTION_HPP
#define ENTITIESGESTION_HPP

#include "../graphical/Components/Control.hpp"
#include "../graphical/Components/Draw.hpp"
#include "../graphical/Components/Health.hpp"
#include "../graphical/Components/Position.hpp"
#include "../graphical/Components/Velocity.hpp"
#include "Entities.hpp"
#include "Registry.hpp"

enum class EntityType {
  Player,
  Enemy,
  Projectile,
};

Entities create_player_entity(Registry &r, Position position, Velocity velocity,
                              Health health, Draw draw);

Entities create_enemy_entity(Registry &r);

Entities create_projectile_entity(Registry &r);

template <EntityType T, typename... Args>
Entities create_entity(Registry &r, Args &&...args) {
  switch (T) {
  case EntityType::Player:
    return create_player_entity(r, std::forward<Args>(args)...);
  case EntityType::Enemy:
    return create_enemy_entity(r);
  case EntityType::Projectile:
    return create_projectile_entity(r);
  }
}

#endif // ENTITIESGESTION_HPP