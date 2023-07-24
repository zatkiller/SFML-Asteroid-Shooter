#include "world.h"

namespace game {

World::World(float x, float y) : x_(x), y_(y) {}

World::World(World&& other)
    : x_(other.x_),
      y_(other.y_),
      entities_(std::move(other.entities_)),
      entitiesTmp_(std::move(other.entitiesTmp_)),
      sounds_(std::move(other.sounds_)) {}

World& World::operator=(World&& other) {
  if (this == &other) {
    return *this;
  }

  x_ = other.x_;
  y_ = other.y_;
  entities_ = std::move(other.entities_);
  entitiesTmp_ = std::move(other.entitiesTmp_);
  sounds_ = std::move(other.sounds_);

  return *this;
}

void World::add(std::shared_ptr<Entity> entity) {
  entitiesTmp_.push_back(std::move(entity));
}

void World::add(Configs::Sounds id) {
  auto sound =
      std::make_unique<sf::Sound>(Configs::sounds.get(static_cast<int>(id)));

  sound->setAttenuation(0);
  sound->play();
  sounds_.emplace_back(std::move(sound));
}

bool World::hasCollided(const Entity& other) {
  for (auto& entity : entities_)
    if (other.hasCollided(*entity.get())) return true;

  return false;
}

int World::size() { return entities_.size() + entitiesTmp_.size(); }
int World::getX() const { return x_; }
int World::getY() const { return y_; }

const std::list<std::shared_ptr<Entity>>& World::getEntities() const {
  return entities_;
}

void World::update(sf::Time deltaTime) {
  if (entitiesTmp_.size() > 0) entities_.merge(entitiesTmp_);

  for (auto& entity : entities_) {
    entity->update(deltaTime);
    sf::Vector2f pos = entity->getPosition();
    if (pos.x < 0) {
      pos.x = x_;
      pos.y = y_ - pos.y;
    } else if (pos.x > x_) {
      pos.x = 0;
      pos.y = y_ - pos.y;
    }
    if (pos.y < 0)
      pos.y = y_;
    else if (pos.y > y_)
      pos.y = 0;

    entity->setPosition(pos);
  }

  const auto end = entities_.end();

  for (auto it_i = entities_.begin(); it_i != end; ++it_i) {
    auto& entity_i = *it_i;
    auto& it_j = it_i;
    it_j++;

    for (; it_j != end; ++it_j) {
      auto& entity_j = *it_j;
      if (entity_i->isAlive() and entity_i->hasCollided(*entity_j.get()))
        entity_i->onDestroy();
      if (entity_j->isAlive() and entity_j->hasCollided(*entity_i.get()))
        entity_j->onDestroy();
    }

    for (auto it = entities_.begin(); it != entities_.end();) {
      if (!(*it)->isAlive()) {
        it = entities_.erase(it);
      } else {
        ++it;
      }
    }

    sounds_.remove_if([](const std::unique_ptr<sf::Sound>& sound) -> bool {
      return sound->getStatus() != sf::SoundSource::Status::Playing;
    });
  }
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  for (auto& entity : entities_) {
    target.draw(*entity.get(), states);
  }
}

}  // namespace game