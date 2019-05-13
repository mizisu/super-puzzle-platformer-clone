
#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "base/base.h"

class Application {
 public:
  Application();
  ~Application();
  bool Initialize();
  void Run();

 private:
  void Close();
  void UpdateDeltaTime();
};

#endif  // __APPLICATION_H__