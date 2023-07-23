#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "player.h"

namespace game {

class Shoot : public Entity {
 public:
  class Enemy {};
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

}  // namespace game