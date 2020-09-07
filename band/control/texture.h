#pragma once

#include <optional>

#include "band/control.h"
#include "band/interface.h"

namespace band {
namespace control {

// Texture captures a texture of a control and displays it.
class Texture : public BaseControl {
  public:
    void CaptureControl(Interface& interface, Control& control);

    ::band::Area Area(const Interface& interface) const override;

    void CleanUp(Interface& interface) override;
    void Update(const Point& position, Interface& interface) override;

    void Draw(const Point& position, Interface& interface) override;

  private:
    std::optional<TextureId> texture_id_ = std::nullopt;
    ::band::Area area_{};

};


}  // namespace control
}  // namespace band
