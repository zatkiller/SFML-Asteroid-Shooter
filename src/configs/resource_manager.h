#pragma once

#include <SFML/Audio.hpp>
#include <memory>
#include <unordered_map>

namespace game {

template <typename Resource, typename Id = int>
class ResourceManager {
 public:
  ResourceManager() = default;
  ~ResourceManager() = default;
  ResourceManager(const ResourceManager&) = delete;
  ResourceManager& operator=(const ResourceManager&) = delete;
  ResourceManager(ResourceManager&&) = default;
  ResourceManager& operator=(ResourceManager&&) = default;

  template <typename... Args>
  void load(const Id& id, Args&&... args) {
    std::unique_ptr<Resource> ptr = std::make_unique<Resource>();

    if (!ptr->loadFromFile(std::forward<Args>(args)...))
      throw std::runtime_error("Impossible to load file");

    map_.emplace(id, std::move(ptr));
  }

  Resource& get(const Id& id) const { return *map_.at(id); }

 private:
  std::unordered_map<Id, std::unique_ptr<Resource>> map_;
};

template <typename Id>
class ResourceManager<sf::Music, Id> {
 public:
  ResourceManager() = default;
  ~ResourceManager() = default;
  ResourceManager(const ResourceManager&) = delete;
  ResourceManager& operator=(const ResourceManager&) = delete;
  ResourceManager(ResourceManager&&) = default;
  ResourceManager& operator=(ResourceManager&&) = default;

  template <typename... Args>
  void load(const Id& id, Args&&... args) {
    std::unique_ptr<sf::Music> ptr = std::make_unique<sf::Music>();

    if (!ptr->openFromFile(std::forward<Args>(args)...))
      throw std::runtime_error("Impossible to load file");

    map_.emplace(id, std::move(ptr));
  }

  sf::Music& get(const Id& id) const { return *map_.at(id); }

 private:
  std::unordered_map<Id, std::unique_ptr<sf::Music>> map_;
};

}  // namespace game