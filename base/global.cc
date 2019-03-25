#include "base.h"
#include "global.h"


namespace Global {

void Log(const std::string_view& str) { std::cout << str << std::endl; }

}  // namespace Global

SDL_Window* Global::Window = NULL;
SDL_Surface* Global::ScreenSurface = NULL;
SDL_Renderer* Global::Renderer = NULL;