#include "band/control.h"

namespace band {

Color BaseControl::BackgroundColor() const {
  return Color{};
}

void BaseControl::SetBackgroundColor(const Color&) { }

Color BaseControl::ForegroundColor() const {
  return Color{};
}

void BaseControl::SetForegroundColor(const Color&) { }

Color BaseControl::BorderColor() const {
  return Color{};
}

void BaseControl::SetBorderColor(const Color&) { }

Dimension BaseControl::HorizontalBorderThickness() const {
  return Dimension{};
}

void BaseControl::SetHorizontalBorderThickness(const Dimension&) { }

Dimension BaseControl::VerticalBorderThickness() const {
  return Dimension{};
}

void BaseControl::SetVerticalBorderThickness(const Dimension&) { }

Dimension BaseControl::HorizontalPadding() const {
  return Dimension{};
}

void BaseControl::SetHorizontalPadding(const Dimension&) { }

Dimension BaseControl::VerticalPadding() const {
  return Dimension{};
}

void BaseControl::SetVerticalPadding(const Dimension&) { }

::band::Area BaseControl::Area() const {
  return ::band::Area{};
}

void BaseControl::SetArea(const ::band::Area&) { }

::band::FontId BaseControl::FontId() const {
  return ::band::FontId{};
}

void BaseControl::SetFontId(::band::FontId) { }

Dimension BaseControl::FontSize() const {
  return Dimension{};
}

void BaseControl::SetFontSize(const Dimension&) { }

void BaseControl::Disable() { }

void BaseControl::Enable() { }

bool BaseControl::IsEnabled() const {
  return true;
}

bool BaseControl::HasFocus() const {
  return false;
}

bool BaseControl::HasPress() const {
  return false;
}

void BaseControl::Display(const Point&, Interface&) { }

void BaseControl::CleanUp(Interface&) { }

void DrawControls(
    const std::initializer_list<std::pair<Control&, Point>>& pairs,
    Interface& interface) {
  interface.StartDrawing();
  interface.Clear(Color{ .r = 0xff, .g = 0xff, .b = 0xff, .a = 0xff });

  for (const std::pair<Control&, Point> pair : pairs) {
    pair.first.Display(pair.second, interface);
  }

  interface.StopDrawing();
}

}  // namespace band
