#include "shoot.h"

#include "enemy.h"
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
  if (dynamic_cast<const Enemy*>(&other) != nullptr) {
    return collisionTest(sprite_, other.sprite_);
  }
  return false;
}

// ShootSaucer::ShootSaucer(SmallSaucer& from)
//     : Shoot(Configs::Textures::ShootSaucer, from.world_) {
//   duration_ = sf::seconds(5);

//   sf::Vector2f pos = Configs::player->getPosition() - from.getPosition();

//   float accuracy_lost =
//       book::random(-1.f, 1.f) * M_PI / ((200 + Configs::getScore()) / 100.f);
//   float angle_rad = std::atan2(pos.y, pos.x) + accuracy_lost;
//   float angle_deg = angle_rad * 180 / M_PI;

//   impulse_ = sf::Vector2f(std::cos(angle_rad), std::sin(angle_rad)) * 500.f;

//   setPosition(from.getPosition());
//   sprite_.setRotation(angle_deg + 90);
//   world_.add(Configs::Sounds::LaserEnemy);
// }

// bool ShootSaucer::isCollide(const Entity& other) const {
//   if (dynamic_cast<const Player*>(&other) or
//       dynamic_cast<const Meteor*>(&other)) {
//     return Collision::circleTest(sprite_, other.sprite_);
//   }
//   return false;
// }

// ShootSaucer::ShootSaucer(SmallSaucer& from)
//     : Shoot(Configs::Textures::ShootSaucer, from.world_) {
//   duration_ = sf::seconds(5);

//   sf::Vector2f pos = Configs::player->getPosition() - from.getPosition();

//   float accuracy_lost =
//       book::random(-1.f, 1.f) * M_PI / ((200 + Configs::getScore()) / 100.f);
//   float angle_rad = std::atan2(pos.y, pos.x) + accuracy_lost;
//   float angle_deg = angle_rad * 180 / M_PI;

//   impulse_ = sf::Vector2f(std::cos(angle_rad), std::sin(angle_rad)) * 500.f;

//   setPosition(from.getPosition());
//   sprite_.setRotation(angle_deg + 90);
//   world_.add(Configs::Sounds::LaserEnemy);
// }

// bool ShootSaucer::isCollide(const Entity& other) const {
//   if (dynamic_cast<const Player*>(&other) or
//       dynamic_cast<const Shoot::Meteor*>(&other)) {
//     return Collision::circleTest(sprite_, other.sprite_);
//   }
//   return false;
// }

}  // namespace game