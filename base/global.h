#ifndef __GLOBAL_H__
#define __GLOBAL_H__

namespace Global {

const int ScreenWidth = 480;
const int ScreenHeight = 680;

extern SDL_Window* Window;
extern SDL_Surface* ScreenSurface;
extern SDL_Renderer* Renderer;

extern double DeltaTime;

void Log(const std::string_view& str);

template <typename T>
void SafeDelete(T* obj) {
  if (obj) {
    delete obj;
    obj = nullptr;
  }
}

};  // namespace Global

#endif  // __GLOBAL_H__