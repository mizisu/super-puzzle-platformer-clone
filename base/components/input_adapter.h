#ifndef __INPUT_ADAPTER_H__
#define __INPUT_ADAPTER_H__

#include "base/base.h"

class InputAdapter {
 public:
  typedef std::function<void(const SDL_Keycode& keycode)> KeyDownFunction;

  InputAdapter();
  virtual ~InputAdapter();
  void KeyDown(KeyDownFunction fn) { keydown = fn; }
  void KeyPress(KeyDownFunction fn) { keypress = fn; }
  void KeyUp(KeyDownFunction fn) { keyup = fn; }

  void OnKeyDown(const SDL_Keycode& keycode) { OnEvent(keydown, keycode); }
  void OnKeyPress(const SDL_Keycode& keycode) { OnEvent(keypress, keycode); }
  void OnKeyUp(const SDL_Keycode& keycode) { OnEvent(keyup, keycode); }

 private:
  void OnEvent(KeyDownFunction fn, const SDL_Keycode& keycode) {
    if (fn != nullptr) fn(keycode);
  }

 private:
  KeyDownFunction keydown;
  KeyDownFunction keypress;
  KeyDownFunction keyup;
};

#endif  // __INPUT_ADAPTER_H__