#pragma once

#include <SFML/Window.hpp>
#include <memory>

#include "player.h"
#include "world.h"

namespace game {

class Game {
 public:
  Game(int x = 1200, int y = 900);
  ~Game() = default;
  Game(const Game&) = delete;
  Game& operator=(const Game&) = delete;
  Game(Game&&) = delete;
  Game& operator=(Game&&) = delete;

  void run(int minFramePerSeconds = 30);
  void initLevel();

 private:
  void processEvents();
  void update(sf::Time timePerFrame);
  void render();
  void reset();

  bool start = true;
  sf::RenderWindow window_;
  World world_;

  sf::Time nextSaucer_;
  sf::Text txt_;
};

}  // namespace game