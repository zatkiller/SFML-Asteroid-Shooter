#include "action.h"

namespace game {

Action::Action(const sf::Keyboard::Key& key, int type) : type_(type) {
  event_.type = sf::Event::EventType::KeyPressed;
  event_.key.code = key;
}

Action::Action(const sf::Mouse::Button& button, int type) : type_(type) {
  event_.type = sf::Event::EventType::MouseButtonPressed;
  event_.mouseButton.button = button;
}

bool Action::test() const {
  bool res = false;

  if (event_.type == sf::Event::EventType::KeyPressed) {
    if (type_ & Type::Pressed)
      res = sf::Keyboard::isKeyPressed(event_.key.code);
  } else if (event_.type == sf::Event::EventType::MouseButtonPressed) {
    if (type_ & Type::Pressed)
      res = sf::Mouse::isButtonPressed(event_.mouseButton.button);
  }
  return res;
}

bool Action::operator==(const sf::Event& event) const {
  bool res = false;

  switch (event.type) {
    case sf::Event::EventType::KeyPressed:
      if ((type_ & Type::Pressed) &&
          (event_.type == sf::Event::EventType::KeyPressed))
        res = event.key.code == event_.key.code;

      break;

    case sf::Event::EventType::KeyReleased:
      if ((type_ & Type::Released) &&
          (event_.type == sf::Event::EventType::KeyPressed))
        res = event.key.code == event_.key.code;

      break;

    case sf::Event::EventType::MouseButtonPressed:
      if ((type_ & Type::Pressed) &&
          (event_.type == sf::Event::EventType::MouseButtonPressed))
        res = event.mouseButton.button == event_.mouseButton.button;

      break;

    case sf::Event::EventType::MouseButtonReleased:
      if ((type_ & Type::Released) &&
          (event_.type == sf::Event::EventType::MouseButtonPressed))
        res = event.mouseButton.button == event_.mouseButton.button;

      break;

    default:
      break;
  }
  return res;
}

bool Action::operator==(const Action& other) const {
  return type_ == other.type_ and other == event_;
}

}  // namespace game