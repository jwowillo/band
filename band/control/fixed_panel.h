#pragma once

#include <cmath>
#include <initializer_list>
#include <utility>
#include <vector>

#include "band/control.h"
#include "band/interface.h"

namespace band {
namespace control {

// FixedPanel displays controls in a single control as arranged.
template <typename T>
class FixedPanel : public BaseControl {
  public:
    template <typename Iter>
    void SetControls(const Iter& begin, const Iter& end);

    void SetControls(const std::initializer_list<std::pair<T, Point>>& controls);

    // Area is the measured area bounding all of the controls.
    ::band::Area Area(const Interface& interface) const override;

    void CleanUp(Interface& interface) override;
    void Update(const Point& position, Interface& interface) override;

    void Draw(const Point& position, Interface& interface) override;

  private:
    std::vector<std::pair<T, Point>> controls_{};

};


}  // namespace control
}  // namespace band

namespace band {
namespace control {

template <typename T>
template <typename Iter>
void FixedPanel<T>::SetControls(const Iter& begin, const Iter& end) {
  controls_ = std::vector<std::pair<T, Point>>{begin, end};
}

template <typename T>
void FixedPanel<T>::SetControls(
    const std::initializer_list<std::pair<T, Point>>& controls) {
  controls_ = std::vector<std::pair<T, Point>>{controls};
}

template <typename T>
::band::Area FixedPanel<T>::Area(const Interface& interface) const {
  ::band::Area current_area{};

  for (
      typename decltype(controls_)::size_type i = 0u;
      i < controls_.size();
      i++) {
    ::band::Area control_area = controls_[i].first->Area(interface);

    Dimension right_extent = controls_[i].second.x;
    Dimension bottom_extent = controls_[i].second.y;

    right_extent = AddDimensions(
        right_extent, control_area.width,
        interface.WindowArea().width);
    bottom_extent = AddDimensions(
        bottom_extent, control_area.height,
        interface.WindowArea().height);

    current_area.width = MaxDimension(
        current_area.width, right_extent,
        interface.WindowArea().width);
    current_area.height = MaxDimension(
        current_area.height, bottom_extent,
        interface.WindowArea().height);
  }

  return current_area;
}

template <typename T>
void FixedPanel<T>::CleanUp(Interface& interface) {
  for (
      typename decltype(controls_)::size_type i = 0u;
      i < controls_.size();
      i++) {
    controls_[i].first->CleanUp(interface);
  }
}

template <typename T>
void FixedPanel<T>::Update(const Point& position, Interface& interface) {
  for (
      typename decltype(controls_)::size_type i = 0u;
      i < controls_.size();
      i++) {
    Point control_position = position;
    control_position.x = AddDimensions(
        control_position.x, controls_[i].second.x,
        interface.WindowArea().width);
    control_position.y = AddDimensions(
        control_position.y, controls_[i].second.y,
        interface.WindowArea().height);

    controls_[i].first->Update(control_position, interface);
  }
}

template <typename T>
void FixedPanel<T>::Draw(const Point& position, Interface& interface) {
  for (
      typename decltype(controls_)::size_type i = 0u;
      i < controls_.size();
      i++) {
    Point control_position = position;
    control_position.x = AddDimensions(
        control_position.x, controls_[i].second.x,
        interface.WindowArea().width);
    control_position.y = AddDimensions(
        control_position.y, controls_[i].second.y,
        interface.WindowArea().height);

    controls_[i].first->Draw(control_position, interface);
  }
}

}  // namespace control
}  // namespace band
