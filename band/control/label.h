#pragma once

#include "band/control.h"
#include "band/interface.h"

namespace band {
namespace control {

// Label is a control that displays text.
class Label : public Control {
  public:
    ::band::Text Text() const;
    void SetText(const ::band::Text& text);

    Dimension FontSize() const;
    void SetFontSize(const Dimension& font_size);

    Color FontColor() const;
    void SetFontColor(const Color& font_color);

    ::band::FontId FontId() const;
    void SetFontId(::band::FontId font_id);

    // Area is the measured size of the text.
    ::band::Area Area(const Interface& interface) const override;

    void Update(const Point& position, const Interface& interface) override;

    void Display(const Point& position, Interface& interface) override;

  private:
    ::band::Text text_{};
    Dimension font_size_{};
    Color font_color_{};
    ::band::FontId font_id_{};

};

}  // namespace control
}  // namespace band
