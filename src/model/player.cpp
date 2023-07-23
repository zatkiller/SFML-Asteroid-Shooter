

#include "player.h"

#include <cmath>

#include "configs/configs.h"
#include "shoot.h"
#include "utils/collision.h"
#include "utils/random.h"

namespace game {

Player::Player(World& world)
    : Entity(Configs::Textures::Player, world),
      ActionTarget(Configs::playerInputs),
      isMoving_(false),
      rotation_(0) {
  bind(static_cast<int>(Configs::PlayerInputs::Shoot),
       [this](const sf::Event&) { shoot(); });
  bind(static_cast<int>(Configs::PlayerInputs::Hyperspace),
       [this](const sf::Event&) { goToHyperspace(); });
}

void Player::update(sf::Time deltaTime) {
  float seconds = deltaTime.asSeconds();
  timeSinceLastShoot_ += deltaTime;
  if (rotation_ != 0) {
    float angle = rotation_ * 250 * seconds;
    sprite_.rotate(angle);
  }
  if (isMoving_) {
    float angle = sprite_.getRotation() / 180 * M_PI - M_PI / 2;
    impulse_ +=
        sf::Vector2f(std::cos(angle), std::sin(angle)) * 300.f * seconds;
  }
  sprite_.move(seconds * impulse_);
}

bool Player::hasCollided(const Entity& other) const {
  if (dynamic_cast<const ShootPlayer*>(&other) == nullptr) {
    return collisionTest(sprite_, other.sprite_);
  }
  return false;
}

void Player::shoot() {
  if (timeSinceLastShoot_ > sf::seconds(0.3)) {
    auto shootPlayer = std::make_unique<ShootPlayer>(*this);
    world_.add(std::move(shootPlayer));
    timeSinceLastShoot_ = sf::Time::Zero;
  }
}

void Player::onDestroy() {
  Entity::onDestroy();
  Configs::lives--;
  world_.add(Configs::Sounds::Boom);
}

void Player::goToHyperspace() {
  impulse_ = sf::Vector2f(0, 0);
  setPosition(random(0, world_.getX()), random(0, world_.getY()));
  world_.add(Configs::Sounds::Jump);
}

void Player::processEvents() {
  isMoving_ = false;
  rotation_ = 0;
  ActionTarget::processEvents();
}

}  // namespace game