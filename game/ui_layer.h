#ifndef __UI_LAYER_H__
#define __UI_LAYER_H__

#include "base/components/node.h"

class UiLayer : public Node {
 public:
  UiLayer();
  virtual ~UiLayer() = default;
};

#endif  // __UI_LAYER_H__