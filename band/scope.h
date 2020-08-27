#pragma once

#include <functional>

namespace band {

// Scope calls a function when the scope is finished.
class Scope {
  public:
    explicit Scope(const std::function<void()>& f);

    ~Scope();

    Scope(const Scope&) = delete;
    Scope& operator=(const Scope&) = delete;
    Scope(const Scope&&) = delete;
    Scope& operator=(const Scope&&) = delete;

  private:
    std::function<void()> f_;
};

}  // namespace band
