#include "game.h"

namespace game {
Game::Game(int x, int y)
    : window_(sf::VideoMode(x, y), "Asteroid_Shooter_SFML"),
      x_(x),
      y_(y),
      world_(x, y),
      player_(std::make_shared<Player>(world_)) {}

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
    if (Configs::player) {
      Configs::player->processEvent(event);
    }
  }
  if (Configs::player) {
    Configs::player->processEvents();
  }
}

void Game::update(sf::Time deltaTime) {
  if (!Configs::player) {
    Configs::player = std::make_shared<Player>(world_);
    Configs::player->setPosition(world_.getX() / 2, world_.getY() / 2);
    world_.add(Configs::player);
  }

  world_.update(deltaTime);
}

void Game::render() {
  window_.clear();
  window_.draw(world_);
  window_.display();
}

}  // namespace game