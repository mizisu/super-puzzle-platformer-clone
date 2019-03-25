#ifndef __GLOBAL_H__
#define __GLOBAL_H__

namespace Global {

const int ScreenWidth = 480;
const int ScreenHeight = 600;

extern SDL_Window* Window;
extern SDL_Surface* ScreenSurface;
extern SDL_Renderer* Renderer;

void Log(const std::string_view& str);

}  // namespace Global

#endif // __GLOBAL_H__