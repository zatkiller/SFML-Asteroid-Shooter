#pragma once

#include <unordered_map>

#include "action.h"

namespace game {
template <typename T = int>
class ActionMap {
 public:
  ActionMap() = default;

  void map(const T& key, const Action& action) { map_.emplace(key, action); }
  const Action& get(const T& key) const { return map_.at(key); }

 private:
  std::unordered_map<T, Action> map_;
};

}  // namespace game