#pragma once

#include "band/interface.h"
#include "band/interface/base_interface_decorator.h"

namespace band {
namespace interface {

// SectionInterfaceDecorator decorates an interface so that only a portion of
// the window is available.
template <typename T>
class SectionInterfaceDecorator : public BaseInterfaceDecorator<T> {
  public:
    SectionInterfaceDecorator(T interface, const Area& section);

    ::band::WindowArea WindowArea() const;

  private:
    Area section_;

};

}  // namespace interface
}  // namespace band

namespace band {
namespace interface {

template <typename T>
SectionInterfaceDecorator<T>::SectionInterfaceDecorator(
    T interface, const Area& section) :
  BaseInterfaceDecorator<T>{std::forward<T>(interface)}, section_{section} { }

template <typename T>
::band::WindowArea SectionInterfaceDecorator<T>::WindowArea() const {
  ::band::WindowArea actual_area = BaseInterfaceDecorator<T>::WindowArea();

  return ::band::WindowArea{
    .width = section_.width.unit == Unit::kRatio ?
      section_.width.scalar * actual_area.width :
      section_.width.scalar,
    .height = section_.height.unit == Unit::kRatio ?
      section_.height.scalar * actual_area.height :
      section_.height.scalar,
  };
}

}  // namespace interface
}  // namespace band
