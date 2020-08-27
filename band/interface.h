#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>

namespace band {

// This file aliases lots of simple types. The reason for this is the desire to
// minimize includes by dependents of this library. Since many of the types are
// defined in many standard-headers, dependents would have to remember to import
// all of them. This way, importing the library is sufficient. It also makes
// providing more complex types for the aliases less of an undertaking in the
// future.

// File is a wrapper around the bytes of a file.
struct File {
  const uint8_t* bytes;
  const size_t n;
};

// Text is a sequence of characters.
using Text = std::string;

// Size is an integral magnitude.
using Size = uint32_t;

// TextureId identifies a texture allowing the implementation to be
// interface-dependent.
using TextureId = size_t;

// ImageId identifies an image allowing the implementation to be
// interface-dependent.
using ImageId = size_t;

// FontId identifies a font allowing the implementation to be
// interface-dependent.
using FontId = size_t;

// Alignment in an area.
//
// If the direction of something is horizontal, top is left and bottom is right.
enum class Alignment { kTop, kMiddle, kBottom };

// Direction in an area.
enum class Direction { kHorizontal, kVertical };

// Unit for a dimension.
//
// A pixel is the atomic unit on a window. A ratio is a propersion of a pixel
// dimension.
enum class Unit { kPixel, kRatio };

// Real is a continuous value.
using Real = double;

// Dimension has a scalar value and a unit.
struct Dimension {
  Real scalar = 0.0;
  Unit unit{};
};
bool operator==(const Dimension& a, const Dimension& b);
bool operator!=(const Dimension& a, const Dimension& b);

// IsDimensionGreaterThanOrEqualTo returns if 'a' is greater than or equal to
// b.
bool IsDimensionGreaterThanOrEqualTo(
    const Dimension& a, const Dimension& b,
    Real pixels);

// MaxDimension determines the max of 'a' and 'b' depending on the 'pixels'.
Dimension MaxDimension(const Dimension& a, const Dimension& b, Real pixels);

// MinDimension determines the min of 'a' and 'b' depending on the 'pixels'.
Dimension MinDimension(const Dimension& a, const Dimension& b, Real pixels);

// AddDimensions adds 'a' and 'b' depending on the 'pixels'.
Dimension AddDimensions(const Dimension& a, const Dimension& b, Real pixels);

// SubtractDimensions subtracts 'b' from 'a' depending on the 'pixels'.
Dimension SubtractDimensions(
    const Dimension& a, const Dimension& b, Real pixels);

// MultiplyDimension multiplies the dimension by the scalar.
Dimension MultiplyDimension(const Dimension& a, Real scalar);

// Point.
struct Point {
  Dimension x{};
  Dimension y{};
};
bool operator!=(const Point& a, const Point& b);

// Line.
struct Line {
  Point a{};
  Point b{};
};
bool operator!=(const Line& a, const Line& b);

// Circle.
struct Circle {
  Point center{};
  Dimension radius{};
};
bool operator!=(const Circle& a, const Circle& b);

// Triangle.
struct Triangle {
  Point a{};
  Point b{};
  Point c{};
};
bool operator!=(const Triangle& a, const Triangle& b);

// Rectangle.
struct Rectangle {
  Point bottom_left{};
  Point top_right{};
};
bool operator!=(const Rectangle& a, const Rectangle& b);

// Area.
struct Area {
  Dimension width{};
  Dimension height{};
};
bool operator!=(const Area& a, const Area& b);

// WindowArea is just like an area but always specified in pixels.
struct WindowArea {
  Real width{};
  Real height{};
};
bool operator!=(const WindowArea& a, const WindowArea& b);

// Component of a color.
using Component = uint8_t;

// Color has red, green, blue, and opacity components.
struct Color {
  Component r{};
  Component g{};
  Component b{};
  Component a{};
};
bool operator!=(const Color& a, const Color& b);

// Leg of a rectangle.
enum class Leg { kWidth, kHeight };

// Interface which can be drawn on and receives actions.
//
// If a texture is selected, the texture is drawn on instead.
//
// StartDrawing must be called before each frame and StopDrawing must be called
// after each frame.
//
// The positive horizontal-drawing-axis goes from left-to-right and the positive
// vertical-drawing-axis goes from top-to-bottom.
class Interface {
  public:
    enum class Action { kLeftClick, kRightClick, kClose, kBackspace };

    virtual ~Interface() = default;

    virtual void SetTargetFps(Size fps) = 0;
    virtual void SetWindowArea(const ::band::WindowArea& area) = 0;
    virtual void SetIcon(ImageId id) = 0;
    virtual void SetTitle(const Text& text) = 0;
    virtual void ToggleFullscreen() = 0;

    virtual void StartDrawing() = 0;
    virtual void StopDrawing() = 0;

    virtual ImageId LoadImage(const File& file) = 0;
    virtual void DeleteImage(ImageId id) = 0;
    virtual void DeleteAllImages() = 0;

    virtual FontId LoadFont(const File& file) = 0;
    virtual void DeleteFont(FontId id) = 0;
    virtual void DeleteAllFonts() = 0;

    virtual TextureId CreateBlankTexture(const Area& area) = 0;
    virtual TextureId CreateImageTexture(ImageId id, const Area& area) = 0;
    virtual void DeleteTexture(TextureId id) = 0;
    virtual void DeleteAllTextures() = 0;
    virtual void SelectTexture(TextureId id) = 0;
    virtual void UnselectTexture() = 0;
    virtual void DrawTexture(TextureId id, const Point& position) = 0;

    virtual void Clear(const Color& color) = 0;
    // DrawLine with a thickness determined by the size fo the leg of the window's
    // area if a ratio-dimension is passed.
    virtual void DrawLine(
        const Line& line, const Dimension& thickness,
        const Leg& leg, const Color& color) = 0;
    // DrawCircle with a radius determined by the size fo the leg of the window's
    // area if a ratio-dimension is passed.
    virtual void DrawCircle(
        const Circle& circle, const Leg& leg, const Color& color) = 0;
    virtual void DrawRectangle(
        const Rectangle& rectangle, const Color& color) = 0;
    // DrawTriangle with points specified in counter-clockwise order.
    virtual void DrawTriangle(const Triangle& triangle, const Color& color) = 0;
    // DrawText where each character has a dimension with ratio relative to the
    // window's height.
    virtual void DrawText(
        const Text& text, const Point& position,
        const Dimension& dimension, const Color& color,
        FontId id) = 0;
    virtual void DrawFps(const Point& position) = 0;

    // MeasureText returns an 'Area' that can have pixel or ratio units depending
    // on the interface. The ratio is relative to the window's height.
    virtual Area MeasureText(
        const Text& text, const Dimension& dimension,
        FontId id) const = 0;
    virtual bool HasAction(const Action& action) const = 0;
    virtual std::optional<char> CharacterPressed() const = 0;
    // MousePosition returns a 'Point' that can have pixel or ratio units
    // depending on the interface.
    virtual Point MousePosition() const = 0;
    virtual ::band::WindowArea WindowArea() const = 0;

};

// DefaultInterface constructs the default-interface.
//
// This allows clients to avoid knowing the details of a specific interface and
// how it needs to be opened.
std::unique_ptr<Interface> DefaultInterface();

}  // namespace band
