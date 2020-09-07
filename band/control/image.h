#pragma once

#include <optional>

#include "band/control.h"
#include "band/interface.h"

namespace band {
namespace control {

// Image displays an image.
//
// If one of the width or height isn't set, the other is set to a value based on
// the aspect-ratio of the image. Additionally, if the calculated height for the
// other leg would exceed the window-area, the known leg is clipped as if the
// real known leg is the limiting window leg.
class Image : public BaseControl {
  public:
    ::band::ImageId ImageId() const;
    void SetImageId(::band::ImageId id);

    void SetWidth(const std::optional<Dimension>& width);
    void SetHeight(const std::optional<Dimension>& height);

    // Area calculated based on the known and unknown legs.
    ::band::Area Area(const Interface& interface) const override;

    void CleanUp(Interface& interface) override;

    void Draw(const Point& position, Interface& interface) override;

  private:
    std::optional<TextureId> texture_id_ = std::nullopt;

    std::optional<Dimension> width_ = std::nullopt;
    std::optional<Dimension> height_ = std::nullopt;

    WindowArea last_window_area_{};
    ::band::ImageId image_id_{};

};


}  // namespace control
}  // namespace band
