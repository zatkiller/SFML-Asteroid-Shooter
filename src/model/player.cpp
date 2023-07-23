#include "player.h"

#include <cmath>

#include "configs/configs.h"

namespace game {

Player::Player()
    : ActionTarget(Configs::playerInputs), isMoving_(false), rotation_(0) {
  ship_.setTexture(
      Configs::textures.get(static_cast<int>(Configs::Textures::Player)));
  ship_.setOrigin(49.5, 37.5);

  bind(static_cast<int>(Configs::PlayerInputs::Up),
       [this](const sf::Event&) { isMoving_ = true; });
  bind(static_cast<int>(Configs::PlayerInputs::Left),
       [this](const sf::Event&) { rotation_ -= 1; });
  bind(static_cast<int>(Configs::PlayerInputs::Right),
       [this](const sf::Event&) { rotation_ += 1; });
}

const sf::Vector2f& Player::getPosition() const { return ship_.getPosition(); }

void Player::update(sf::Time deltaTime) {
  float seconds = deltaTime.asSeconds();

  if (rotation_ != 0) {
    float angle = (rotation_ > 0 ? 1 : -1) * 180 * seconds;
    ship_.rotate(angle);
  }

  if (isMoving_) {
    float angle = ship_.getRotation() / 180 * M_PI - M_PI / 2;
    velocity_ +=
        sf::Vector2f(std::cos(angle), std::sin(angle)) * 60.f * seconds;
  }

  ship_.move(seconds * velocity_);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(ship_, states);
}

void Player::processEvents() {
  isMoving_ = false;
  rotation_ = 0;
  ActionTarget::processEvents();
}

}  // namespace game