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
    BigSaucer
  };

  enum class Sounds : int {
    Boom1,
    Boom2,
    Jump,
    LaserPlayer,
    LaserEnemy,
    SaucerSpawn1,
    SaucerSpawn2,
  };

  static ActionMap<int> playerInputs;
  static ResourceManager<sf::Texture, int> textures;
  static ResourceManager<sf::SoundBuffer, int> sounds;

  static int lives;
  static int level;

  Configs() = delete;
  ~Configs() = default;
  Configs(const Configs&) = delete;
  Configs& operator=(const Configs&) = delete;
  Configs(Configs&&) = default;
  Configs& operator=(Configs&&) = default;

  static void initialize();

  static int getScore();
  static void addScore(int score);

  static std::shared_ptr<Player> player;

 private:
  static int score_;
  static sf::Text score_txt_;

  static void initPlayerInputs();
  static void initTextures();
  static void initSounds();
};

}  // namespace game