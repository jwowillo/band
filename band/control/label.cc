#include "band/control/label.h"

namespace band {
namespace control {

::band::Text Label::Text() const {
  return text_;
}

void Label::SetText(const ::band::Text& text) {
  text_ = text;
}

Dimension Label::FontSize() const {
  return font_size_;
}

void Label::SetFontSize(const Dimension& font_size) {
  font_size_ = font_size;
}

Color Label::FontColor() const {
  return font_color_;
}

void Label::SetFontColor(const Color& font_color) {
  font_color_ = font_color;
}

::band::FontId Label::FontId() const {
  return font_id_;
}

void Label::SetFontId(::band::FontId font_id) {
  font_id_ = font_id;
}

::band::Area Label::Area(const Interface& interface) const {
  return interface.MeasureText(text_, this->FontSize(), this->FontId());
}

void Label::Draw(const Point& position, Interface& interface) {
  interface.DrawText(
      text_, position,
      this->FontSize(), this->FontColor(), this->FontId());
}

}  // namespace control
}  // namespace band
