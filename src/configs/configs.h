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
  };

  enum class Textures : int {
    Player,
  };

  enum class Sounds : int {
    PLACEHOLDER,
  };

  static ActionMap<int> playerInputs;
  static ResourceManager<sf::Texture, int> textures;
  static ResourceManager<sf::SoundBuffer, int> sounds;

  Configs() = delete;
  ~Configs() = default;
  Configs(const Configs&) = delete;
  Configs& operator=(const Configs&) = delete;
  Configs(Configs&&) = default;
  Configs& operator=(Configs&&) = default;

  static void initialize();

 private:
  static void initPlayerInputs();
  static void initTextures();
  static void initSounds();
};

}  // namespace game