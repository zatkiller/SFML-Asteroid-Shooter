#include "configs.h"

#include "events/action.h"

namespace game {

ActionMap<int> Configs::playerInputs;

void Configs::initialize() { initPlayerInputs(); }

void Configs::initPlayerInputs() {
  playerInputs.map(PlayerInputs::Up, Action(sf::Keyboard::Up));
  playerInputs.map(PlayerInputs::Right, Action(sf::Keyboard::Right));
  playerInputs.map(PlayerInputs::Left, Action(sf::Keyboard::Left));
}

}  // namespace game