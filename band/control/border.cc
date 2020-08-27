#include "band/control/border.h"

#include <cmath>

#include "band/control/rectangle.h"

namespace band {
namespace control {

void Border::SetArea(const ::band::Area& area) {
  area_ = area;
}

Dimension Border::Thickness() const {
  return thickness_;
}

void Border::SetThickness(const Dimension& thickness) {
  thickness_ = thickness;
}

::band::Color Border::Color() const {
  return color_;
}

void Border::SetColor(const ::band::Color& color) {
  color_ = color;
}

Real Border::RealBorderThickness(const Interface& interface) const {
  return thickness_.unit == Unit::kPixel ?
    thickness_.scalar :
    thickness_.scalar * std::min(
        interface.WindowArea().width,
        interface.WindowArea().height);
}

::band::Area Border::Area(const Interface&) const {
  return area_;
}

void Border::Update(const Point&, const Interface&) { }

void Border::Display(const Point& position, Interface& interface) {
  Dimension thickness{};
  thickness.scalar = RealBorderThickness(interface);
  thickness.unit = Unit::kPixel;

  ::band::Area area = this->Area(interface);

  ::band::Area horizontal_area{ .width = area.width, .height = thickness };
  ::band::Area vertical_area{ .width = thickness, .height = area.height };

  ::band::control::Rectangle vertical;
  vertical.SetColor(this->Color());
  vertical.SetArea(vertical_area);

  ::band::control::Rectangle horizontal;
  horizontal.SetColor(this->Color());
  horizontal.SetArea(horizontal_area);

  Point top_left = position;
  Point top_right{
    .x = SubtractDimensions(
        AddDimensions(top_left.x, area.width, interface.WindowArea().width),
        thickness, interface.WindowArea().width),
    .y = top_left.y
  };
  Point bottom_left{
    .x = top_left.x,
    .y = SubtractDimensions(
        AddDimensions(top_left.y, area.height, interface.WindowArea().height),
        thickness, interface.WindowArea().height)
  };

  vertical.Display(top_left, interface);
  horizontal.Display(top_left, interface);
  vertical.Display(top_right, interface);
  horizontal.Display(bottom_left, interface);
}

}  // namespace control
}  // namespace band
