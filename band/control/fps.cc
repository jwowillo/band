#include "band/control/fps.h"

namespace band {
namespace control {

::band::Area Fps::Area(const Interface&) const {
  return ::band::Area{};
}

void Fps::Update(const Point&, const Interface&) { }

void Fps::Display(const Point& position, Interface& interface) {
  interface.DrawFps(position);
}

}  // namespace control
}  // namespace band
