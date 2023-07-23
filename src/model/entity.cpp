#include "entity.h"

namespace game {
Entity::Entity(Configs::Textures id, World& world)
    : world_(world), alive_(true) {
  sf::Texture& texture = Configs::textures.get(static_cast<int>(id));
  sprite_.setTexture(texture);
  sprite_.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
}

bool Entity::isAlive() const { return alive_; }

void Entity::onDestroy() { alive_ = false; }

const sf::Vector2f& Entity::getPosition() const {
  return sprite_.getPosition();
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(sprite_, states);
}

}  // namespace game