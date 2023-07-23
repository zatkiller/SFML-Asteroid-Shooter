#pragma once

#include <SFML/Graphics.hpp>

#include "entity.h"
#include "events/action_target.h"
#include "world.h"
namespace game {

class Player : public Entity, public ActionTarget<int> {
 public:
  Player(World& world);
  ~Player() = default;
  Player(const Player&) = delete;
  Player& operator=(const Player&) = delete;
  Player(Player&&) = delete;
  Player& operator=(Player&&) = delete;

  virtual bool hasCollided(const Entity& other) const override;
  virtual void update(sf::Time deltaTime) override;
  virtual void onDestroy() override;

  void processEvents();
  void shoot();
  void goToHyperspace();

 private:
  bool isMoving_;
  int rotation_;
  sf::Time timeSinceLastShoot_;
};

}  // namespace game