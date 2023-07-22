#include "player.h"

#include <cmath>

#include "configs/configs.h"

namespace game {

Player::Player()
    : ActionTarget(Configs::playerInputs),
      shape_(sf::Vector2f(32, 32)),
      isMoving_(false),
      rotation_(0) {
  shape_.setFillColor(sf::Color::Blue);
  shape_.setOrigin(16, 16);

  bind(Configs::PlayerInputs::Up,
       [this](const sf::Event&) { isMoving_ = true; });
  bind(Configs::PlayerInputs::Left,
       [this](const sf::Event&) { rotation_ -= 1; });
  bind(Configs::PlayerInputs::Right,
       [this](const sf::Event&) { rotation_ += 1; });
}

void Player::update(sf::Time deltaTime) {
  float seconds = deltaTime.asSeconds();

  if (rotation_ != 0) {
    float angle = (rotation_ > 0 ? 1 : -1) * 180 * seconds;
    shape_.rotate(angle);
  }

  if (isMoving_) {
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
  isMoving_ = false;
  rotation_ = 0;
  ActionTarget::processEvents();
}

}  // namespace game