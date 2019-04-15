#include "base/components/input.h"
#include "base/components/input_adapter.h"

void Input::Update(const SDL_Event& event) {
  if (event.type == SDL_KEYDOWN) OnKeyDown(event.key.keysym.sym);
  if (event.type == SDL_KEYUP) OnKeyUp(event.key.keysym.sym);
}

void Input::AddAdapter(InputAdapter* adapter) { adapters.push_back(adapter); }

void Input::RemoveAdapter(InputAdapter* adapter) {
  std::remove(adapters.begin(), adapters.end(), adapter);
}

KeyState Input::GetKeyState(const SDL_Keycode& keycode) {
  if (auto it = tracking_keys.find(keycode); it != tracking_keys.end()) {
    return it->second;
  } else {
    return KeyState::KeyUp;
  }
}

void Input::OnKeyDown(const SDL_Keycode& keycode) {
  if (auto it = tracking_keys.find(keycode); it == tracking_keys.end())
    OnKeyDownCore(keycode);
  else {
    if (it->second == KeyState::KeyPress || it->second == KeyState::KeyDown)
      OnKeyPress(keycode);
    else
      OnKeyDownCore(keycode);
  }
}

void Input::OnKeyDownCore(const SDL_Keycode& keycode) {
  tracking_keys[keycode] = KeyState::KeyDown;
  for (auto& adapter : adapters) adapter->OnKeyDown(keycode);
}

void Input::OnKeyPress(const SDL_Keycode& keycode) {
  tracking_keys[keycode] = KeyState::KeyPress;
  for (auto& adapter : adapters) adapter->OnKeyPress(keycode);
}

void Input::OnKeyUp(const SDL_Keycode& keycode) {
  tracking_keys[keycode] = KeyState::KeyUp;
  for (auto& adapter : adapters) adapter->OnKeyUp(keycode);
}