#pragma once

#include <functional>

#include "band/interface.h"

namespace band {

// Control is an encapsulated feature that can be drawn on an interface.
class Control {
  public:
    virtual ~Control() = default;

    // Area of the control based on the interface.
    virtual ::band::Area Area(const Interface& interface) const = 0;

    // CleanUp anything that needs to be cleaned-up.
    //
    // This is useful for cleaning up local textures, images, fonts, or other
    // resources.
    virtual void CleanUp(Interface& interface) = 0;

    // Update allows the control to determine if attributes need to be updated
    // prior to being displayed.
    //
    // This is useful for when textures of controls are captured. Update can be
    // called every frame and the texture can be recaptured if anything changed.
    //
    // The point is passed to determine where the control will eventually be
    // drawn onto the screen. This is useful for cases like determining if
    // a control has been interacted with.
    virtual void Update(const Point& position, Interface& interface) = 0;

    // Draw the control.
    virtual void Draw(const Point& position, Interface& interface) = 0;

};

// BaseControl is a helper that provides default functionality for all control
// methods that can be overridden.
class BaseControl : public Control {
  public:
    ::band::Area Area(const Interface& interface) const override;

    void CleanUp(Interface& interface) override;
    void Update(const Point& position, Interface& interface) override;
    void Draw(const Point& position, Interface& interface) override;

};

// Run the root control until the window is closed and then clean up.
void Run(
    const Color& clear_color,
    Interface& interface, Control& control);

// CleanUp all controls starting at the root control.
void CleanUp(Interface& interface, Control& control);

// Update all controls starting at the root control.
void Update(
    const Point& position,
    Interface& interface, Control& control);

// DrawFrame draws the single control and triggers a frame.
//
// Typically, the control is a panel control containing the entire screen.
void DrawFrame(
    const Color& clear_color, const Point& position,
    Interface& interface, Control& control);

}  // namespace band
