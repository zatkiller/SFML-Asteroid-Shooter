#include "configs/configs.h"
#include "model/game.h"

int main(int argc, char* argv[]) {
  game::Configs::initialize();
  game::Game game(1400, 900);

  game.run();

  return 0;
}