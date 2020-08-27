#include "band/interface.h"

#include <cmath>

#include "band/interface/raylib_interface.h"

namespace band {

bool operator==(const Dimension& a, const Dimension& b) {
  return a.scalar == b.scalar && a.unit == b.unit;
}
bool operator!=(const Dimension& a, const Dimension& b) {
  return !(a == b);
}

bool operator==(const Point& a, const Point& b) {
  return a.x == b.x && a.y == b.y;
}
bool operator!=(const Point& a, const Point& b) {
  return !(a == b);
}

bool operator==(const Line& a, const Line& b) {
  return a.a == b.a && a.b == b.b;
}
bool operator!=(const Line& a, const Line& b) {
  return !(a == b);
}

bool operator==(const Circle& a, const Circle& b) {
  return a.center == b.center && a.radius == b.radius;
}
bool operator!=(const Circle& a, const Circle& b) {
  return !(a == b);
}

bool operator==(const Triangle& a, const Triangle& b) {
  return a.a == b.a && a.b == b.b && a.c == b.c;
}
bool operator!=(const Triangle& a, const Triangle& b) {
  return !(a == b);
}

bool operator==(const Rectangle& a, const Rectangle& b) {
  return a.bottom_left == b.bottom_left && a.top_right == b.top_right;
}
bool operator!=(const Rectangle& a, const Rectangle& b) {
  return !(a == b);
}

bool operator==(const Area& a, const Area& b) {
  return a.width == b.width && a.height == b.height;
}
bool operator!=(const Area& a, const Area& b) {
  return !(a == b);
}

bool operator==(const WindowArea& a, const WindowArea& b) {
  return a.width == b.width && a.height == b.height;
}
bool operator!=(const WindowArea& a, const WindowArea& b) {
  return !(a == b);
}

bool operator==(const Color& a, const Color& b) {
  return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}
bool operator!=(const Color& a, const Color& b) {
  return !(a == b);
}

bool IsDimensionGreaterThanOrEqualTo(
    const Dimension& a, const Dimension& b,
    Real pixels) {
  Real av = a.unit == Unit::kPixel ?  a.scalar : a.scalar * pixels;
  Real bv = b.unit == Unit::kPixel ?  b.scalar : b.scalar * pixels;

  return av >= bv;
}

Dimension MaxDimension(
    const Dimension& a, const Dimension& b, Real pixels) {
  Real av = a.unit == Unit::kPixel ?  a.scalar : a.scalar * pixels;
  Real bv = b.unit == Unit::kPixel ?  b.scalar : b.scalar * pixels;

  return Dimension{ .scalar = std::max(av, bv), .unit = Unit::kPixel };
}

Dimension MinDimension(
    const Dimension& a, const Dimension& b, Real pixels) {
  Real av = a.unit == Unit::kPixel ?  a.scalar : a.scalar * pixels;
  Real bv = b.unit == Unit::kPixel ?  b.scalar : b.scalar * pixels;

  return Dimension{ .scalar = std::min(av, bv), .unit = Unit::kPixel };
}

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

Dimension MultiplyDimension(const Dimension& a, Real scalar) {
  return Dimension{ .scalar = a.scalar * scalar, .unit = a.unit };
}

std::unique_ptr<Interface> DefaultInterface() {
  std::unique_ptr<interface::RaylibInterface> interface =
    std::make_unique<interface::RaylibInterface>();

  interface->Open();

  return std::move(interface);
}

}  // namespace band
