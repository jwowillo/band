#include "band/control/image.h"

namespace band {
namespace control {

::band::ImageId Image::ImageId() const {
  return image_id_;
}

void Image::SetImageId(::band::ImageId id) {
  texture_id_ = std::nullopt;
  image_id_ = id;
}

void Image::SetWidth(const std::optional<Dimension>& width) {
  texture_id_ = std::nullopt;
  width_ = width;
}

void Image::SetHeight(const std::optional<Dimension>& height) {
  texture_id_ = std::nullopt;
  height_ = height;
}

::band::Area Image::Area(const Interface& interface) const {
  if (width_ == std::nullopt && height_ == std::nullopt) {
    return ::band::Area{};
  }

  Dimension width{};
  Dimension height{};
  WindowArea window_area = interface.WindowArea();

  // The width and height need to be in pixel values to preserve the aspect
  // ratio.

  Real aspect_ratio =
    interface.ImageArea(image_id_).width.scalar /
    interface.ImageArea(image_id_).height.scalar;

  bool skip_height = false;
  if (width_ == std::nullopt) {
    width = MultiplyDimension(height_.value(), aspect_ratio);
    if (width.unit != Unit::kPixel) {
      width.scalar *= window_area.height;
      width.unit = Unit::kPixel;
    }

    if (width.scalar > window_area.width) {
      width.scalar = window_area.width;
      height.scalar = window_area.width * 1.0 / aspect_ratio;
      height.unit = Unit::kPixel;
      skip_height = true;
    }
  } else {
    width = width_.value();
  }
  if (height_ == std::nullopt) {
    // height must have a value if skip-height is true because only one of width
    // and height can be left unset. Because of this, this branch will never
    // occur if skip-height is true.
    height = MultiplyDimension(width_.value(), 1.0 / aspect_ratio);
    if (height.unit != Unit::kPixel) {
      height.scalar *= window_area.width;
      height.unit = Unit::kPixel;
    }

    if (height.scalar > window_area.height) {
      height.scalar = window_area.height;
      width.scalar = window_area.height * aspect_ratio;
      width.unit = Unit::kPixel;
    }
  } else {
    // Don't want to mess up the height if it was set due to clipping.
    if (!skip_height) {
      height = height_.value();
    }
  }

  return ::band::Area{ .width = width, .height = height };
}

void Image::CleanUp(Interface& interface) {
  if (!texture_id_.has_value()) {
    return;
  }

  interface.DeleteTexture(texture_id_.value());
}

void Image::Draw(const Point& position, Interface& interface) {
  if (!texture_id_.has_value() || last_window_area_ != interface.WindowArea()) {
    if (texture_id_.has_value()) {
      interface.DeleteTexture(texture_id_.value());
    }

    last_window_area_ = interface.WindowArea();
    texture_id_ = interface.CreateImageTexture(
        image_id_, this->Area(interface));
  }

  interface.DrawTexture(texture_id_.value(), position);
}

}  // namespace control
}  // namespace band
