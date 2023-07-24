#include "game.h"

#include "meteor.h"
#include "saucer.h"
#include "utils/random.h"

namespace game {
Game::Game(int x, int y)
    : window_(sf::VideoMode(x, y), "Asteroid_Shooter_SFML"), world_(x, y) {}

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
  world_.update(deltaTime);

  if (!Configs::player) {
    Configs::player = std::make_shared<Player>(world_);
    Configs::player->setPosition(world_.getX() / 2, world_.getY() / 2);
    world_.add(Configs::player);
  }

  nextSaucer_ -= deltaTime;

  if (nextSaucer_ < sf::Time::Zero) {
    Saucer::newSaucer(world_);
    nextSaucer_ = sf::seconds(random(10.f, 60.f - Configs::level * 2));
  }

  if (world_.size() < 1) {
    ++Configs::level;
    initLevel();
  }
}

void Game::render() {
  window_.clear();
  window_.draw(world_);
  window_.display();
}

void Game::reset() {
  nextSaucer_ = sf::seconds(random(5.f, 6.f - Configs::level * 2));
  world_.clear();
  Configs::player = nullptr;
}

void Game::initLevel() {
  int meteors;
  switch (Configs::level) {
    case 1:
      meteors = 4;
      break;
    case 2:
      meteors = 5;
      break;
    case 3:
      meteors = 7;
      break;
    case 4:
      meteors = 9;
      break;
    default:
      meteors = 11;
      break;
  }

  for (int i = 0; i < meteors; ++i) {
    auto meteor = std::make_shared<BigMeteor>(world_);
    do {
      meteor->setPosition(random(0.f, (float)world_.getX()),
                          random(0.f, (float)world_.getY()));
    } while (world_.hasCollided(*meteor.get()));
    world_.add(meteor);
  }
}

}  // namespace game