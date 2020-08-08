#pragma once

#include <optional>
#include <utility>

#include "band/interface.h"

namespace band {

// Style declares all settable attributes of a control.
struct Style {
  std::optional<Color> background_color;
  std::optional<Color> foreground_color;
  std::optional<Color> border_color;
  std::optional<Dimension> horizontal_border_thickness;
  std::optional<Dimension> vertical_border_thickness;
  std::optional<Dimension> horizontal_padding;
  std::optional<Dimension> vertical_padding;
  std::optional<Area> area;
  std::optional<FontId> font_id;
  std::optional<Dimension> font_size;
};

// ControlFactory creates controls with default style values based on what is
// set in the style.
class ControlFactory {
  public:
    explicit ControlFactory(const Style& style);

    template <typename T, typename... Args>
    T&& Create(Args&&... args);

  private:
    Style style_;

};

}  // namespace band

namespace band {

template <typename T, typename... Args>
T&& ControlFactory::Create(Args&&... args) {
  T t{std::forward<Args>(args)...};

  if (style_.background_color.has_value()) {
    t.SetBackgroundColor(style_.background_color.value());
  }

  if (style_.foreground_color.has_value()) {
    t.SetForegroundColor(style_.foreground_color.value());
  }

  if (style_.border_color.has_value()) {
    t.SetBorderColor(style_.border_color.value());
  }

  if (style_.horizontal_border_thickness.has_value()) {
    t.SetHorizontalBorderThickness(style_.horizontal_border_thickness.value());
  }

  if (style_.vertical_border_thickness.has_value()) {
    t.SetVerticalBorderThickness(style_.vertical_border_thickness.value());
  }

  if (style_.horizontal_padding.has_value()) {
    t.SetHorizontalPadding(style_.horizontal_padding.value());
  }

  if (style_.vertical_padding.has_value()) {
    t.SetVerticalPadding(style_.vertical_padding.value());
  }

  if (style_.area.has_value()) {
    t.SetArea(style_.area.value());
  }

  if (style_.font_id.has_value()) {
    t.SetFontId(style_.font_id.value());
  }

  if (style_.font_size.has_value()) {
    t.SetFontSize(style_.font_size.value());
  }

  return std::move(t);
}

}  // namesapce band
