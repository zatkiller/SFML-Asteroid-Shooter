#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace game {

class Game {
 public:
  Game();
  Game(const Game&) = delete;
  Game& operator=(const Game&) = delete;
  Game(Game&&) = delete;
  Game& operator=(Game&&) = delete;

  void run();

 private:
  void processEvents();
  void update();
  void render();

  sf::RenderWindow _window;
  sf::CircleShape _player;
};

}  // namespace game