#include "saucer.h"

#include "enemy.h"
#include "entity.h"
#include "shoot.h"
#include "utils/collision.h"
#include "utils/random.h"
#include "world.h"

namespace game {

bool Saucer::hasCollided(const Entity& other) const {
  if (dynamic_cast<const ShootSaucer*>(&other) == nullptr) {
    return collisionTest(sprite_, other.sprite_);
  }
  return false;
}

void Saucer::update(sf::Time deltaTime) {
  float seconds = deltaTime.asSeconds();
  std::shared_ptr<Entity> near = nullptr;
  float near_distance = 300;
  for (auto& entity : world_.getEntities()) {
    if (entity.get() != this and
        (dynamic_cast<const Shoot::Meteor*>(entity.get()) or
         dynamic_cast<const ShootPlayer*>(entity.get()))) {
      float x = getPosition().x - entity->getPosition().x;
      float y = getPosition().y - entity->getPosition().y;
      float dist = std::sqrt(x * x + y * y);
      if (dist < near_distance) {
        near_distance = dist;
        near = entity;
      }
    }
  }
  if (near != nullptr) {
    sf::Vector2f pos = near->getPosition() - getPosition();
    float angle_rad = std::atan2(pos.y, pos.x);
    impulse_ -= sf::Vector2f(std::cos(angle_rad), std::sin(angle_rad)) * 300.f *
                seconds;
  } else {
    sf::Vector2f pos = Configs::player->getPosition() - getPosition();
    float angle_rad = std::atan2(pos.y, pos.x);
    impulse_ += sf::Vector2f(std::cos(angle_rad), std::sin(angle_rad)) * 100.f *
                seconds;
  }
  sprite_.move(seconds * impulse_);
}

void Saucer::onDestroy() {
  Enemy::onDestroy();
  world_.add(Configs::Sounds::Boom2);
}

void Saucer::newSaucer(World& world) {
  std::shared_ptr<Saucer> res = nullptr;
  if (random(0.f, 1.f) > Configs::getScore() / 40000.f)
    res = std::make_shared<BigSaucer>(world);
  else
    res = std::make_shared<SmallSaucer>(world);
  res->setPosition(random(0, 1) * world.getX(),
                   random(0.f, (float)world.getY()));
  world.add(res);
}

BigSaucer::BigSaucer(World& world)
    : Saucer(Configs::Textures::BigSaucer, world) {
  world_.add(Configs::Sounds::SaucerSpawn1);
  impulse_ *= 300.f;
}

int BigSaucer::getPoints() const { return 50; }

SmallSaucer::SmallSaucer(World& world)
    : Saucer(Configs::Textures::SmallSaucer, world) {
  timeSinceLastShoot_ = sf::Time::Zero;
  world_.add(Configs::Sounds::SaucerSpawn2);
  impulse_ *= 400.f;
}

int SmallSaucer::getPoints() const { return 200; }

void SmallSaucer::update(sf::Time deltaTime) {
  Saucer::update(deltaTime);
  // shoot on the Configs::player
  timeSinceLastShoot_ += deltaTime;
  if (timeSinceLastShoot_ > sf::seconds(1.5)) {
    if (Configs::player != nullptr)
      world_.add(std::make_shared<ShootSaucer>(*this));
    timeSinceLastShoot_ = sf::Time::Zero;
  }
}

}  // namespace game