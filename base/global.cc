#include "base/base.h"

namespace Global {

void Log(const std::string_view& str) { std::cout << str << std::endl; }

int EnergyToLevel(int energy) {
  if (energy < 40) {
    return 1;
  } else if (energy < 80) {
    return 2;
  } else if (energy < 120) {
    return 3;
  } else if (energy <= PlayerMaxEnergy) {
    return 4;
  } else {
    return 1;
  }
}

}  // namespace Global

SDL_Window* Global::Window = NULL;
SDL_Surface* Global::ScreenSurface = NULL;
SDL_Renderer* Global::Renderer = NULL;
double Global::DeltaTime = 0;