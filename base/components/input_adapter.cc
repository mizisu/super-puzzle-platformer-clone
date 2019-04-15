#include "base/components/input_adapter.h"
#include "base/components/input.h"

InputAdapter::InputAdapter()
    : keydown(nullptr), keypress(nullptr), keyup(nullptr) {
  Input::GetInstance().AddAdapter(this);
}

InputAdapter::~InputAdapter() { Input::GetInstance().RemoveAdapter(this); }