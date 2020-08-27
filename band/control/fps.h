#pragma once

#include "band/control.h"
#include "band/interface.h"

namespace band {
namespace control {

// Fps displays the FPS.
//
// The area isn't calculated because it is meant to be an overlay left to the
// interface.
class Fps : public Control {
  public:
    ::band::Area Area(const Interface& interface) const override;

    void Update(const Point& position, const Interface& interface) override;

    void Display(const Point& position, Interface& interface) override;

};


}  // namespace control
}  // namespace band
