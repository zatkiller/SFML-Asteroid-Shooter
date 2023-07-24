#pragma once

#include <SFML/Graphics.hpp>

#include "configs/configs.h"
#include "entity.h"

namespace game {

class Enemy : public Entity {
 public:
  Enemy(Configs::Textures id, World& world);
  ~Enemy() = default;
  Enemy(const Enemy&) = delete;
  Enemy& operator=(const Enemy&) = delete;
  Enemy(Enemy&&) = delete;
  Enemy& operator=(Enemy&&) = delete;

  virtual int getPoints() const = 0;
  virtual void onDestroy();
};

}  // namespace game