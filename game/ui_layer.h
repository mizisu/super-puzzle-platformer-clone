#ifndef __UI_LAYER_H__
#define __UI_LAYER_H__

#include "base/components/node.h"

class Score;
class BarSprite;

class UiLayer : public Node {
 public:
  UiLayer();
  virtual ~UiLayer() = default;
  void AddScore(long num);
  void SetEnerge(int value);

 private:
  std::shared_ptr<Score> score;
  std::shared_ptr<BarSprite> lvbar;
};

#endif  // __UI_LAYER_H__