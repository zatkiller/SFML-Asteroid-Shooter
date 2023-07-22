#include "game.h"

namespace game {
Game::Game() : window_(sf::VideoMode(800, 600), "Game_Architecture") {
  player_.setPosition(10, 20);
}

// Minimum time steps
void Game::run(int minFramePerSeconds) {
  sf::Clock clock;
  sf::Time timeSinceLastUpdate;
  sf::Time timePerFrame = sf::seconds(1.f / minFramePerSeconds);
  while (window_.isOpen()) {
    processEvents();
    timeSinceLastUpdate = clock.restart();
    while (timeSinceLastUpdate > timePerFrame) {
      timeSinceLastUpdate -= timePerFrame;
      update(timePerFrame);
    }
    update(timeSinceLastUpdate);
    render();
  }
}

void Game::processEvents() {
  sf::Event event;
  while (window_.pollEvent(event)) {
    if (event.type == sf::Event::Closed)  // Close window
      window_.close();
    else if (event.type == sf::Event::KeyPressed)  // keyboard input
    {
      if (event.key.code == sf::Keyboard::Escape) window_.close();
    }
  }
  player_.processEvents();
}

void Game::update(sf::Time timePerFrame) {}

void Game::render() {
  window_.clear();
  window_.draw(player_);
  window_.display();
}

}  // namespace game