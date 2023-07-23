#include "collision.h"

#include <cmath>

namespace game {

float getRadius(const sf::Sprite& s) {
  sf::Vector2f rect(s.getTextureRect().width, s.getTextureRect().height);
  rect.x *= s.getScale().x;
  rect.y *= s.getScale().y;
  return (rect.x + rect.y) / 4;
}

bool collisionTest(const sf::Sprite& first, const sf::Sprite& second) {
  float radius1 = getRadius(first), radius2 = getRadius(second);

  float xd = first.getPosition().x - second.getPosition().x;
  float yd = first.getPosition().y - second.getPosition().y;

  // Pythagoras
  return std::sqrt(xd * xd + yd * yd) <= radius1 + radius2;
}

}  // namespace game
