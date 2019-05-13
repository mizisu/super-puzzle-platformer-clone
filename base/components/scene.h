#ifndef __SCENE_H__
#define __SCENE_H__

#include "base/components/node.h"

class SceneManager;

class Scene : public Node {
 public:
  Scene();
  ~Scene();
};

#endif  // __SCENE_H__
