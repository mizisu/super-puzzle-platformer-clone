#ifndef __NODE_H__
#define __NODE_H__

#include "base.h"

class Node {
 public:
  virtual void Update();
  virtual void Render();

  void UpdateChildren();
  void RenderChildren();

 private:
 std::vector<std::shared_ptr<Node>> children;
};

#endif  // __NODE_H__