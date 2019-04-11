#include "base/application.h"
#include "base/base.h"
#include "base/components/scene_manager.h"
#include "game/game_scene.h"

Application::Application() {}

Application::~Application() { Close(); }

bool Application::Initialize() {
  try {
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
      throw std::string("SDL Init Error : ") + SDL_GetError();

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    auto window = SDL_CreateWindow("super-puzzle-platformer-clone",
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED, Global::ScreenWidth,
                                   Global::ScreenHeight, SDL_WINDOW_SHOWN);

    if (window == NULL)
      throw std::string("SDL_CreateWindow Error :") + SDL_GetError();

    auto renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);

    SDL_RenderSetScale(renderer, 0.5f, 0.5f);

    int imgFlags = IMG_INIT_PNG;
    IMG_Init(imgFlags);

    Global::Window = window;
    Global::Renderer = renderer;
    Global::ScreenSurface = SDL_GetWindowSurface(window);

    scene_manager = std::make_unique<SceneManager>();
    scene_manager->Push(new GameScene());

    return true;

  } catch (const std::string& error) {
    Global::Log(error);
    return false;
  }
}

void Application::Run() {
  auto running = true;
  SDL_Event event;
  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
      } else if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
          case SDLK_ESCAPE:
            running = false;
            break;
        }
      }
    }

    SDL_RenderClear(Global::Renderer);
    UpdateDeltaTime();
    scene_manager->Play();
    SDL_RenderPresent(Global::Renderer);
    SDL_Delay(16);
  }
}

void Application::Close() {
  SDL_DestroyRenderer(Global::Renderer);
  SDL_DestroyWindow(Global::Window);
  Global::Renderer = NULL;
  Global::Window = NULL;
  IMG_Quit();
  SDL_Quit();
}

void Application::UpdateDeltaTime() {
  static Uint64 NOW = SDL_GetPerformanceCounter();
  static Uint64 LAST = 0;

  LAST = NOW;
  NOW = SDL_GetPerformanceCounter();

  auto deltaTime =
      ((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());
  Global::DeltaTime = deltaTime / 100;
}