#include "band/all.h"
#include "band/asset/font/helvetica.font.h"
#include "example/icon.image.h"

int main() {
  std::unique_ptr<band::Interface> interface = band::DefaultInterface();

  interface->SetTitle("simple");
  interface->SetTargetFps(60u);
  interface->SetWindowArea(band::WindowArea{ .width = 1024.0, .height = 1024.0 });

  band::Dimension text_size{ .scalar = 0.05, .unit = band::Unit::kRatio };
  band::Dimension middle{ .scalar = 0.5, .unit = band::Unit::kRatio };

  band::FontId font_id = interface->LoadFont(band::asset::font::Helvetica());
  band::ImageId icon_id = interface->LoadImage(Icon());

  interface->SetIcon(icon_id);

  while (!interface->HasAction(band::Action::kClose)) {
    interface->StartDrawing();

    interface->Clear(band::Color{ .r = 0xff, .g = 0xff, .b = 0xff, .a = 0xff });

    band::Area text_area = interface->MeasureText("simple", text_size, font_id);
    interface->DrawText(
        "simple",
        band::Point{
          .x = band::SubtractDimensions(
              middle, band::MultiplyDimensions(
                text_area.width, 0.5), interface->WindowArea().width),
          .y = band::SubtractDimensions(
              middle, band::MultiplyDimensions(
                text_area.height, 0.5), interface->WindowArea().height) },
        text_size,
        band::Color{ .r = 0x00, .g = 0x00, .b = 0x00, .a = 0xff },
        font_id);
    interface->DrawFps(band::Point{
        .x = band::Dimension{ .scalar = 0.0, .unit = band::Unit::kRatio },
        .y = band::Dimension{ .scalar = 0.0, .unit = band::Unit::kRatio } });

    interface->StopDrawing();
  }
}
