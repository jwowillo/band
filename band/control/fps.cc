#include "band/control/fps.h"

namespace band {
namespace control {

void Fps::Draw(const Point& position, Interface& interface) {
  interface.DrawFps(position);
}

}  // namespace control
}  // namespace band
