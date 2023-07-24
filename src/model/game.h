#pragma once

#include <SFML/Window.hpp>
#include <memory>

#include "player.h"
#include "world.h"

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

  bool start = true;
  int x_, y_;
  sf::RenderWindow window_;
  std::shared_ptr<Player> player_;
  World world_;
};

}  // namespace game