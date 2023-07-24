#pragma once

#include <SFML/Graphics.hpp>

#include "configs/configs.h"

namespace game {

class World;
class Entity : public sf::Drawable {
 public:
  Entity(Configs::Textures id, World& world);
  virtual ~Entity() = default;
  Entity(const Entity&) = delete;
  Entity& operator=(const Entity&) = delete;
  Entity(Entity&&) = delete;
  Entity& operator=(Entity&&) = delete;

  virtual bool isAlive() const;
  const sf::Vector2f& getPosition() const;

  template <typename... Args>
  void setPosition(Args&&... args) {
    sprite_.setPosition(std::forward<Args>(args)...);
  }

  virtual bool hasCollided(const Entity& other) const = 0;
  virtual void update(sf::Time deltaTime) = 0;
  virtual void onDestroy();

 protected:
  friend class Player;
  friend class Saucer;
  friend class ShootPlayer;
  friend class ShootSaucer;

  sf::Sprite sprite_;
  sf::Vector2f impulse_;
  World& world_;
  bool alive_;

 private:
  virtual void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const override;
};

}  // namespace game