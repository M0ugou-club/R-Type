#include "Game.hpp"
#include <vector>

void position_system(Registry &registry, float deltaTime) {
  auto &positions = registry.get_components<Position>();
  auto &velocities = registry.get_components<Velocity>();

  for (std::size_t i = 0; i < positions.size(); ++i) {
    if (positions[i] && velocities[i]) {
      positions[i]->x += velocities[i]->x * deltaTime;
      positions[i]->y += velocities[i]->y * deltaTime;
    }
  }
}

void control_system(Registry &registry) {
  const bool *keyState = SDL_GetKeyboardState(NULL);

  auto &controllables = registry.get_components<Control>();
  auto &velocities = registry.get_components<Velocity>();

  for (std::size_t i = 0; i < controllables.size(); ++i) {
    if (controllables[i] && velocities[i]) {
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

void draw_system(Registry &registry, SDL_Renderer *renderer) {
  auto &positions = registry.get_components<Position>();
  auto &drawables = registry.get_components<Draw>();

  for (std::size_t i = 0; i < positions.size(); ++i) {
    if (positions[i] && drawables[i]) {
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

int main() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL Initialization failed: " << SDL_GetError() << std::endl;
    return 1;
  }

  //if (TTF_Init() < 0) {
    //std::cerr << "TTF Initialization failed: " << SDL_GetError() << std::endl;
    //SDL_Quit();
    //return 1;
  //}

  SDL_Window *window = SDL_CreateWindow("ECS System", 800, 600, 0);
  if (!window) {
    std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, nullptr);
  if (!renderer) {
    std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  //TTF_Font *font = TTF_OpenFont("../src/graphical/font/COMICATE.TTF", 24);
  //if (!font) {
    //std::cerr << "Font loading failed: " << SDL_GetError() << std::endl;
    //SDL_DestroyRenderer(renderer);
    //SDL_DestroyWindow(window);
    //SDL_Quit();
    //return 1;
  //}

  Registry registry;

  registry.register_component<Position>();
  registry.register_component<Velocity>();
  registry.register_component<Draw>();
  registry.register_component<Control>();
  registry.register_component<Health>();

  auto player = create_entity<EntityType::Player>(registry, Position(400, 100), Velocity(), Health(), Draw({0, 255, 0, 255}, {100, 150, 50, 50}));
  auto enemy = registry.spawn_entity();
  registry.add_component<Position>(enemy, Position(700, 200));
  registry.add_component<Velocity>(enemy, Velocity(0, -100));
  registry.add_component<Draw>(enemy, Draw({255, 0, 0, 255}, {100, 150, 50, 50}));
  registry.add_component<Health>(enemy, Health(50));


  bool running = true;
  SDL_Event event;
  Uint64 now = SDL_GetPerformanceCounter();
  Uint64 last = 0;
  float deltaTime = 0;

  while (running) {
    last = now;
    now = SDL_GetPerformanceCounter();
    deltaTime = (float)((now - last) / (float)SDL_GetPerformanceFrequency());

    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        running = false;
      }
    }

    control_system(registry);
    position_system(registry, deltaTime);
    get_space_event(registry, player);
    collision_system(registry, enemy);
    enemy_system(registry, enemy);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    draw_system(registry, renderer);

    SDL_RenderPresent(renderer);
  }

  //TTF_CloseFont(font);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
