#include "player.h"

#include <math.h>

#include <cmath>

namespace game {

Player::Player() : shape_(sf::Vector2f(32, 32)) {
  shape_.setFillColor(sf::Color::Blue);
  shape_.setOrigin(16, 16);
}

void Player::update(sf::Time deltaTime) {
  float seconds = deltaTime.asSeconds();

  if (rotation != 0) {
    float angle = (rotation > 0 ? 1 : -1) * 180 * seconds;
    shape_.rotate(angle);
  }

  if (isMoving) {
    float angle = shape_.getRotation() / 180 * M_PI - M_PI / 2;
    velocity_ +=
        sf::Vector2f(std::cos(angle), std::sin(angle)) * 60.f * seconds;
  }

  shape_.move(seconds * velocity_);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(shape_, states);
}

void Player::processEvents() {
  isMoving = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
  rotation = 0;
  rotation -= sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
  rotation += sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
}

}  // namespace game