#ifndef __SCORE_H__
#define __SCORE_H__

#include "base/components/node.h"

class Texture;
class Sprite;

class Score : public Node {
 public:
  Score();
  virtual ~Score() = default;
  virtual void Update() override;
  void Add(long num);
  void MoveY(int y);

 public:
  long score;

 private:
  int y;
  long current_score;
  RandomGenerator rand;
  std::vector<std::shared_ptr<Texture>> textures;
  std::vector<std::shared_ptr<Sprite>> sprites;
};

#endif  // __SCORE_H__