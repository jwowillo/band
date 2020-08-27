#pragma once

#include <optional>

#include "band/control.h"
#include "band/interface.h"

namespace band {
namespace control {

// Anchor the control with respect to the reference area.
template <typename T>
class Anchor : public Control {
  public:
    Alignment HorizontalAlignment() const;
    void SetHorizontalAlignment(const Alignment& alignment);

    Alignment VerticalAlignment() const;
    void SetVerticalAlignment(const Alignment& alignment);

    ::band::Area ReferenceArea() const;
    void SetReferenceArea(const ::band::Area& area);

    void SetControl(T control);

    // Area is the measured area of all the controls.
    ::band::Area Area(const Interface& interface) const override;

    void Update(const Point& position, const Interface& interface) override;

    void Display(const Point& position, Interface& interface) override;

  private:
    Alignment horizontal_alignment_{};
    Alignment vertical_alignment_{};

    ::band::Area area_{};
    std::optional<T> control_ = std::nullopt;

};


}  // namespace control
}  // namespace band

namespace band {
namespace control {

template <typename T>
Alignment Anchor<T>::HorizontalAlignment() const {
  return horizontal_alignment_;
}

template <typename T>
void Anchor<T>::SetHorizontalAlignment(const Alignment& alignment) {
  horizontal_alignment_ = alignment;
}

template <typename T>
Alignment Anchor<T>::VerticalAlignment() const {
  return vertical_alignment_;
}

template <typename T>
void Anchor<T>::SetVerticalAlignment(const Alignment& alignment) {
  vertical_alignment_ = alignment;
}

template <typename T>
::band::Area Anchor<T>::ReferenceArea() const {
  return area_;
}

template <typename T>
void Anchor<T>::SetReferenceArea(const ::band::Area& area) {
  area_ = area;
}

template <typename T>
void Anchor<T>::SetControl(T control) {
  control_ = control;
}

template <typename T>
::band::Area Anchor<T>::Area(const Interface&) const {
  return area_;
}

template <typename T>
void Anchor<T>::Update(const Point& position, const Interface& interface) {
  if (control_ == std::nullopt) {
    return;
  }

  ::band::Area control_area = control_.value()->Area(interface);
  Point offset{};

  if (horizontal_alignment_ == Alignment::kMiddle ||
      horizontal_alignment_ == Alignment::kBottom) {
    offset.x = SubtractDimensions(
        area_.width, control_area.width,
        interface.WindowArea().width);

    if (horizontal_alignment_ == Alignment::kMiddle) {
      offset.x = MultiplyDimension(offset.x, 0.5);
    }
  }

  if (vertical_alignment_ == Alignment::kMiddle ||
      vertical_alignment_ == Alignment::kBottom) {
    offset.y = SubtractDimensions(
        area_.height, control_area.height,
        interface.WindowArea().height);

    if (vertical_alignment_ == Alignment::kMiddle) {
      offset.y = MultiplyDimension(offset.y, 0.5);
    }
  }

  offset.x = AddDimensions(offset.x, position.x, interface.WindowArea().width);
  offset.y = AddDimensions(offset.y, position.y, interface.WindowArea().height);

  control_.value()->Update(offset, interface);
}

template <typename T>
void Anchor<T>::Display(const Point& position, Interface& interface) {
  if (control_ == std::nullopt) {
    return;
  }

  ::band::Area control_area = control_.value()->Area(interface);
  Point offset{};

  if (horizontal_alignment_ == Alignment::kMiddle ||
      horizontal_alignment_ == Alignment::kBottom) {
    offset.x = SubtractDimensions(
        area_.width, control_area.width,
        interface.WindowArea().width);

    if (horizontal_alignment_ == Alignment::kMiddle) {
      offset.x = MultiplyDimension(offset.x, 0.5);
    }
  }

  if (vertical_alignment_ == Alignment::kMiddle ||
      vertical_alignment_ == Alignment::kBottom) {
    offset.y = SubtractDimensions(
        area_.height, control_area.height,
        interface.WindowArea().height);

    if (vertical_alignment_ == Alignment::kMiddle) {
      offset.y = MultiplyDimension(offset.y, 0.5);
    }
  }

  offset.x = AddDimensions(offset.x, position.x, interface.WindowArea().width);
  offset.y = AddDimensions(offset.y, position.y, interface.WindowArea().height);

  control_.value()->Display(offset, interface);
}

}  // namespace control
}  // namespace band
