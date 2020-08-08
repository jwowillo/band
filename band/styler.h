#pragma once

#include <optional>

#include "band/control.h"
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

// Styler styles controls with style-values based on what is set in the passed
// style-structure.
class Styler {
  public:
    explicit Styler(const Style& style);

    void Apply(Control& control);

  private:
    Style style_;

};

}  // namespace band
