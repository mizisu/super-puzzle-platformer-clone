#ifndef __SCORE_SCENE_H__
#define __SCORE_SCENE_H__

#include "base/components/scene.h"
#include "game/score.h"

class ScoreScene : public Scene {
 public:
  ScoreScene(int score) {
    auto score_view = std::make_shared<Score>();
    score_view->Add(score);
    score_view->MoveY(500);
    this->AddChild(score_view);
  }
};

#endif  // __SCORE_SCENE_H__