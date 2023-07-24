#include "meteor.h"

#include "utils/collision.h"
#include "utils/random.h"
#include "world.h"

namespace game {
bool Meteor::hasCollided(const Entity& other) const {
  if (dynamic_cast<const Meteor*>(&other) == nullptr) {
    return collisionTest(sprite_, other.sprite_);
  }
  return false;
}

void Meteor::update(sf::Time deltaTime) {
  float seconds = deltaTime.asSeconds();
  sprite_.move(seconds * impulse_);
}
SmallMeteor::SmallMeteor(World& world)
    : Meteor((Configs::Textures)random(
                 static_cast<int>(Configs::Textures::SmallMeteor1),
                 static_cast<int>(Configs::Textures::SmallMeteor4)),
             world) {
  impulse_ *= 300.f;
}

int SmallMeteor::getPoints() const { return 100; }

void SmallMeteor::onDestroy() {
  Meteor::onDestroy();
  world_.add(Configs::Sounds::Explosion3);
}

MediumMeteor::MediumMeteor(World& world)
    : Meteor((Configs::Textures)random(
                 static_cast<int>(Configs::Textures::MediumMeteor1),
                 static_cast<int>(Configs::Textures::MediumMeteor2)),
             world) {
  impulse_ *= 200.f;
}

int MediumMeteor::getPoints() const { return 60; }

void MediumMeteor::onDestroy() {
  Meteor::onDestroy();

  int nb = random(2, 3);
  for (int i = 0; i < nb; ++i) {
    auto meteor = std::make_shared<SmallMeteor>(world_);
    meteor->setPosition(getPosition());
    world_.add(meteor);
  }
  world_.add(Configs::Sounds::Explosion2);
}

BigMeteor::BigMeteor(World& world)
    : Meteor((Configs::Textures)random(
                 static_cast<int>(Configs::Textures::BigMeteor1),
                 static_cast<int>(Configs::Textures::BigMeteor4)),
             world) {
  impulse_ *= 100.f;
}

int BigMeteor::getPoints() const { return 20; }

void BigMeteor::onDestroy() {
  Meteor::onDestroy();
  int nb = random(2, 3);
  for (int i = 0; i < nb; ++i) {
    auto meteor = std::make_shared<MediumMeteor>(world_);
    meteor->setPosition(getPosition());
    world_.add(meteor);
  }
  world_.add(Configs::Sounds::Explosion1);
}

}  // namespace game