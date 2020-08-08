#include "band/styler.h"

namespace band {

Styler::Styler(const Style& style) : style_{style} { }

void Styler::Apply(Control& control) {
  if (style_.background_color.has_value()) {
    control.SetBackgroundColor(style_.background_color.value());
  }

  if (style_.foreground_color.has_value()) {
    control.SetForegroundColor(style_.foreground_color.value());
  }

  if (style_.border_color.has_value()) {
    control.SetBorderColor(style_.border_color.value());
  }

  if (style_.horizontal_border_thickness.has_value()) {
    control.SetHorizontalBorderThickness(
        style_.horizontal_border_thickness.value());
  }

  if (style_.vertical_border_thickness.has_value()) {
    control.SetVerticalBorderThickness(
        style_.vertical_border_thickness.value());
  }

  if (style_.horizontal_padding.has_value()) {
    control.SetHorizontalPadding(style_.horizontal_padding.value());
  }

  if (style_.vertical_padding.has_value()) {
    control.SetVerticalPadding(style_.vertical_padding.value());
  }

  if (style_.area.has_value()) {
    control.SetArea(style_.area.value());
  }

  if (style_.font_id.has_value()) {
    control.SetFontId(style_.font_id.value());
  }

  if (style_.font_size.has_value()) {
    control.SetFontSize(style_.font_size.value());
  }
}

}  // namespace band
