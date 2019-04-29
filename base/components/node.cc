#include "base/components/node.h"

Node::Node() : erase_mark(false) {}
Node::~Node() { Clear(); }

void Node::Update() {}
void Node::Render() {}

void Node::UpdateChildren() {
  Update();
  for (auto node : children) {
    node->UpdateChildren();
  }
}

void Node::RenderChildren() {
  Render();
  for (auto node : children) {
    node->RenderChildren();
  }
}

void Node::RemoveMarkedChild() {
  for (auto it = children.begin(); it != children.end();) {
    if ((*it)->IsErase()) {
      it = children.erase(it);
    } else {
      it++;
    }
  }

  for (auto node : children) {
    node->RemoveMarkedChild();
  }
}

void Node::AddChild(std::shared_ptr<Node> child) {
  child->parent = this;
  children.push_back(child);
}

void Node::Clear() { children.clear(); }
