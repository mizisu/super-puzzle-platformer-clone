#ifndef __UI_LAYER_H__
#define __UI_LAYER_H__

#include "base/components/node.h"

class Sprite;
class BarSprite;
class Score;

class UiLayer : public Node {
 public:
  UiLayer();
  virtual ~UiLayer() = default;
  virtual void Update() override;
  void AddScore(long num);
  void SetEnerge(int value);

 private:
  std::shared_ptr<Score> score;
  std::shared_ptr<BarSprite> lvbar;
  std::vector<std::shared_ptr<Sprite>> lv_mark;
};

#endif  // __UI_LAYER_H__