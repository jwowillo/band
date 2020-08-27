#include "band/control/texture.h"

#include <iostream>

namespace band {
namespace control {

void Texture::CaptureControl(Interface& interface, Control& control) {
  if (texture_id_.has_value()) {
    CleanUp(interface);
  }

  area_ = control.Area(interface);

  texture_id_ = interface.CreateBlankTexture(area_);
  interface.SelectTexture(texture_id_.value());

  control.Display(band::Point{}, interface);

  interface.UnselectTexture();
}

void Texture::CleanUp(Interface& interface) {
  if (!texture_id_.has_value()) {
    return;
  }

  interface.DeleteTexture(texture_id_.value());
  texture_id_ = std::nullopt;
}

::band::Area Texture::Area(const Interface&) const {
  if (!texture_id_.has_value()) {
    return ::band::Area{};
  }

  return area_;
}

void Texture::Update(const Point&, const Interface&) {
  return;
}

void Texture::Display(const Point& position, Interface& interface) {
  if (!texture_id_.has_value()) {
    return;
  }

  interface.DrawTexture(texture_id_.value(), position);
}

}  // namespace control
}  // namespace band
