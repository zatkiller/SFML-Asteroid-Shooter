#include "configs.h"

#include "events/action.h"

namespace game {

ActionMap<int> Configs::playerInputs;
ResourceManager<sf::Texture, int> Configs::textures;
ResourceManager<sf::SoundBuffer, int> Configs::sounds;

sf::Text Configs::score_txt_;
std::shared_ptr<Player> Configs::player = nullptr;

int Configs::lives = 0;
int Configs::level = 10;
int Configs::score_ = 0;

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
  textures.load(static_cast<int>(Textures::ShootPlayer),
                "media/Shoot/Player.png");
  textures.load(static_cast<int>(Textures::ShootSaucer),
                "media/Shoot/Saucer.png");

  textures.load(static_cast<int>(Textures::BigSaucer), "media/Saucer/Big.png");
  textures.load(static_cast<int>(Textures::SmallSaucer),
                "media/Saucer/Small.png");
}

void Configs::initSounds() {
  sounds.load(static_cast<int>(Sounds::LaserPlayer), "media/sounds/laser1.ogg");
  sounds.load(static_cast<int>(Sounds::LaserEnemy), "media/sounds/laser2.ogg");
  sounds.load(static_cast<int>(Sounds::Boom1), "media/sounds/boom.flac");
  sounds.load(static_cast<int>(Sounds::Boom2), "media/sounds/boom2.flac");
  sounds.load(static_cast<int>(Sounds::Jump), "media/sounds/hyperspace.flac");

  sounds.load(static_cast<int>(Sounds::SaucerSpawn1),
              "media/sounds/spawn1.flac");
  sounds.load(static_cast<int>(Sounds::SaucerSpawn2),
              "media/sounds/spawn2.flac");
}

void Configs::addScore(int score) {
  int old = score_;
  score_ += score * level;
  lives += score_ / 10000 - old / 10000;
  score_txt_.setString(std::to_string(score_));
}

int Configs::getScore() { return score_; }

}  // namespace game