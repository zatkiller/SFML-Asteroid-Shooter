#include "configs.h"

#include "events/action.h"

namespace game {

ActionMap<int> Configs::playerInputs;
ResourceManager<sf::Texture, int> Configs::textures;
ResourceManager<sf::SoundBuffer, int> Configs::sounds;

int Configs::lives;

void Configs::initialize() {
  initPlayerInputs();
  initTextures();
  initSounds();
}

void Configs::initPlayerInputs() {
  playerInputs.map(static_cast<int>(PlayerInputs::Up),
                   Action(sf::Keyboard::Up));
  playerInputs.map(static_cast<int>(PlayerInputs::Right),
                   Action(sf::Keyboard::Right));
  playerInputs.map(static_cast<int>(PlayerInputs::Left),
                   Action(sf::Keyboard::Left));
  playerInputs.map(
      static_cast<int>(PlayerInputs::Hyperspace),
      Action(sf::Keyboard::Down, static_cast<int>(Action::Type::Released)));
  playerInputs.map(static_cast<int>(PlayerInputs::Shoot),
                   Action(sf::Keyboard::Space));
}

void Configs::initTextures() {
  textures.load(static_cast<int>(Textures::Player), "media/Player/Ship.png");
}

void Configs::initSounds() {
  sounds.load(static_cast<int>(Sounds::LaserPlayer), "media/sounds/laser1.ogg");
  sounds.load(static_cast<int>(Sounds::Boom), "media/sounds/boom.flac");
  sounds.load(static_cast<int>(Sounds::Jump), "media/sounds/hyperspace.flac");
}

}  // namespace game