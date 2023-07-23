#include "shoot.h"

#include "utils/collision.h"
#include "utils/random.h"

namespace game {
Shoot::Shoot(Configs::Textures textures, World& world)
    : Entity(textures, world) {
  float angle = random(0.f, 2.f * M_PI);
  impulse_ = sf::Vector2f(std::cos(angle), std::sin(angle));
}

void Shoot::update(sf::Time deltaTime) {
  float seconds = deltaTime.asSeconds();
  sprite_.move(seconds * impulse_);
  duration_ -= deltaTime;
  if (duration_ < sf::Time::Zero) alive_ = false;
}

bool Shoot::hasCollided(const Entity& other) const { return false; }

ShootPlayer::ShootPlayer(Player& from)
    : Shoot(Configs::Textures::ShootPlayer, from.world_) {
  duration_ = sf::seconds(5);

  float angle = from.sprite_.getRotation() / 180 * M_PI - M_PI / 2;
  impulse_ = sf::Vector2f(std::cos(angle), std::sin(angle)) * 500.f;

  setPosition(from.getPosition());
  sprite_.setRotation(from.sprite_.getRotation());
  world_.add(Configs::Sounds::LaserPlayer);
}

bool ShootPlayer::hasCollided(const Entity& other) const {
  if (dynamic_cast<const ShootPlayer::Enemy*>(&other) != nullptr) {
    return collisionTest(sprite_, other.sprite_);
  }
  return false;
}

}  // namespace game