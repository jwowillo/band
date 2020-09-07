#pragma once

#include <optional>

#include "band/control.h"
#include "band/interface.h"
#include "band/interface/section_interface_decorator.h"

namespace band {
namespace control {

// PaddedPanel is a panel with padded borders.
//
// Controls inside the panel think the window's area is only that of the area
// inside of the padding.
template <typename T>
class PaddedPanel : public BaseControl {
  public:
    Dimension HorizontalPadding() const;
    void SetHorizontalPadding(const Dimension& padding);

    Dimension VerticalPadding() const;
    void SetVerticalPadding(const Dimension& padding);

    // ReferenceArea describes the actual area before padding.
    ::band::Area ReferenceArea() const;
    void SetReferenceArea(const ::band::Area& area);

    void SetControl(T control);

    ::band::Area Area(const Interface& interface) const override;

    void Update(const Point& position, Interface& interface) override;

    void Draw(const Point& position, Interface& interface) override;

  private:
    Dimension horizontal_padding_{};
    Dimension vertical_padding_{};

    ::band::Area area_{};
    std::optional<T> control_ = std::nullopt;

};


}  // namespace control
}  // namespace band

namespace band {
namespace control {

template <typename T>
Dimension PaddedPanel<T>::HorizontalPadding() const {
  return horizontal_padding_;
}

template <typename T>
void PaddedPanel<T>::SetHorizontalPadding(const Dimension& padding) {
  horizontal_padding_ = padding;
}

template <typename T>
Dimension PaddedPanel<T>::VerticalPadding() const {
  return vertical_padding_;
}

template <typename T>
void PaddedPanel<T>::SetVerticalPadding(const Dimension& padding) {
  vertical_padding_ = padding;
}

template <typename T>
::band::Area PaddedPanel<T>::ReferenceArea() const {
  return area_;
}

template <typename T>
void PaddedPanel<T>::SetReferenceArea(const ::band::Area& area) {
  area_ = area;
}

template <typename T>
void PaddedPanel<T>::SetControl(T control) {
  control_ = std::forward<T>(control);
}

template <typename T>
::band::Area PaddedPanel<T>::Area(const Interface&) const {
  return area_;
}

template <typename T>
void PaddedPanel<T>::Update(const Point& position, Interface& interface) {
  if (control_ == std::nullopt) {
    return;
  }

  ::band::Area inverted_area{};
  inverted_area.width = SubtractDimensions(
      area_.width, MultiplyDimension(horizontal_padding_, 2.0),
      interface.WindowArea().width);
  inverted_area.height = SubtractDimensions(
      area_.height, MultiplyDimension(vertical_padding_, 2.0),
      interface.WindowArea().height);
  interface::SectionInterfaceDecorator<Interface*> decorator{
    &interface, inverted_area};

  Point offset = position;
  offset.x = band::AddDimensions(
      offset.x, horizontal_padding_,
      interface.WindowArea().width);
  offset.y = band::AddDimensions(
      offset.x, vertical_padding_,
      interface.WindowArea().width);

  control_.value()->Update(offset, decorator);
}

template <typename T>
void PaddedPanel<T>::Draw(const Point& position, Interface& interface) {
  if (control_ == std::nullopt) {
    return;
  }

  ::band::Area inverted_area{};
  inverted_area.width = SubtractDimensions(
      area_.width, MultiplyDimension(horizontal_padding_, 2.0),
      interface.WindowArea().width);
  inverted_area.height = SubtractDimensions(
      area_.height, MultiplyDimension(vertical_padding_, 2.0),
      interface.WindowArea().height);
  interface::SectionInterfaceDecorator<Interface*> decorator{
    &interface, inverted_area};

  Point offset = position;
  offset.x = band::AddDimensions(
      offset.x, horizontal_padding_,
      interface.WindowArea().width);
  offset.y = band::AddDimensions(
      offset.y, vertical_padding_,
      interface.WindowArea().height);

  control_.value()->Draw(offset, decorator);
}

}  // namespace control
}  // namespace band
