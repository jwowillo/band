#pragma once

#include "band/interface.h"

namespace band {

// Control is an encapsulated feature that can be drawn on an interface.
class Control {
  public:
    virtual ~Control() = default;

    virtual ::band::Area Area(const Interface& interface) const = 0;

    virtual void Update(const Point& position, const Interface& interface) = 0;
    virtual void Display(const Point& position, Interface& interface) = 0;

};

// Update all controls starting at the root control.
void Update(
    const Point& position, const Interface& interface,
    Control& control);

// DrawFrame draws the single control and triggers a frame.
//
// Typically, the control is a panel control containing the entire screen.
void DrawFrame(
    const Color& clear_color, const Point& position,
    Interface& interface, Control& control);

}  // namespace band
