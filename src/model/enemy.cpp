#include "enemy.h"

#include "utils/random.h"

namespace game {

Enemy::Enemy(Configs::Textures id, World& world) : Entity(id, world) {
  float angle = random(0.f, 2.f * M_PI);
  impulse_ = sf::Vector2f(std::cos(angle), std::sin(angle));
}

void Enemy::onDestroy() {
  Entity::onDestroy();
  Configs::addScore(getPoints());
}

}  // namespace game