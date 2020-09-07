#pragma once

#include "band/control.h"
#include "band/interface.h"

namespace band {
namespace control {

// Fps displays the FPS.
//
// The area isn't calculated because it is meant to be an overlay left to the
// interface.
class Fps : public BaseControl {
  public:
    void Draw(const Point& position, Interface& interface) override;

};


}  // namespace control
}  // namespace band
