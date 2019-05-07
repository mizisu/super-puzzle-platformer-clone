#ifndef __TIMER_H__
#define __TIMER_H__

#include <chrono>
#include <thread>

class Timer {
 public:
  Timer() : running(false) {}
  ~Timer() { Stop(); }

  template <typename func>
  void SetTimeout(func function, int interval) {
    this->running = true;
    std::thread t([=]() {
      if (!this->running) return;
      std::this_thread::sleep_for(std::chrono::milliseconds(interval));
      if (!this->running) return;
      function();
    });
    t.detach();
  }

  template <typename func>
  void SetInterval(func function, int interval) {
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

  void Stop() { running = false; }

 private:
  bool running;
};

#endif  // __TIMER_H__