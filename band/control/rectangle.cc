#include "band/control/rectangle.h"

namespace band {
namespace control {

void Rectangle::SetArea(const ::band::Area& area) {
  area_ = area;
}

::band::Color Rectangle::Color() const {
  return color_;
}

void Rectangle::SetColor(const ::band::Color& color) {
  color_ = color;
}

::band::Area Rectangle::Area(const Interface&) const {
  return area_;
}

void Rectangle::Update(const Point&, const Interface&) { }

void Rectangle::Display(const Point& position, Interface& interface) {
  ::band::Area area = this->Area(interface);

  Point bottom_left = position;
  Point top_right{
    .x = AddDimensions(
        bottom_left.x, area.width,
        interface.WindowArea().width),
    .y = AddDimensions(
        bottom_left.y, area.height,
        interface.WindowArea().height),
  };
  ::band::Rectangle rectangle{
    .bottom_left = bottom_left,
    .top_right = top_right
  };

  interface.DrawRectangle(rectangle, this->Color());
}

}  // namespace control
}  // namespace band
