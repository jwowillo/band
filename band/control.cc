#include "band/control.h"

namespace band {

void Update(
    const Point& position, const Interface& interface,
    Control& control) {
  control.Update(position, interface);
}

void DrawFrame(
    const Color& clear_color, const Point& position,
    Interface& interface, Control& control) {
  interface.StartDrawing();
  interface.Clear(clear_color);

  control.Display(position, interface);

  interface.StopDrawing();
}

}  // namespace band
