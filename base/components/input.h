#ifndef __INPUT_H__
#define __INPUT_H__

#include "base/base.h"

class InputAdapter;

enum class KeyState {
  KeyDown,
  KeyPress,
  KeyUp,
};

class Input {
 private:
  Input() = default;

 public:
  static auto& GetInstance() {
    static Input input;
    return input;
  }

  void Update(const SDL_Event& event);
  void AddAdapter(InputAdapter* adapter);
  void RemoveAdapter(InputAdapter* adapter);
  KeyState GetKeyState(const SDL_Keycode& keycode);

 private:
  void OnKeyDown(const SDL_Keycode& keycode);
  void OnKeyDownCore(const SDL_Keycode& keycode);
  void OnKeyPress(const SDL_Keycode& keycode);
  void OnKeyUp(const SDL_Keycode& keycode);

 private:
  std::unordered_map<SDL_Keycode, KeyState> tracking_keys;
  std::vector<InputAdapter*> adapters;
};

#endif  // __INPUT_H__
