#pragma once

#include <functional>
#include <vector>

#include "band/control.h"
#include "band/interface.h"

namespace band {

// Stage is an RAII-structure that cleans up controls it created with the
// interface passed to the constructor.
class Stage {
  public:
    explicit Stage(Interface& interface);

    ~Stage();

    Stage(const Stage&) = delete;
    Stage& operator=(const Stage&) = delete;
    Stage(const Stage&&) = delete;
    Stage& operator=(const Stage&&) = delete;

    template <typename T, typename... Args>
    T& Add(Args&&... args);

  private:
    Interface& interface_;
    std::vector<std::reference_wrapper<Control>> controls_;

};

}  // namespace band

namespace band {

template <typename T, typename... Args>
T& Stage::Add(Args&&... args) {
  T t{std::forward<Args>(args)...};
  controls_.push_back(t);
  return t;
}

}  // namespace band
