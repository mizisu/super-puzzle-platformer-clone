#include "game/normal_block.h"
#include "base/components/texture_manager.h"

const int BlockLife = 2;

RandomGenerator NormalBlock::rand;

NormalBlock::NormalBlock() : life(BlockLife) {
  type = (BlockType)rand.Get(0, 3);
  LoadImages();
  this->SetTexture(block_images[life]);
}

NormalBlock::~NormalBlock() {}

void NormalBlock::Hit() {
  timer.SetInterval(
      [&]() {
        this->SetTexture(this->block_images[life]);
        timer.Stop();
      },
      100);
  HitInternal();
}

void NormalBlock::Update() { base::Update(); }

void NormalBlock::HitInternal() {
  this->life -= 1;
  if (life <= 0) life = 0;
  this->SetTexture(block_damaged_images[life]);
}

void NormalBlock::LoadImages() {
  std::string block_type = "";

  if (type == BlockType::Red)
    block_type = "r";
  else if (type == BlockType::Green)
    block_type = "g";
  else if (type == BlockType::Blue)
    block_type = "b";

  std::string image_file = "play/block/" + block_type;

  std::string image_files[] = {
      image_file + "3.png",
      image_file + "2.png",
      image_file + "1.png",
  };

  for (auto& file : image_files) {
    block_images.push_back(TextureManager::GetInstance().GetTexture(file));
  }

  block_damaged_images.push_back(TextureManager::GetInstance().GetTexture(
      "play/block/block_damaged2.png"));
  block_damaged_images.push_back(TextureManager::GetInstance().GetTexture(
      "play/block/block_damaged3.png"));
}