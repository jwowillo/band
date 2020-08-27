#pragma once

#include <optional>

#include "band/control.h"
#include "band/interface.h"

namespace band {
namespace control {

// Texture captures a texture of a control and displays it.
class Texture : public Control {
  public:
    void CaptureControl(Interface& interface, Control& control);
    void CleanUp(Interface& interface);

    ::band::Area Area(const Interface& interface) const override;

    void Update(const Point& position, const Interface& interface) override;

    void Display(const Point& position, Interface& interface) override;

  private:
    std::optional<TextureId> texture_id_ = std::nullopt;
    ::band::Area area_{};

};


}  // namespace control
}  // namespace band
