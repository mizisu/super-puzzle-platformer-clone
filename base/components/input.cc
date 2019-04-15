#include "base/components/input.h"
#include "base/components/input_adapter.h"

void Input::Initialize() {
  prev_keystate = SDL_GetKeyboardState(NULL);
  current_keystate = SDL_GetKeyboardState(NULL);
}

void Input::Update(const SDL_Event& event) {
  if (event.type == SDL_KEYDOWN) OnKeyDown(event.key.keysym.scancode);
  if (event.type == SDL_KEYUP) OnKeyUp(event.key.keysym.scancode);
}

void Input::UpdateKeyState() {
  prev_keystate = current_keystate;
  current_keystate = SDL_GetKeyboardState(NULL);
}

void Input::AddAdapter(InputAdapter* adapter) { adapters.push_back(adapter); }

void Input::RemoveAdapter(InputAdapter* adapter) {
  std::remove(adapters.begin(), adapters.end(), adapter);
}

KeyState Input::GetKeyState(const SDL_Scancode& scancode) {
  if (!prev_keystate[scancode] && current_keystate[scancode])
    return KeyState::KeyDown;

  if (prev_keystate[scancode] && current_keystate[scancode])
    return KeyState::KeyPress;

  if (prev_keystate[scancode] && !current_keystate[scancode])
    return KeyState::KeyUp;

  return KeyState::None;
}

bool Input::IsKeyDown(const SDL_Scancode& scancode) {
  return this->GetKeyState(scancode) == KeyState::KeyDown;
}
bool Input::IsKeyPress(const SDL_Scancode& scancode) {
  return this->GetKeyState(scancode) == KeyState::KeyPress;
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