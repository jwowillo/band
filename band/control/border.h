#pragma once

#include <optional>

#include "band/control.h"
#include "band/interface.h"

namespace band {
namespace control {

// Border draws a rectangular border around the area without exceeding it.
//
// The thickness is based on the smallest leg of the window area if the
// thickness is a ratio.
class Border : public Control {
  public:
    Dimension Thickness() const;
    void SetThickness(const Dimension& thickness);

    ::band::Color Color() const;
    void SetColor(const ::band::Color& color);

    // RealBorderThickness returns the actual border-thickness in terms of
    // pixels.
    //
    // This is needed to hide the logic on which leg of the area is used to
    // determine the real border-thickness.
    Real RealBorderThickness(const Interface& interface) const;

    void SetArea(const ::band::Area& area);

    ::band::Area Area(const Interface& interface) const override;

    void Update(const Point& position, const Interface& interface) override;

    void Display(const Point& position, Interface& interface) override;

  private:
    ::band::Area area_{};
    Dimension thickness_{};
    ::band::Color color_{};

};


}  // namespace control
}  // namespace band
