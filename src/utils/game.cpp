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
    if (event.type == sf::Event::Closed)
      window_.close();
    else if (event.type == sf::Event::KeyPressed) {
      if (event.key.code == sf::Keyboard::Escape)
        window_.close();
      else if (event.key.code == sf::Keyboard::Up)
        player_.isMoving = true;
      else if (event.key.code == sf::Keyboard::Left)
        player_.rotation = -1;
      else if (event.key.code == sf::Keyboard::Right)
        player_.rotation = 1;
    } else if (event.type == sf::Event::KeyReleased) {
      if (event.key.code == sf::Keyboard::Up)
        player_.isMoving = false;
      else if (event.key.code == sf::Keyboard::Left)
        player_.rotation = 0;
      else if (event.key.code == sf::Keyboard::Right)
        player_.rotation = 0;
    }
  }
}

void Game::update(sf::Time timePerFrame) {}

void Game::render() {
  window_.clear();
  window_.draw(player_);
  window_.display();
}

}  // namespace game