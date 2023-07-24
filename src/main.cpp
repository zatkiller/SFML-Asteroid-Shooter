#include "configs/configs.h"
#include "model/game.h"

int main(int argc, char* argv[]) {
  game::Configs::initialize();
  game::Game game;

  game.run();

  return 0;
}