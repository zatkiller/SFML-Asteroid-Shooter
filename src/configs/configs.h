#pragma once

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

  static ActionMap<int> playerInputs;
  static ResourceManager<sf::Texture, int> textures;

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
};

}  // namespace game