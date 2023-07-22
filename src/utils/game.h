#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "player.h"

namespace game {

class Game {
 public:
  Game();
  ~Game() = default;
  Game(const Game&) = delete;
  Game& operator=(const Game&) = delete;
  Game(Game&&) = delete;
  Game& operator=(Game&&) = delete;

  void run(int minFramePerSeconds = 30);

 private:
  void processEvents();
  void update(sf::Time timePerFrame);
  void render();

  sf::RenderWindow window_;
  Player player_;
};

}  // namespace game