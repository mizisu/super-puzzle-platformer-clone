#ifndef __NODE_H__
#define __NODE_H__

#include "base.h"

class Node {
 public:
  Node();
  virtual ~Node();
  
  virtual void Update();
  virtual void Render();

  void UpdateChildren();
  void RenderChildren();
  void AddChild(std::shared_ptr<Node> child);
  void Clear();
  
 private:
  std::vector<std::shared_ptr<Node>> children;
};

#endif  // __NODE_H__