#pragma once

#include "events/action_map.h"

namespace game {

class Configs {
 public:
  static ActionMap<int> playerInputs;

  Configs() = delete;
  ~Configs() = default;
  Configs(const Configs&) = delete;
  Configs& operator=(const Configs&) = delete;
  Configs(Configs&&) = delete;
  Configs& operator=(Configs&&) = delete;

  static void initialize();

  enum PlayerInputs : int {
    Up,
    Left,
    Right,
  };

 private:
  static void initPlayerInputs();
};

}  // namespace game