
#include "enemy.h"

namespace game {
class Meteor : public Enemy {
 public:
  using Enemy::Enemy;

  ~Meteor() = default;
  Meteor(const Meteor&) = delete;
  Meteor& operator=(const Meteor&) = delete;
  Meteor(Meteor&&) = delete;
  Meteor& operator=(Meteor&&) = delete;

  virtual bool hasCollided(const Entity& other) const override;
  virtual void update(sf::Time deltaTime) override;
};

class SmallMeteor : public Meteor {
 public:
  SmallMeteor(World& world);
  virtual int getPoints() const override;
  virtual void onDestroy() override;
};

class MediumMeteor : public Meteor {
 public:
  MediumMeteor(World& worll);
  virtual int getPoints() const override;
  virtual void onDestroy() override;
};

class BigMeteor : public Meteor {
 public:
  BigMeteor(World& world);
  virtual int getPoints() const override;
  virtual void onDestroy() override;
};

}  // namespace game