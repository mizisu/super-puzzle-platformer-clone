#include "block.h"
#include "base/sprite.h"
#include "base/texture_manager.h"

const int BlockLife = 2;

RandomGenerator Block::rand;

Block::Block() : life(BlockLife) {
  type = (BlockType)rand.Get(0, 2);
  std::string block_type = "";

  if (type == BlockType::Red) {
    block_type = "r";
  } else if (type == BlockType::Green) {
    block_type = "g";
  } else if (type == BlockType::Blue) {
    block_type = "b";
  }

  std::string image_file = "./res/play/block/" + block_type;

  block_images.push_back(
      TextureManager::GetInstance().GetTexture(image_file + "3.png"));
  block_images.push_back(
      TextureManager::GetInstance().GetTexture(image_file + "2.png"));
  block_images.push_back(
      TextureManager::GetInstance().GetTexture(image_file + "1.png"));

  
  this->SetTexture(block_images[life]);
}

Block::~Block() {}

void Block::Hit() {
  this->life -= 1;
  if (life < 0) {
    life = 0;
    return;
  }
  this->SetTexture(block_images[life]);
}
