#pragma once

#include <SFML/Window.hpp>

#include "player.h"

namespace game {

class Game {
 public:
  Game(int x = 800, int y = 600);
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

  const int x_, y_;
  sf::RenderWindow window_;
  Player player_;
};

}  // namespace game