#ifndef __NODE_H__
#define __NODE_H__

#include "base/base.h"

class Node {
 public:
  Node();
  virtual ~Node();

  virtual void Update();
  virtual void Render();

  void UpdateChildren();
  void RenderChildren();
  void RemoveMarkedChild();
  void AddChild(std::shared_ptr<Node> child);
  void Clear();
  virtual void Erase() { erase_mark = true; }
  bool IsErase() { return erase_mark; }
  Node* GetParent() { return parent; }

 private:
  std::list<std::shared_ptr<Node>> children;
  Node* parent;
  bool erase_mark;
};

#endif  // __NODE_H__