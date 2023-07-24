#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "events/action_map.h"
#include "resource_manager.h"

namespace game {

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
  };

  enum class Sounds : int {
    Boom,
    Jump,
    LaserPlayer,
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

  static void addScore(int score);

 private:
  static int score_;
  static sf::Text score_txt_;

  static void initPlayerInputs();
  static void initTextures();
  static void initSounds();
};

}  // namespace game