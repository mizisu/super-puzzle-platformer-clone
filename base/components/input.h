#ifndef __INPUT_H__
#define __INPUT_H__

#include "base/base.h"

class InputAdapter;

enum class KeyState {
  None,
  KeyDown,
  KeyPress,
  KeyUp,
};

class Input {
 private:
  Input() : prev_keystate(nullptr), current_keystate(nullptr){};

 public:
  static auto& GetInstance() {
    static Input input;
    return input;
  }

  void Initialize();
  void Update(const SDL_Event& event);
  void UpdateKeyState();
  void AddAdapter(InputAdapter* adapter);
  void RemoveAdapter(InputAdapter* adapter);
  KeyState GetKeyState(const SDL_Scancode& scancode);
  bool IsKeyDown(const SDL_Scancode& scancode);
  bool IsKeyPress(const SDL_Scancode& scancode);
  bool IsKeyUp(const SDL_Scancode& scancode);

 private:
  void OnKeyDown(const SDL_Scancode& scancode);
  void OnKeyDownCore(const SDL_Scancode& scancode);
  void OnKeyPress(const SDL_Scancode& scancode);
  void OnKeyUp(const SDL_Scancode& scancode);

 private:
  const Uint8* prev_keystate;
  const Uint8* current_keystate;
  // bool keystate[SDL_NUM_SCANCODES];
  std::unordered_map<SDL_Scancode, KeyState> tracking_keys;
  std::vector<InputAdapter*> adapters;
};

#endif  // __INPUT_H__
