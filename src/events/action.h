#pragma once

#include <SFML/Window.hpp>

namespace game {
class Action {
 public:
  enum Type {
    RealTime = 1,
    Pressed = 1 << 1,
    Released = 1 << 2,
  };

  Action(const sf::Keyboard::Key& key,
         int type = Type::RealTime | Type::Pressed);
  Action(const sf::Mouse::Button& button,
         int type = Type::RealTime | Type::Pressed);

  bool test() const;
  bool operator==(const sf::Event& event) const;
  bool operator==(const Action& other) const;

 private:
  template <typename T>
  friend class ActionTarget;
  sf::Event event_;
  int type_;
};

}  // namespace game