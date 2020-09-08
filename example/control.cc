#include <iostream>
#include <memory>

#include "band/all.h"
#include "band/asset/font/helvetica.font.h"
#include "example/icon.image.h"

using PointerStackPanel = band::control::StackPanel<band::Control*>;
using PointerAnchor = band::control::Anchor<band::Control*>;
using PointerButton = band::control::Button<band::Control*>;

class Control : public band::BaseControl {
  public:
    explicit Control(band::FontId id) {
      label_.SetText("control");
      label_.SetFontSize(
          band::Dimension{ .scalar = 0.1, .unit = band::Unit::kRatio });
      label_.SetFontColor(
          band::Color{ .r = 0x00, .g = 0x00, .b = 0x00, .a = 0xff });
      label_.SetFontId(id);

      separator_.SetArea(band::Area{
          .width = band::Dimension{
            .scalar = 0.5,
            .unit = band::Unit::kRatio
          },
          .height = band::Dimension{
            .scalar = 0.005,
            .unit = band::Unit::kRatio
          } });
      separator_.SetColor(
          band::Color{ .r = 0xff, .g = 0x00, .b = 0x00, .a = 0xff });

      padding_.SetArea(band::Area{
          .width = band::Dimension{
            .scalar = 0.5,
            .unit = band::Unit::kRatio
          },
          .height = band::Dimension{
            .scalar = 0.02,
            .unit = band::Unit::kRatio
          } });
      padding_.SetColor(
          band::Color{ .r = 0xff, .g = 0xff, .b = 0xff, .a = 0xff });

      button_control_.SetText("button");
      button_control_.SetFontSize(
          band::Dimension{ .scalar = 0.1, .unit = band::Unit::kRatio });
      button_control_.SetFontColor(
          band::Color{ .r = 0x00, .g = 0x00, .b = 0x00, .a = 0xff });
      button_control_.SetFontId(id);

      button_.SetFillColor(
          band::Color{ .r = 0xff, .g = 0xff, .b = 0xff, .a = 0xff });
      button_.SetHoverColor(
          band::Color{ .r = 0xcc, .g = 0xcc, .b = 0xcc, .a = 0xff });
      button_.SetHorizontalAlignment(band::Alignment::kMiddle);
      button_.SetVerticalAlignment(band::Alignment::kMiddle);
      button_.SetBorderColor(
          band::Color{ .r = 0xff, .g = 0x00, .b = 0x00, .a = 0xff  });
      button_.SetBorderThickness(band::Dimension{
            .scalar = 0.005,
            .unit = band::Unit::kRatio
          });
      button_.SetControl(&button_control_);

      stack_panel_.SetAlignment(band::Alignment::kMiddle);
      stack_panel_.SetDirection(band::Direction::kVertical);
      stack_panel_.SetControls({&label_, &padding_, &separator_, &padding_, &button_});

      anchor_.SetHorizontalAlignment(band::Alignment::kMiddle);
      anchor_.SetVerticalAlignment(band::Alignment::kMiddle);
      anchor_.SetReferenceArea(::band::Area{
          .width = band::Dimension{ .scalar = 1.0, .unit = band::Unit::kRatio },
          .height = band::Dimension{ .scalar = 1.0, .unit = band::Unit::kRatio } });
      anchor_.SetControl(&texture_);

    }

    band::Area Area(const band::Interface& interface) const override {
      return anchor_.Area(interface);
    }

    void CleanUp(band::Interface& interface) override {
      stack_panel_.CleanUp(interface);
      anchor_.CleanUp(interface);
    }

    void Update(const band::Point& point, band::Interface& interface) override {
      PointerAnchor anchor{};
      anchor.SetHorizontalAlignment(band::Alignment::kMiddle);
      anchor.SetVerticalAlignment(band::Alignment::kMiddle);
      anchor.SetReferenceArea(::band::Area{
          .width = band::Dimension{ .scalar = 1.0, .unit = band::Unit::kRatio },
          .height = band::Dimension{ .scalar = 1.0, .unit = band::Unit::kRatio } });
      anchor.SetControl(&stack_panel_);

      anchor.Update(point, interface);

      anchor_.Update(point, interface);

      PointerButton::Action current_action = button_.LastAction();
      if (current_action == PointerButton::Action::kPress) {
        std::cout << "button pressed" << std::endl;
      }

      if (first_frame_ ||
          last_area_ != interface.WindowArea() ||
          last_action_ != current_action) {
        first_frame_ = false;

        texture_.CaptureControl(interface, stack_panel_);
        last_area_ = interface.WindowArea();
        last_action_ = current_action;
      }
    }

    void Draw(const band::Point& point, band::Interface& interface) override {
      anchor_.Draw(point, interface);
    }

  private:
    bool first_frame_ = false;

    band::WindowArea last_area_{};
    PointerButton::Action last_action_{};

    band::control::Label label_{};
    band::control::Separator separator_{};
    band::control::Separator padding_{};
    band::control::Label button_control_{};
    PointerButton button_{};
    PointerStackPanel stack_panel_{};
    PointerAnchor anchor_{};
    band::control::Texture texture_{};

};

int main() {
  std::unique_ptr<band::Interface> created_interface = band::DefaultInterface();

  using Interface =
    band::interface::DebugInterfaceDecorator<std::unique_ptr<band::Interface>>;
  Interface interface{std::move(created_interface)};

  interface.SetTitle("control");
  interface.SetTargetFps(60u);
  interface.SetWindowArea(band::WindowArea{ .width = 1024.0, .height = 1024.0 });

  band::FontId font_id = interface.LoadFont(band::asset::font::Helvetica());
  band::ImageId icon_id = interface.LoadImage(Icon());
  interface.SetIcon(icon_id);

  band::Color background_color{ .r = 0xff, .g = 0xff, .b = 0xff, .a = 0xff };
  Control control{font_id};

  band::Run(background_color, interface, control);
}
