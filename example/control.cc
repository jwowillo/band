#include <iostream>

#include "band/all.h"
#include "band/asset/font/helvetica.font.h"
#include "example/icon.image.h"

int main() {
  std::unique_ptr<band::Interface> created_interface = band::DefaultInterface();
  band::Interface& interface = *created_interface;

  interface.SetTitle("control");
  interface.SetTargetFps(60u);
  interface.SetWindowArea(band::WindowArea{ .width = 1024.0, .height = 1024.0 });

  band::FontId font_id = interface.LoadFont(band::asset::font::Helvetica());
  band::ImageId icon_id = interface.LoadImage(Icon());
  interface.SetIcon(icon_id);

  band::control::Label label{};
  label.SetText("control");
  label.SetFontSize(
      band::Dimension{ .scalar = 0.1, .unit = band::Unit::kRatio });
  label.SetFontColor(
      band::Color{ .r = 0x00, .g = 0x00, .b = 0x00, .a = 0xff });
  label.SetFontId(font_id);

  band::control::Separator separator{};
  separator.SetArea(band::Area{
      .width = band::Dimension{
        .scalar = 0.5,
        .unit = band::Unit::kRatio
      },
      .height = band::Dimension{
        .scalar = 0.005,
        .unit = band::Unit::kRatio
      } });
  separator.SetColor(
      band::Color{ .r = 0xff, .g = 0x00, .b = 0x00, .a = 0xff });

  band::control::Separator padding{};
  padding.SetArea(band::Area{
      .width = band::Dimension{
        .scalar = 0.5,
        .unit = band::Unit::kRatio
      },
      .height = band::Dimension{
        .scalar = 0.02,
        .unit = band::Unit::kRatio
      } });
  padding.SetColor(
      band::Color{ .r = 0xff, .g = 0xff, .b = 0xff, .a = 0xff });

  band::control::Label button_control{};
  button_control.SetText("button");
  button_control.SetFontSize(
      band::Dimension{ .scalar = 0.1, .unit = band::Unit::kRatio });
  button_control.SetFontColor(
      band::Color{ .r = 0x00, .g = 0x00, .b = 0x00, .a = 0xff });
  button_control.SetFontId(font_id);

  using PointerStackPanel = band::control::StackPanel<band::Control*>;
  using PointerFixedPanel = band::control::FixedPanel<band::Control*>;
  using PointerAnchor = band::control::Anchor<band::Control*>;
  using PointerButton = band::control::Button<band::Control*>;

  PointerButton button{};
  button.SetFillColor(
      band::Color{ .r = 0xff, .g = 0xff, .b = 0xff, .a = 0xff });
  button.SetHoverColor(
      band::Color{ .r = 0xcc, .g = 0xcc, .b = 0xcc, .a = 0xff });
  button.SetHorizontalAlignment(band::Alignment::kMiddle);
  button.SetVerticalAlignment(band::Alignment::kMiddle);
  button.SetBorderColor(
      band::Color{ .r = 0xff, .g = 0x00, .b = 0x00, .a = 0xff  });
  button.SetBorderThickness(band::Dimension{
        .scalar = 0.005,
        .unit = band::Unit::kRatio
      });
  button.SetControl(&button_control);

  PointerStackPanel stack_panel{};
  stack_panel.SetAlignment(band::Alignment::kMiddle);
  stack_panel.SetDirection(band::Direction::kVertical);
  stack_panel.SetControls({&label, &padding, &separator, &padding, &button});

  band::control::Texture texture{};
  band::Scope scope{[&texture, &interface]() { texture.CleanUp(interface); }};

  PointerAnchor update_anchor{};
  update_anchor.SetHorizontalAlignment(band::Alignment::kMiddle);
  update_anchor.SetVerticalAlignment(band::Alignment::kMiddle);
  update_anchor.SetReferenceArea(::band::Area{
      .width = band::Dimension{ .scalar = 1.0, .unit = band::Unit::kRatio },
      .height = band::Dimension{ .scalar = 1.0, .unit = band::Unit::kRatio } });
  update_anchor.SetControl(&stack_panel);

  PointerAnchor anchor{};
  anchor.SetHorizontalAlignment(band::Alignment::kMiddle);
  anchor.SetVerticalAlignment(band::Alignment::kMiddle);
  anchor.SetReferenceArea(::band::Area{
      .width = band::Dimension{ .scalar = 1.0, .unit = band::Unit::kRatio },
      .height = band::Dimension{ .scalar = 1.0, .unit = band::Unit::kRatio } });
  anchor.SetControl(&texture);

  band::control::Fps fps{};

  PointerFixedPanel fixed_panel{};
  fixed_panel.SetControls({ {&fps, band::Point{}}, {&anchor, band::Point{}} });

  bool first_frame = true;
  band::WindowArea last_window_area{};
  PointerButton::Action last_action{};

  while (!interface.HasAction(band::Interface::Action::kClose)) {
    band::Update(band::Point{}, interface, update_anchor);

    PointerButton::Action current_action = button.LastAction();
    if (current_action == PointerButton::Action::kPress) {
      std::cout << "button pressed" << std::endl;
    }

    if (first_frame ||
        last_window_area != interface.WindowArea() ||
        current_action != last_action) {
      first_frame = false;

      texture.CaptureControl(interface, stack_panel);
      last_window_area = interface.WindowArea();
      last_action = current_action;
    }

    band::DrawFrame(
        band::Color{ .r = 0xff, .g = 0xff, .b = 0xff, .a = 0xff },
        band::Point{}, interface, fixed_panel);
  }
}
