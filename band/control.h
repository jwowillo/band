#pragma once

#include "band/interface.h"

namespace band {

// Control is an encapsulated feature that can be drawn on an interface.
class Control {
  public:
    virtual ~Control() = default;

    // Area of the control based on the interface.
    virtual ::band::Area Area(const Interface& interface) const = 0;

    // Update allows the control to determine if attributes need to be updated
    // prior to being displayed.
    //
    // This is useful for when textures of controls are captured. Update can be
    // called every frame and the texture can be recaptured if anything changed.
    virtual void Update(const Point& position, const Interface& interface) = 0;

    // Display the control.
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
