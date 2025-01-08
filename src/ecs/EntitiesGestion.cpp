#include "EntitiesGestion.hpp"

Entities create_player_entity(Registry &r, Position position, Velocity velocity,
                              Health health, Draw draw,
                              std::optional<Control> control,
                              std::optional<std::size_t> id) {
  auto entity = id.has_value() ? r.spawn_entity(id.value()) : r.spawn_entity();
  r.add_component<Position>(entity, std::move(position));
  r.add_component<Velocity>(entity, std::move(velocity));
  r.add_component<Health>(entity, std::move(health));
  r.add_component<Draw>(entity, std::move(draw));
  if (control.has_value()) {
    r.add_component<Control>(entity, std::move(control.value()));
  }
  r.add_component<EntityType>(entity, EntityType::Player);
  return entity;
}

Entities create_enemy_entity(Registry &r, Position position, Velocity velocity,
                             Health health, Draw draw,
                             std::optional<std::size_t> id) {
  auto entity = id.has_value() ? r.spawn_entity(id.value()) : r.spawn_entity();
  r.add_component<Position>(entity, std::move(position));
  r.add_component<Velocity>(entity, std::move(velocity));
  r.add_component<Health>(entity, std::move(health));
  r.add_component<Draw>(entity, std::move(draw));
  r.add_component<Control>(entity, Control());
  r.add_component<EntityType>(entity, EntityType::Enemy);
  return entity;
}

Entities create_projectile_entity(Registry &r, Position position,
                                  Velocity velocity, Draw draw,
                                  std::optional<std::size_t> id) {
  auto entity = id.has_value() ? r.spawn_entity(id.value()) : r.spawn_entity();
  r.add_component<EntityType>(entity, EntityType::Projectile);
  r.add_component<Position>(entity, std::move(position));
  r.add_component<Velocity>(entity, std::move(velocity));
  r.add_component<Draw>(entity, std::move(draw));
  return entity;
}