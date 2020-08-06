#include "band/interface.h"

#include "band/interface/raylib_interface.h"

#include <iostream>

namespace band {

Dimension AddDimensions(
    const Dimension& a, const Dimension& b, Real pixels) {
  Real av = a.unit == Unit::kPixel ?  a.scalar : a.scalar * pixels;
  Real bv = b.unit == Unit::kPixel ?  b.scalar : b.scalar * pixels;

  return Dimension{ .scalar = av + bv, .unit = Unit::kPixel };
}

Dimension SubtractDimensions(
    const Dimension& a, const Dimension& b, Real pixels) {
  Real av = a.unit == Unit::kPixel ?  a.scalar : a.scalar * pixels;
  Real bv = b.unit == Unit::kPixel ?  b.scalar : b.scalar * pixels;

  return Dimension{ .scalar = av - bv, .unit = Unit::kPixel };
}

Dimension MultiplyDimensions(const Dimension& a, Real scalar) {
  return Dimension{ .scalar = a.scalar * scalar, .unit = a.unit };
}

std::unique_ptr<Interface> DefaultInterface(
    const WindowArea& window_area,
    const Text& window_name,
    const std::optional<File>& file_icon,
    Size target_fps) {
  std::unique_ptr<interface::RaylibInterface> interface =
    std::make_unique<interface::RaylibInterface>();

  ImageId icon = 0u;
  if (file_icon.has_value()) {
    icon = interface->LoadImage(file_icon.value());
  }

  interface::WindowInfo window_info{
    .area = window_area,
    .name = window_name,
    .fps = target_fps,
    .icon = icon
  };

  interface->Open(window_info);

  return std::move(interface);
}

}  // namespace band
