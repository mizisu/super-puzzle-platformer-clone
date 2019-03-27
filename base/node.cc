#include "node.h"

Node::Node() {}
Node::~Node() {}

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

void Node::AddChild(std::shared_ptr<Node> child) { children.push_back(child); }