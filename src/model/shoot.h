#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "player.h"
#include "saucer.h"

namespace game {

class Shoot : public Entity {
 public:
  class Meteor {};

  Shoot(Configs::Textures textures, World& world);
  ~Shoot() = default;
  Shoot(const Shoot&) = delete;
  Shoot& operator=(const Shoot&) = delete;
  Shoot(Shoot&&) = delete;
  Shoot& operator=(Shoot&&) = delete;

  virtual void update(sf::Time deltaTime) override;
  virtual bool hasCollided(const Entity& other) const override;

 protected:
  sf::Time duration_;
};

class ShootPlayer : public Shoot {
 public:
  ~ShootPlayer() = default;
  ShootPlayer(const ShootPlayer&) = delete;
  ShootPlayer& operator=(const ShootPlayer&) = delete;
  ShootPlayer(ShootPlayer&&) = delete;
  ShootPlayer& operator=(ShootPlayer&&) = delete;

  ShootPlayer(Player& from);
  virtual bool hasCollided(const Entity& other) const override;
};

class SmallSaucer;
class ShootSaucer : public Shoot {
 public:
  ShootSaucer(SmallSaucer& from);
  ~ShootSaucer() = default;
  ShootSaucer(const ShootSaucer&) = delete;
  ShootSaucer& operator=(const ShootSaucer&) = delete;
  ShootSaucer(ShootSaucer&&) = delete;
  ShootSaucer& operator=(ShootSaucer&&) = delete;

  virtual bool hasCollided(const Entity& other) const;
};

}  // namespace game