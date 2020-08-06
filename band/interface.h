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

// Unit for a dimension.
//
// A pixel is the atomic unit on a window. A ratio is a propersion of a pixel
// dimension.
enum class Unit { kPixel, kRatio };

// Real is a continuous value.
using Real = double;

// Dimension has a scalar value and a unit.
struct Dimension {
  Real scalar;
  Unit unit;
};

// AddDimensions adds 'a' and 'b' depending on the 'pixels'.
Dimension AddDimensions(const Dimension& a, const Dimension& b, Real pixels);

// SubtractDimensions subtracts 'b' from 'a' depending on the 'pixels'.
Dimension SubtractDimensions(
    const Dimension& a, const Dimension& b, Real pixels);

// MultiplyDimensions multiplies the dimension by the scalar.
Dimension MultiplyDimensions(const Dimension& a, Real scalar);

// Point.
struct Point {
  Dimension x;
  Dimension y;
};

// Line.
struct Line {
  Point a;
  Point b;
};

// Circle.
struct Circle {
  Point center;
  Dimension radius;
};

// Triangle.
struct Triangle {
  Point a;
  Point b;
  Point c;
};

// Rectangle.
struct Rectangle {
  Point bottom_left;
  Point top_right;
};

// Area.
struct Area {
  Dimension width;
  Dimension height;
};

// WindowArea is just like an area but always specified in pixels.
struct WindowArea {
  Real width;
  Real height;
};

// Component of a color.
using Component = uint8_t;

// Color has red, green, blue, and opacity components.
struct Color {
  Component r;
  Component g;
  Component b;
  Component a;
};

// Action that can be performed on the interface.
enum class Action { kLeftClick, kRightClick, kClose, kBackspace };

// Leg of a rectangle.
enum class Leg { kWidth, kHeight };

// Interface which can be drawn on and receives actions.
//
// If a texture is selected, the texture is drawn on instead.
//
// StartDrawing must be called before each frame and StopDrawing must be called
// after each frame.
class Interface {
  public:
    virtual ~Interface() = default;

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

// DefaultInterface constructs the default-interface initialized with the passed
// parameters.
//
// This allows clients to avoid knowing the details of a specific interface and
// how it needs to be opened.
//
// Initial window-parameters are passed so that the screen can have the right
// attributes the first time it opens instead of being quickly modified.
std::unique_ptr<Interface> DefaultInterface(
    const WindowArea& window_area,
    const Text& window_name,
    const std::optional<File>& icon_file,
    Size target_fps);

}  // namespace band
