#ifndef __TIMER_H__
#define __TIMER_H__

class Timer {
 public:
  Timer();
  ~Timer();

  template <typename func>
  void SetInterval(func function, int interval);
  void Stop() { running = false; }
 private:
  bool running;
};

#endif  // __TIMER_H__