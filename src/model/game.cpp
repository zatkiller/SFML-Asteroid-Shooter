#include "game.h"

namespace game {
Game::Game(int x, int y)
    : window_(sf::VideoMode(x, y), "Asteroid_Shooter_SFML"),
      x_(x),
      y_(y),
      world_(x, y),
      player_(world_) {}

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

void Game::update(sf::Time deltaTime) {
  player_.update(deltaTime);

  sf::Vector2f pos = player_.getPosition();

  if (pos.x < 0) {
    pos.x = x_;
    pos.y = y_ - pos.y;
  } else if (pos.x > x_) {
    pos.x = 0;
    pos.y = y_ - pos.y;
  }

  if (pos.y < 0)
    pos.y = y_;
  else if (pos.y > y_)
    pos.y = 0;

  player_.setPosition(pos);
}

void Game::render() {
  window_.clear();
  window_.draw(player_);
  window_.display();
}

}  // namespace game