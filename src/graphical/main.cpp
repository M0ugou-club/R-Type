/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** main
*/

#include "../ecs/Registry.hpp"
#include "TcpClient.hpp"
#include "UdpClient.hpp"
#include "Components/Control.hpp"
#include "Components/Draw.hpp"
#include "Components/Health.hpp"
#include "Components/Position.hpp"
#include "Components/Velocity.hpp"
#include <SDL3/SDL.h>
#include <iostream>
#include <vector>
#include "Game.hpp"

void draw_system(Registry &registry, SDL_Renderer *renderer)
{
  auto &positions = registry.get_components<Position>();
  auto &drawables = registry.get_components<Draw>();

  for (std::size_t i = 0; i < positions.size(); ++i)
  {
    if (positions[i] && drawables[i])
    {
      SDL_FRect rect = {static_cast<float>(positions[i]->x),
                        static_cast<float>(positions[i]->y),
                        static_cast<float>(drawables[i]->rect.w),
                        static_cast<float>(drawables[i]->rect.h)};
      SDL_SetRenderDrawColor(renderer, drawables[i]->color.r,
                             drawables[i]->color.g, drawables[i]->color.b,
                             drawables[i]->color.a);
      SDL_RenderFillRect(renderer, &rect);
    }
  }
}

std::vector<uint8_t> serialize_connect(const std::string &player_name)
{
  std::vector<uint8_t> packet;
  packet.push_back(0x01);
  uint16_t payload_size = htons(player_name.size());
  packet.push_back((payload_size >> 8) & 0xFF);
  packet.push_back(payload_size & 0xFF);
  for (char c : player_name)
    packet.push_back(static_cast<uint8_t>(c));
  return packet;
}

int main()
{

  //   try {
  //     TcpClient tcp("127.0.0.1", 12345);
  //     UdpClient udp("127.0.0.1", 12346);

  //     std::string player_name = "Player";
  //     auto connect_packet = serialize_connect(player_name);

  //     tcp.send_data(connect_packet);

  //     while (true) {
  //       std::vector<uint8_t> move_packet = {0x04, 0x01, 0x02};
  //       udp.send_data(move_packet);

  //       std::vector<uint8_t> response;
  //       tcp.receive_data(response);

  //       // Process server response (not implemented)
  //     }

  //   } catch (const std::exception &e) {
  //     std::cerr << "Error: " << e.what() << std::endl;
  //     return 1;
  //   }
    std::cout << "SDL Version: " << SDL_GetVersion() << std::endl;
    if (SDL_Init(SDL_INIT_VIDEO) == 0)
    {
        std::cerr << "SDL Initialization failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("ECS Draw System", 800, 600, 0);
    if (!window)
    {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer)
    {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    Registry registry;

    registry.register_component<Position>();
    registry.register_component<Velocity>();
    registry.register_component<Draw>();
    registry.register_component<Control>();
    registry.register_component<Health>();

    auto player = registry.spawn_entity();
    registry.add_component<Position>(player, Position(100, 150));
    registry.add_component<Velocity>(player, Velocity());
    registry.add_component<Health>(player, Health());
    registry.add_component<Draw>(
        player, Draw({0, 255, 0, 255}, {100, 150, 50, 50}));
    registry.add_component<Control>(player, Control());

    auto ennemy = registry.spawn_entity();
    registry.add_component<Position>(ennemy, Position(600, 300));
    registry.add_component<Velocity>(ennemy, Velocity());
    registry.add_component<Health>(ennemy, Health());
    registry.add_component<Draw>(
        ennemy, Draw({255, 0, 0, 255}, {500, 150, 50, 50}));

    bool running = true;
    SDL_Event event;
    Uint64 now = SDL_GetPerformanceCounter();
    Uint64 last = 0;
    float deltaTime = 0;

    while (running)
    {
        last = now;
        now = SDL_GetPerformanceCounter();
        deltaTime = (float)((now - last) / (float)SDL_GetPerformanceFrequency());

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                running = false;
            }
        }
        auto &player_positions = registry.get_components<Position>();

        const Position &player_position = player_positions[player].value();
        handle_bullet_shooting(registry, player_position);


        control_system(registry);
        position_system(registry, deltaTime);
        bullet_system(registry, deltaTime);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        draw_system(registry, renderer);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

// int main() {
//   try {
//     TcpClient tcp("127.0.0.1", 12345);
//     UdpClient udp("127.0.0.1", 12346);

//     std::string player_name = "Player";
//     auto connect_packet = serialize_connect(player_name);

//     tcp.send_data(connect_packet);

//     while (true) {
//       std::vector<uint8_t> move_packet = {0x04, 0x01, 0x02};
//       udp.send_data(move_packet);

//       std::vector<uint8_t> response;
//       tcp.receive_data(response);

//       // Process server response (not implemented)
//     }

//   } catch (const std::exception &e) {
//     std::cerr << "Error: " << e.what() << std::endl;
//     return 1;
//   }

//   return 0;
// }
