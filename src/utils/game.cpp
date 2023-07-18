#include "game.h"

namespace game {
Game::Game()
    : _window(sf::VideoMode({800, 600}), "Game_Architecture"), _player(150) {
  _player.setFillColor(sf::Color::Blue);
  _player.setPosition({10, 20});
}

void Game::run() {
  while (_window.isOpen()) {
    processEvents();
    update();
    render();
  }
}

void Game::processEvents() {
  sf::Event event;
  while (_window.pollEvent(event)) {
    if ((event.type == sf::Event::Closed) or
        ((event.type == sf::Event::KeyPressed) and
         (event.key.code == sf::Keyboard::Escape))) {
      _window.close();
    }
  }
}

void Game::update() {}

void Game::render() {
  _window.clear();
  _window.draw(_player);
  _window.display();
}

}  // namespace game