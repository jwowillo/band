#include "band/scope.h"

namespace band {

Scope::Scope(const std::function<void()>& f) : f_{f} { }

Scope::~Scope() { f_(); }

}  // namespace band
