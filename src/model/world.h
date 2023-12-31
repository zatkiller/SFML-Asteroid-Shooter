#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <list>
#include <memory>

#include "entity.h"

namespace game {

class World : public sf::Drawable {
  bool isAlive() { return true; }

  sf::Vector2f getPosition() { return {10, 10}; }

 public:
  World(float x, float y);
  ~World() = default;
  World(const World&) = delete;
  World& operator=(const World&) = delete;
  World(World&&);
  World& operator=(World&&);

  void add(std::shared_ptr<Entity> entity);
  void clear();
  bool hasCollided(const Entity& other);
  int size();
  void add(Configs::Sounds id);
  const std::list<std::shared_ptr<Entity>>& getEntities() const;
  int getX() const;
  int getY() const;
  void update(sf::Time deltaTime);

 private:
  int x_, y_;

  std::list<std::shared_ptr<Entity>> entities_;
  std::list<std::shared_ptr<Entity>> entitiesTmp_;
  std::list<std::unique_ptr<sf::Sound>> sounds_;

  virtual void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const override;
};

}  // namespace game