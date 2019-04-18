#include "base/components/input.h"
#include "base/components/input_adapter.h"

void Input::Initialize() {
}

void Input::Update(const SDL_Event& event) {
  if (event.type == SDL_KEYDOWN) OnKeyDown(event.key.keysym.scancode);
  if (event.type == SDL_KEYUP) OnKeyUp(event.key.keysym.scancode);
}

void Input::AddAdapter(InputAdapter* adapter) { adapters.push_back(adapter); }

void Input::RemoveAdapter(InputAdapter* adapter) {
  std::remove(adapters.begin(), adapters.end(), adapter);
}

KeyState Input::GetKeyState(const SDL_Scancode& scancode) {
  return SDL_GetKeyboardState(NULL)[scancode] ? KeyState::KeyDown : KeyState::KeyUp;
}

bool Input::IsKeyDown(const SDL_Scancode& scancode) {
  return this->GetKeyState(scancode) == KeyState::KeyDown;
}

bool Input::IsKeyUp(const SDL_Scancode& scancode) {
  return this->GetKeyState(scancode) == KeyState::KeyUp;
}

void Input::OnKeyDown(const SDL_Scancode& scancode) {
  if (auto it = tracking_keys.find(scancode); it == tracking_keys.end())
    OnKeyDownCore(scancode);
  else {
    if (it->second == KeyState::KeyPress || it->second == KeyState::KeyDown)
      OnKeyPress(scancode);
    else
      OnKeyDownCore(scancode);
  }
}

void Input::OnKeyDownCore(const SDL_Scancode& keycode) {
  tracking_keys[keycode] = KeyState::KeyDown;
  for (auto& adapter : adapters) adapter->OnKeyDown(keycode);
}

void Input::OnKeyPress(const SDL_Scancode& keycode) {
  tracking_keys[keycode] = KeyState::KeyPress;
  for (auto& adapter : adapters) adapter->OnKeyPress(keycode);
}

void Input::OnKeyUp(const SDL_Scancode& keycode) {
  tracking_keys[keycode] = KeyState::KeyUp;
  for (auto& adapter : adapters) adapter->OnKeyUp(keycode);
}