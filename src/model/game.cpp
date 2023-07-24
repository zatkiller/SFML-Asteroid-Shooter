#include "game.h"

#include "meteor.h"
#include "saucer.h"
#include "utils/random.h"

namespace game {
Game::Game(int x, int y)
    : window_(sf::VideoMode(x, y), "Asteroid_Shooter_SFML"), world_(x, y) {
  txt_.setFont(Configs::fonts.get(static_cast<int>(Configs::Fonts::Gui)));
  txt_.setCharacterSize(70);
  txt_.setString("Press any Key to start");

  sf::FloatRect size = txt_.getGlobalBounds();
  txt_.setOrigin(size.width / 2, size.height / 2);
  txt_.setPosition(x / 2, y / 2);
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

    if (Configs::isGameOver()) {
      if (event.type == sf::Event::KeyPressed)  // keyboard input
        reset();
    } else if (!Configs::isGameOver() && Configs::player) {
      Configs::player->processEvent(event);
    }
  }
  if (!Configs::isGameOver() && Configs::player) {
    Configs::player->processEvents();
  }
}

void Game::update(sf::Time deltaTime) {
  if (!Configs::isGameOver()) {
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

    if (world_.size() <= 1) {
      ++Configs::level;
      initLevel();
    }
  }
}

void Game::render() {
  window_.clear();
  if (Configs::isGameOver()) {
    window_.draw(txt_);
  } else {
    window_.draw(world_);
    Configs::draw(window_);
  }
  window_.display();
}

void Game::reset() {
  nextSaucer_ = sf::seconds(random(5.f, 6.f - Configs::level * 2));
  world_.clear();
  Configs::player = nullptr;
  Configs::reset();
  initLevel();
}

void Game::initLevel() {
  int meteors;
  switch (Configs::level) {
    case 1:
      meteors = 2;
      break;
    case 2:
      meteors = 4;
      break;
    case 3:
      meteors = 6;
      break;
    case 4:
      meteors = 8;
      break;
    default:
      meteors = 10;
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