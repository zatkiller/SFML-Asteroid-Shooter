#include "action_target.h"

namespace game {

bool ActionTarget::processEvent(const sf::Event& event) const {
  bool res = false;

  for (auto& action : eventsPoll_) {
    if (action.first == event) {
      action.second(event);
      res = true;
      break;
    }
  }

  return res;
}

void ActionTarget::processEvents() const {
  for (auto& action : realTimeEvents_) {
    if (action.first.test()) {
      action.second(action.first.event_);
    }
  }
}

void ActionTarget::bind(const Action& action, const FuncType& callback) {
  if (action.type_ & Action::Type::RealTime)
    realTimeEvents_.emplace_back(action, callback);
  else
    eventsPoll_.emplace_back(action, callback);
}

void ActionTarget::unbind(const Action& action) {
  auto remove_func = [&action](const std::pair<Action, FuncType>& pair) {
    return pair.first == action;
  };

  if (action.type_ & Action::Type::RealTime)
    realTimeEvents_.remove_if(remove_func);
  else
    eventsPoll_.remove_if(remove_func);
}

}  // namespace game