#pragma once

#include "enemy.h"
#include "entity.h"
#include "world.h"

namespace game {
class Saucer : public Enemy {
 public:
  using Enemy::Enemy;  // make Enemy parent constructor visible to overload
                       // during Saucer constructor call

  Saucer(const Saucer&) = delete;
  Saucer& operator=(const Saucer&) = delete;
  Saucer(Saucer&&) = delete;
  Saucer& operator=(Saucer&&) = delete;

  virtual bool hasCollided(const Entity& other) const override;
  virtual void update(sf::Time deltaTime) override;
  virtual void onDestroy() override;
  static void newSaucer(World& world);
};

class BigSaucer : public Saucer {
 public:
  BigSaucer(World& world);
  virtual int getPoints() const override;
};

class SmallSaucer : public Saucer {
 public:
  SmallSaucer(World& world);
  virtual int getPoints() const override;
  virtual void update(sf::Time deltaTime) override;

 private:
  sf::Time timeSinceLastShoot_;
};

}  // namespace game