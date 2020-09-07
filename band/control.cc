#include "band/control.h"

#include "band/scope.h"

namespace band {

::band::Area BaseControl::Area(const Interface&) const {
  return ::band::Area{};
}

void BaseControl::CleanUp(Interface&) { }
void BaseControl::Update(const Point&, Interface&) { }
void BaseControl::Draw(const Point&, Interface&) { }

void CleanUp(Interface& interface, Control& control) {
  control.CleanUp(interface);
}

void Run(
    const Color& clear_color,
    const std::function<void()>& callback,
    Interface& interface, Control& control) {
  Scope scope{[&interface, &control]() { control.CleanUp(interface); }};

  while (!interface.HasAction(Interface::Action::kClose)) {
    Update(Point{}, interface, control);
    callback();
    DrawFrame(clear_color, Point{}, interface, control);
  }
}

void Update(
    const Point& position,
    Interface& interface, Control& control) {
  control.Update(position, interface);
}

void DrawFrame(
    const Color& clear_color, const Point& position,
    Interface& interface, Control& control) {
  interface.StartDrawing();
  interface.Clear(clear_color);

  control.Draw(position, interface);

  interface.StopDrawing();
}

}  // namespace band
