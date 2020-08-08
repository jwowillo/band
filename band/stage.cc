#include "band/stage.h"

namespace band {

Stage::Stage(Interface& interface) : interface_{interface} { }

Stage::~Stage() {
  for (const std::reference_wrapper<Control>& control : controls_) {
    control.get().CleanUp(interface_);
  }
}

}  // namespace band
