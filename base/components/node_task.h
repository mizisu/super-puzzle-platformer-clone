#ifndef __NODE_TASK_H__
#define __NODE_TASK_H__

#include "base/components/node.h"

class NodeTask : public Node {
 public:
  static auto After(std::function<void()> function, double interval) {
    auto task = std::make_shared<NodeTask>();
    task->function = function;
    task->interval = interval;
    return task;
  }

 public:
  NodeTask() : function(nullptr), interval(0) {}
  virtual ~NodeTask() { this->function = nullptr; }
  virtual void Update() override {
    this->interval -= Global::DeltaTime;
    if (this->interval < 0 && this->function != nullptr) {
      this->function();
      this->Erase();
    }
  }

 private:
  std::function<void()> function;
  double interval;
};

#endif  // __NODE_TASK_H__