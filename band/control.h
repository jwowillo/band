#pragma once

#include <initializer_list>
#include <memory>
#include <utility>

#include "band/interface.h"

namespace band {

// Control is an encapsulated feature that can be drawn on an interface.
class Control {
  public:
    virtual ~Control() = default;

    virtual Color BackgroundColor() const = 0;
    virtual void SetBackgroundColor(const Color& color) = 0;

    virtual Color ForegroundColor() const = 0;
    virtual void SetForegroundColor(const Color& color) = 0;

    virtual Color BorderColor() const = 0;
    virtual void SetBorderColor(const Color& color) = 0;

    virtual Dimension HorizontalBorderThickness() const = 0;
    virtual void SetHorizontalBorderThickness(const Dimension& dimension) = 0;

    virtual Dimension VerticalBorderThickness() const = 0;
    virtual void SetVerticalBorderThickness(const Dimension& dimension) = 0;

    virtual Dimension HorizontalPadding() const = 0;
    virtual void SetHorizontalPadding(const Dimension& dimension) = 0;

    virtual Dimension VerticalPadding() const = 0;
    virtual void SetVerticalPadding(const Dimension& dimension) = 0;

    virtual ::band::Area Area() const = 0;
    virtual void SetArea(const ::band::Area& area) = 0;

    virtual ::band::FontId FontId() const = 0;
    virtual void SetFontId(::band::FontId id) = 0;

    virtual Dimension FontSize() const = 0;
    virtual void SetFontSize(const Dimension& font_size) = 0;

    virtual void Disable() = 0;
    virtual void Enable() = 0;

    virtual bool IsEnabled() const = 0;

    virtual bool HasFocus() const = 0;
    virtual bool HasPress() const = 0;

    virtual void Display(const Point& point, Interface& interface) = 0;
    virtual void CleanUp(Interface& interface) = 0;

};

// BaseControl is a control with all methods implemented with default
// functionality to simplify control implementation for controls that don't need
// all the attributes.
class BaseControl : public Control {
  public:
    Color BackgroundColor() const override;
    void SetBackgroundColor(const Color& color) override;

    Color ForegroundColor() const override;
    void SetForegroundColor(const Color& color) override;

    Color BorderColor() const override;
    void SetBorderColor(const Color& color) override;

    Dimension HorizontalBorderThickness() const override;
    void SetHorizontalBorderThickness(const Dimension& dimension) override;

    Dimension VerticalBorderThickness() const override;
    void SetVerticalBorderThickness(const Dimension& dimension) override;

    Dimension HorizontalPadding() const override;
    void SetHorizontalPadding(const Dimension& dimension) override;

    Dimension VerticalPadding() const override;
    void SetVerticalPadding(const Dimension& dimension) override;

    ::band::Area Area() const override;
    void SetArea(const ::band::Area& area) override;

    ::band::FontId FontId() const override;
    void SetFontId(::band::FontId id) override;

    Dimension FontSize() const override;
    void SetFontSize(const Dimension& font_size) override;

    void Disable() override;
    void Enable() override;

    bool IsEnabled() const override;

    bool HasFocus() const override;
    bool HasPress() const override;

    void Display(const Point& point, Interface& interface) override;
    void CleanUp(Interface& interface) override;

};

// DrawControls wraps the displaying of controls with start and stop drawing
// calls.
void DrawControls(
    const std::initializer_list<std::pair<Control&, Point>>& pairs,
    Interface& interface);

}  // namespace band
