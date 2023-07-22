#include "configs.h"

#include "events/action.h"

namespace game {

ActionMap<int> Configs::playerInputs;
ResourceManager<sf::Texture, int> Configs::textures;

void Configs::initialize() {
  initPlayerInputs();
  initTextures();
}

void Configs::initPlayerInputs() {
  playerInputs.map(static_cast<int>(PlayerInputs::Up),
                   Action(sf::Keyboard::Up));
  playerInputs.map(static_cast<int>(PlayerInputs::Right),
                   Action(sf::Keyboard::Right));
  playerInputs.map(static_cast<int>(PlayerInputs::Left),
                   Action(sf::Keyboard::Left));
}

void Configs::initTextures() {
  textures.load(static_cast<int>(Textures::Player), "media/Player/Ship.png");
}

}  // namespace game