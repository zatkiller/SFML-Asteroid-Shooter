#include <unordered_map>

namespace game {
template <typename T = int>
class ActionMap {
 public:
  ActionMap() = default;

  void map(const T& key, const Action& action) { _map.emplace(key, action); }
  const Action& get(const T& key) const { return _map.at(key); }

 private:
  std::unordered_map<T, Action> map_;
};

}  // namespace game