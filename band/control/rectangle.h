#pragma once

#include "band/control.h"
#include "band/interface.h"

namespace band {
namespace control {

// Rectangle is a solid color filling an area.
class Rectangle : public Control {
  public:
    ::band::Color Color() const;
    void SetColor(const ::band::Color& color);

    void SetArea(const ::band::Area& area);

    ::band::Area Area(const Interface& interface) const override;

    void Update(const Point& position, const Interface& interface) override;

    void Display(const Point& position, Interface& interface) override;

  private:
    ::band::Area area_{};
    ::band::Color color_{};

};


}  // namespace control
}  // namespace band
