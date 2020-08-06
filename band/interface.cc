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

std::unique_ptr<Interface> DefaultInterface() {
  std::unique_ptr<interface::RaylibInterface> interface =
    std::make_unique<interface::RaylibInterface>();

  interface->Open();

  return std::move(interface);
}

}  // namespace band
