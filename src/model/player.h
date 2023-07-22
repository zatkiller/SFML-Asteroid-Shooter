#pragma once

#include <SFML/Graphics.hpp>

#include "events/action_target.h"
#include "player.h"

namespace game {

class Player : public sf::Drawable, public ActionTarget {
 public:
  Player();
  ~Player() = default;
  Player(const Player&) = delete;
  Player& operator=(const Player&) = delete;
  Player(Player&&) = delete;
  Player& operator=(Player&&) = delete;

  template <typename... Args>
  void setPosition(Args&&... args) {
    // setPosition for sf::Transformable takes either 2 float numbers or
    // sf::Vector2f as the parameters
    shape_.setPosition(std::forward<Args>(args)...);
  }

  void update(sf::Time deltaTime);
  void processEvents();

 private:
  virtual void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const override;

  bool isMoving_;
  int rotation_;

  sf::RectangleShape shape_;
  sf::Vector2f velocity_;
};

}  // namespace game