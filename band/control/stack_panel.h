#pragma once

#include <initializer_list>
#include <vector>

#include "band/control.h"
#include "band/control/anchor.h"
#include "band/interface.h"

namespace band {
namespace control {

// StackPanel arranges a collection of controls in a stack with a passed
// direction.
//
// The stacked controls can have an alignment with respect to the panel.
template <typename T>
class StackPanel : public Control {
  public:
    ::band::Alignment Alignment() const;
    void SetAlignment(const ::band::Alignment& alignment);

    ::band::Direction Direction() const;
    void SetDirection(const ::band::Direction& direction);

    template <typename Iter>
    void SetControls(const Iter& begin, const Iter& end);

    void SetControls(const std::initializer_list<T>& controls);

    // Area is the measured area of all the controls.
    ::band::Area Area(const Interface& interface) const override;

    void Update(const Point& position, const Interface& interface) override;

    void Display(const Point& position, Interface& interface) override;

  private:
    ::band::Alignment alignment_{};
    ::band::Direction direction_{};

    std::vector<T> controls_{};

};


}  // namespace control
}  // namespace band

namespace band {
namespace control {

template <typename T>
::band::Alignment StackPanel<T>::Alignment() const {
  return alignment_;
}

template <typename T>
void StackPanel<T>::SetAlignment(const ::band::Alignment& alignment) {
  alignment_ = alignment;
}

template <typename T>
::band::Direction StackPanel<T>::Direction() const {
  return direction_;
}

template <typename T>
void StackPanel<T>::SetDirection(const ::band::Direction& direction) {
  direction_ = direction;
}

template <typename T>
template <typename Iter>
void StackPanel<T>::SetControls(const Iter& begin, const Iter& end) {
  controls_ = std::vector<T>{begin, end};
}

template <typename T>
void StackPanel<T>::SetControls(const std::initializer_list<T>& controls) {
  controls_ = std::vector<T>{controls};
}

template <typename T>
::band::Area StackPanel<T>::Area(const Interface& interface) const {
  ::band::Area current_area{};

  auto width_function = MaxDimension;
  auto height_function = AddDimensions;
  if (direction_ == Direction::kHorizontal) {
    width_function = AddDimensions;
    height_function = MaxDimension;
  }

  for (
      typename decltype(controls_)::size_type i = 0u;
      i < controls_.size();
      i++) {
    ::band::Area control_area = controls_[i]->Area(interface);

    current_area.width = width_function(
        current_area.width, control_area.width,
        interface.WindowArea().width);
    current_area.height = height_function(
        current_area.height, control_area.height,
        interface.WindowArea().height);
  }

  return current_area;
}

template <typename T>
void StackPanel<T>::Update(const Point& position, const Interface& interface) {
  ::band::Area total_area = this->Area(interface);
  Point current_position = position;

  for (
      typename decltype(controls_)::size_type i = 0u;
      i < controls_.size();
      i++) {
    ::band::Area control_area = controls_[i]->Area(interface);

    Anchor<T> anchor{};
    anchor.SetHorizontalAlignment(alignment_);
    anchor.SetVerticalAlignment(Alignment::kTop);
    ::band::Area reference_area{};

    if (direction_ == Direction::kVertical) {
      reference_area.width = total_area.width;
      reference_area.height = control_area.height;
    } else {
      reference_area.width = control_area.width;
      reference_area.height = total_area.height;
    }

    anchor.SetReferenceArea(reference_area);
    anchor.SetControl(controls_[i]);

    anchor.Update(current_position, interface);

    if (direction_ == Direction::kVertical) {
      current_position.y = AddDimensions(
          current_position.y, control_area.height,
          interface.WindowArea().height);
    } else {
      current_position.x = AddDimensions(
          current_position.x, control_area.width,
          interface.WindowArea().width);
    }
  }
}

template <typename T>
void StackPanel<T>::Display(const Point& position, Interface& interface) {
  ::band::Area total_area = this->Area(interface);
  Point current_position = position;

  for (
      typename decltype(controls_)::size_type i = 0u;
      i < controls_.size();
      i++) {
    ::band::Area control_area = controls_[i]->Area(interface);

    Anchor<T> anchor;
    anchor.SetHorizontalAlignment(alignment_);
    anchor.SetVerticalAlignment(Alignment::kTop);
    ::band::Area reference_area{};

    if (direction_ == Direction::kVertical) {
      reference_area.width = total_area.width;
      reference_area.height = control_area.height;
    } else {
      reference_area.width = control_area.width;
      reference_area.height = total_area.height;
    }

    anchor.SetReferenceArea(reference_area);
    anchor.SetControl(controls_[i]);

    anchor.Display(current_position, interface);

    if (direction_ == Direction::kVertical) {
      current_position.y = AddDimensions(
          current_position.y, control_area.height,
          interface.WindowArea().height);
    } else {
      current_position.x = AddDimensions(
          current_position.x, control_area.width,
          interface.WindowArea().width);
    }
  }
}

}  // namespace control
}  // namespace band
