#pragma once

#include <optional>

#include "band/control.h"
#include "band/control/anchor.h"
#include "band/control/border.h"
#include "band/control/rectangle.h"
#include "band/interface.h"

namespace band {
namespace control {

// Button that can be pressed.
//
// The button can have different colors based on the button state. The
// last-action is updated after update calls and can be used to determine if the
// button received an input.
template <typename T>
class Button : public Control {
  public:
    enum class Action { kNone, kPress, kHover };

    Color FillColor() const;
    void SetFillColor(const Color& color);

    Color HoverColor() const;
    void SetHoverColor(const Color& color);

    Color DisabledColor() const;
    void SetDisabledColor(const Color& color);

    Color BorderColor() const;
    void SetBorderColor(const Color& color);

    Alignment HorizontalAlignment() const;
    void SetHorizontalAlignment(const Alignment& alignment);

    Alignment VerticalAlignment() const;
    void SetVerticalAlignment(const Alignment& alignment);

    Dimension BorderThickness() const;
    void SetBorderThickness(const Dimension& border_thickness);

    void Disable();
    void Enable();

    bool IsEnabled() const;

    // SetArea to the passed area.
    //
    // If the area is nullopt, the area will be calculated based on the passed
    // control.
    void SetArea(const std::optional<::band::Area>& area);

    void SetControl(T control);

    Action LastAction() const;

    ::band::Area Area(const Interface& interface) const override;

    // Determine if the button was hovered, pressed, or nothing happened.
    void Update(
        const Point& position,
        const Interface& interface) override;

    void Display(const Point& position, Interface& interface) override;

  private:
    Color fill_color_{};
    Color hover_color_{};
    Color disabled_color_{};
    Color border_color_{};

    Alignment horizontal_alignment_{};
    Alignment vertical_alignment_{};

    Dimension border_thickness_{};

    bool is_enabled_ = true;

    std::optional<::band::Area> area_{};

    std::optional<T> control_ = std::nullopt;

    Action last_action_ = Action::kNone;

};


}  // namespace control
}  // namespace band

namespace band {
namespace control {

template <typename T>
Color Button<T>::FillColor() const {
  return fill_color_;
}

template <typename T>
void Button<T>::SetFillColor(const Color& color) {
  fill_color_ = color;
}

template <typename T>
Color Button<T>::HoverColor() const {
  return hover_color_;
}

template <typename T>
void Button<T>::SetHoverColor(const Color& color) {
  hover_color_ = color;
}

template <typename T>
Color Button<T>::DisabledColor() const {
  return disabled_color_;
}

template <typename T>
void Button<T>::SetDisabledColor(const Color& color) {
  disabled_color_ = color;
}

template <typename T>
Color Button<T>::BorderColor() const {
  return border_color_;
}

template <typename T>
void Button<T>::SetBorderColor(const Color& color) {
  border_color_ = color;
}

template <typename T>
Alignment Button<T>::HorizontalAlignment() const {
  return horizontal_alignment_;
}

template <typename T>
void Button<T>::SetHorizontalAlignment(const Alignment& alignment) {
  horizontal_alignment_ = alignment;
}

template <typename T>
Alignment Button<T>::VerticalAlignment() const {
  return vertical_alignment_;
}

template <typename T>
void Button<T>::SetVerticalAlignment(const Alignment& alignment) {
  vertical_alignment_ = alignment;
}

template <typename T>
Dimension Button<T>::BorderThickness() const {
  return border_thickness_;
}

template <typename T>
void Button<T>::SetBorderThickness(const Dimension& border_thickness) {
  border_thickness_ = border_thickness;
}

template <typename T>
void Button<T>::Disable() {
  is_enabled_ = false;
}

template <typename T>
void Button<T>::Enable() {
  is_enabled_ = true;
}

template <typename T>
bool Button<T>::IsEnabled() const {
  return is_enabled_;
}

template <typename T>
void Button<T>::SetArea(const std::optional<::band::Area>& area) {
  area_ = area;
}

template <typename T>
void Button<T>::SetControl(T control) {
  control_ = control;
}

template <typename T>
typename band::control::Button<T>::Action Button<T>::LastAction() const {
  return last_action_;
}

template <typename T>
::band::Area Button<T>::Area(const Interface& interface) const {
  if (!area_.has_value()) {
    if (!control_.has_value()) {
      return ::band::Area{};
    }

    return control_.value()->Area(interface);
  }

  return area_.value();
}

template <typename T>
void Button<T>::Update(
    const Point& position,
    const Interface& interface) {
  ::band::Area area = Area(interface);

  Point mouse_position = interface.MousePosition();
  bool did_press = interface.HasAction(Interface::Action::kLeftClick);

  bool is_right_of = IsDimensionGreaterThanOrEqualTo(
      mouse_position.x, position.x,
      interface.WindowArea().width);
  bool is_above = IsDimensionGreaterThanOrEqualTo(
      mouse_position.y, position.y,
      interface.WindowArea().height);
  bool is_left_of = IsDimensionGreaterThanOrEqualTo(
      AddDimensions(position.x, area.width, interface.WindowArea().width),
      mouse_position.x,
      interface.WindowArea().width);
  bool is_below = IsDimensionGreaterThanOrEqualTo(
      AddDimensions(position.y, area.height, interface.WindowArea().height),
      mouse_position.y,
      interface.WindowArea().height);

  if (!is_right_of || !is_above || !is_below || !is_left_of) {
    last_action_ = Action::kNone;
  } else {
    last_action_ = did_press ?  Action::kPress : Action::kHover;
  }
}

template <typename T>
void Button<T>::Display(const Point& position, Interface& interface) {
  ::band::Area area = Area(interface);

  Rectangle rectangle{};
  rectangle.SetArea(area);

  if (is_enabled_) {
    switch (last_action_) {
    case Action::kNone:
      rectangle.SetColor(fill_color_);
      break;
    case Action::kHover:
    case Action::kPress:
    default:
      rectangle.SetColor(hover_color_);
      break;
    }
  } else {
    rectangle.SetColor(disabled_color_);
  }

  Border border{};
  border.SetArea(area);
  border.SetThickness(border_thickness_);
  border.SetColor(border_color_);

  Anchor<T> anchor{};
  anchor.SetHorizontalAlignment(horizontal_alignment_);
  anchor.SetVerticalAlignment(vertical_alignment_);
  anchor.SetReferenceArea(area);
  if (control_.has_value()) {
    anchor.SetControl(control_.value());
  }

  rectangle.Display(position, interface);
  border.Display(position, interface);
  anchor.Display(position, interface);
}

}  // namespace control
}  // namespace band
