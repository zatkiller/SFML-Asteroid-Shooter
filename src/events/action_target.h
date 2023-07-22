#include <functional>
#include <list>

#include "action.h"

namespace game {

class ActionTarget {
 public:
  using FuncType = std::function<void(const sf::Event&)>;

  ActionTarget() = default;

  bool processEvent(const sf::Event& event) const;
  void processEvents() const;
  void bind(const Action& action, const FuncType& callback);
  void unbind(const Action& action);

 private:
  std::list<std::pair<Action, FuncType>> realTimeEvents_;
  std::list<std::pair<Action, FuncType>> eventsPoll_;
};

}  // namespace game