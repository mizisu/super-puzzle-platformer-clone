#include "base/input_adapter.h"

InputAdapter::InputAdapter()
    : keydown(nullptr), keypress(nullptr), keyup(nullptr) {
  Input::GetInstance().AddAdapter(this);
}

InputAdapter::~InputAdapter() { Input::GetInstance().RemoveAdapter(this); }