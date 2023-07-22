#pragma once

#include <functional>
#include <list>

#include "action_map.h"

namespace game {

template <typename T = int>
class ActionTarget {
 public:
  using FuncType = std::function<void(const sf::Event&)>;

  ActionTarget(const ActionMap<T>& map) : actionMap_(map) {}

  bool processEvent(const sf::Event& event) const {
    bool res = false;

    for (auto& pair : eventsPoll_) {
      if (pair.first == event) {
        pair.second(event);
        res = true;
        break;
      }
    }

    return res;
  }

  void processEvents() const {
    for (auto& pair : realTimeEvents_) {
      const Action& action = actionMap_.get(pair.first);

      if (action.test()) {
        pair.second(action.event_);
      }
    }
  }

  void bind(const T& key, const FuncType& callback) {
    const Action& action = actionMap_.get(key);
    if (action.type_ & Action::Type::RealTime)
      realTimeEvents_.emplace_back(key, callback);
    else
      eventsPoll_.emplace_back(key, callback);
  }

  void unbind(const T& key) {
    auto remove_func = [&key](const std::pair<T, FuncType>& pair) {
      return pair.first == key;
    };

    const Action& action = actionMap_.get(key);
    if (action.type_ & Action::Type::RealTime)
      realTimeEvents_.remove_if(remove_func);
    else
      eventsPoll_.remove_if(remove_func);
  }

 private:
  std::list<std::pair<T, FuncType>> realTimeEvents_;
  std::list<std::pair<T, FuncType>> eventsPoll_;

  const ActionMap<T>& actionMap_;
};

}  // namespace game