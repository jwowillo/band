#pragma once

#include "band/interface.h"
#include "band/interface/base_interface_decorator.h"

namespace band {
namespace interface {

// DebugInterfaceDecorator decorates an interface to draw the FPS every frame.
template <typename T>
class DebugInterfaceDecorator : public BaseInterfaceDecorator<T> {
  public:
    using BaseInterfaceDecorator<T>::BaseInterfaceDecorator;

    // StopDrawing draws the FPS then ends the drawing.
    void StopDrawing() override;

    // DrawFps does nothing since the FPS is already drawn.
    void DrawFps(const Point& position) override;

};

}  // namespace interface
}  // namespace band

namespace band {
namespace interface {

template <typename T>
void DebugInterfaceDecorator<T>::StopDrawing() {
  this->interface_->DrawFps(band::Point{});

  BaseInterfaceDecorator<T>::StopDrawing();
}

template <typename T>
void DebugInterfaceDecorator<T>::DrawFps(const Point&) { }

}  // namespace interface
}  // namespace band
