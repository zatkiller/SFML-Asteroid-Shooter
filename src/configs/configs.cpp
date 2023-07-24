#include "configs.h"

#include "events/action.h"

namespace game {

ActionMap<int> Configs::playerInputs;
ResourceManager<sf::Texture, int> Configs::textures;
ResourceManager<sf::SoundBuffer, int> Configs::sounds;

sf::Text Configs::score_txt_;
std::shared_ptr<Player> Configs::player = nullptr;

int Configs::lives = 0;
int Configs::level = 0;
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

  textures.load(static_cast<int>(Textures::BigMeteor1),
                "media/Meteor/Big1.png");
  textures.load(static_cast<int>(Textures::BigMeteor2),
                "media/Meteor/Big2.png");
  textures.load(static_cast<int>(Textures::BigMeteor3),
                "media/Meteor/Big3.png");
  textures.load(static_cast<int>(Textures::BigMeteor4),
                "media/Meteor/Big4.png");

  textures.load(static_cast<int>(Textures::MediumMeteor1),
                "media/Meteor/Medium1.png");
  textures.load(static_cast<int>(Textures::MediumMeteor2),
                "media/Meteor/Medium2.png");

  textures.load(static_cast<int>(Textures::SmallMeteor1),
                "media/Meteor/Small1.png");
  textures.load(static_cast<int>(Textures::SmallMeteor2),
                "media/Meteor/Small2.png");
  textures.load(static_cast<int>(Textures::SmallMeteor3),
                "media/Meteor/Small3.png");
  textures.load(static_cast<int>(Textures::SmallMeteor4),
                "media/Meteor/Small4.png");
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

  sounds.load(static_cast<int>(Sounds::Explosion1),
              "media/sounds/explosion1.flac");
  sounds.load(static_cast<int>(Sounds::Explosion2),
              "media/sounds/explosion2.flac");
  sounds.load(static_cast<int>(Sounds::Explosion3),
              "media/sounds/explosion3.flac");
}

void Configs::addScore(int score) {
  int old = score_;
  score_ += score * level;
  lives += score_ / 10000 - old / 10000;
  score_txt_.setString(std::to_string(score_));
}

int Configs::getScore() { return score_; }

}  // namespace game