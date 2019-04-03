#ifndef __BACKGROUND_LAYER_H__
#define __BACKGROUND_LAYER_H__

#include "base/node.h"

class BackgroundLayer : public Node {
 public:
  BackgroundLayer();
  virtual ~BackgroundLayer();

 private:
  void CreateBottomLine();
  void CreatePill();
  void CreateEdge();

 private:
  int background_width;
  int background_height;
};

#endif  // __BACKGROUND_LAYER_H__