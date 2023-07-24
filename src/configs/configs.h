#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "events/action_map.h"
#include "resource_manager.h"

namespace game {

class Player;
class Configs {
 public:
  enum class PlayerInputs : int {
    Up,
    Left,
    Right,
    Shoot,
    Hyperspace,
  };

  enum class Textures : int {
    Player,
    ShootPlayer,
    ShootSaucer,
    SmallSaucer,
    BigSaucer,
    BigMeteor1,
    BigMeteor2,
    BigMeteor3,
    BigMeteor4,
    MediumMeteor1,
    MediumMeteor2,
    SmallMeteor1,
    SmallMeteor2,
    SmallMeteor3,
    SmallMeteor4,
    PlayerLife,
  };

  enum class Sounds : int {
    Boom1,
    Boom2,
    Jump,
    LaserPlayer,
    LaserEnemy,
    SaucerSpawn1,
    SaucerSpawn2,
    Explosion1,
    Explosion2,
    Explosion3,
  };

  enum class Music : int {
    Theme,
  };

  enum class Fonts : int {
    Gui,
  };

  static ActionMap<int> playerInputs;
  static ResourceManager<sf::Texture, int> textures;
  static ResourceManager<sf::SoundBuffer, int> sounds;
  static ResourceManager<sf::Font, int> fonts;
  static ResourceManager<sf::Music, int> musics;

  static int lives;
  static int level;

  Configs() = delete;
  ~Configs() = default;
  Configs(const Configs&) = delete;
  Configs& operator=(const Configs&) = delete;
  Configs(Configs&&) = default;
  Configs& operator=(Configs&&) = default;

  static void initialize();
  static void reset();

  static int getScore();
  static void addScore(int score);

  static bool isGameOver();

  static std::shared_ptr<Player> player;

  static void draw(sf::RenderTarget& target);

 private:
  static int score_;
  static sf::Text scoreTxt_;
  static sf::Sprite sprLife_;

  static void initPlayerInputs();
  static void initTextures();
  static void initSounds();
  static void initFonts();
  static void initMusic();
};

}  // namespace game