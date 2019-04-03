#include "timer.h"
#include "thread"

Timer::Timer() : running(false) {}
Timer::~Timer() { Stop(); }

template <typename func>
void Timer::SetInterval(func function, int interval) {
  this->running = true;
  std::thread t([=]() {
    while (true) {
      if (!this->running) return;
      std::this_thread::sleep_for(std::chrono::milliseconds(interval));
      if (!this->running) return;
      function();
    }
  });
  t.detach();
}