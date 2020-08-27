#include "band/all.h"
#include "band/asset/font/helvetica.font.h"
#include "example/icon.image.h"

int main() {
  std::unique_ptr<band::Interface> created_interface = band::DefaultInterface();
  band::Interface& interface = *created_interface;

  interface.SetTitle("simple");
  interface.SetTargetFps(60u);
  interface.SetWindowArea(band::WindowArea{ .width = 1024.0, .height = 1024.0 });

  band::Dimension text_size{ .scalar = 0.05, .unit = band::Unit::kRatio };
  band::Dimension middle{ .scalar = 0.5, .unit = band::Unit::kRatio };

  band::FontId font_id = interface.LoadFont(band::asset::font::Helvetica());
  band::ImageId icon_id = interface.LoadImage(Icon());

  interface.SetIcon(icon_id);

  while (!interface.HasAction(band::Interface::Action::kClose)) {
    interface.StartDrawing();

    interface.Clear(band::Color{ .r = 0xff, .g = 0xff, .b = 0xff, .a = 0xff });

    band::Area text_area = interface.MeasureText("simple", text_size, font_id);
    interface.DrawText(
        "simple",
        band::Point{
          .x = band::SubtractDimensions(
              middle, band::MultiplyDimension(
                text_area.width, 0.5), interface.WindowArea().width),
          .y = band::SubtractDimensions(
              middle, band::MultiplyDimension(
                text_area.height, 0.5), interface.WindowArea().height) },
        text_size,
        band::Color{ .r = 0x00, .g = 0x00, .b = 0x00, .a = 0xff },
        font_id);

    interface.DrawTriangle(band::Triangle{
        .a = band::Point{
          .x = band::Dimension{ .scalar = 0.4, .unit = band::Unit::kRatio },
          .y = band::Dimension{ .scalar = 0.1, . unit = band::Unit::kRatio }
        },
        .b = band::Point{
          .x = band::Dimension{ .scalar = 0.3, .unit = band::Unit::kRatio },
          .y = band::Dimension{ .scalar = 0.1, . unit = band::Unit::kRatio }
        },
        .c = band::Point{
          .x = band::Dimension{ .scalar = 0.4, .unit = band::Unit::kRatio },
          .y = band::Dimension{ .scalar = 0.2, . unit = band::Unit::kRatio }
        } },
        band::Color{ .r = 0xff, .g = 0x00, .b = 0x00, .a = 0xff });

    interface.DrawLine(band::Line{
        .a = band::Point{
          .x = band::Dimension{ .scalar = 0.8, .unit = band::Unit::kRatio },
          .y = band::Dimension{ .scalar = 0.6, . unit = band::Unit::kRatio }
        },
        .b = band::Point{
          .x = band::Dimension{ .scalar = 0.6, .unit = band::Unit::kRatio },
          .y = band::Dimension{ .scalar = 0.8, . unit = band::Unit::kRatio }
        } },
        band::Dimension{ .scalar = 0.01, .unit = band::Unit::kRatio },
        band::Leg::kHeight,
        band::Color{ .r = 0x00, .g = 0xff, .b = 0x00, .a = 0xff });

    interface.DrawFps(band::Point{
        .x = band::Dimension{ .scalar = 0.0, .unit = band::Unit::kRatio },
        .y = band::Dimension{ .scalar = 0.0, .unit = band::Unit::kRatio } });

    band::TextureId texture_id = interface.CreateBlankTexture(band::Area{
        .width = band::Dimension{ .scalar = 0.2, .unit = band::Unit::kRatio },
        .height = band::Dimension{ .scalar = 0.15, .unit = band::Unit::kRatio } });
    interface.SelectTexture(texture_id);
    interface.DrawTriangle(band::Triangle{
        .a = band::Point{
          .x = band::Dimension{ .scalar = 0.0, .unit = band::Unit::kRatio },
          .y = band::Dimension{ .scalar = 1.0, . unit = band::Unit::kRatio }
        },
        .b = band::Point{
          .x = band::Dimension{ .scalar = 1.0, .unit = band::Unit::kRatio },
          .y = band::Dimension{ .scalar = 1.0, . unit = band::Unit::kRatio }
        },
        .c = band::Point{
          .x = band::Dimension{ .scalar = 0.5, .unit = band::Unit::kRatio },
          .y = band::Dimension{ .scalar = 0.0, . unit = band::Unit::kRatio }
        } },
        band::Color{ .r = 0x00, .g = 0x00, .b = 0xff, .a = 0xff });
    interface.UnselectTexture();
    interface.DrawTexture(texture_id, band::Point{
        .x = band::Dimension{ .scalar = 0.1, .unit = band::Unit::kRatio },
        .y = band::Dimension{ .scalar = 0.6, .unit = band::Unit::kRatio } });

    interface.StopDrawing();

    interface.DeleteTexture(texture_id);
  }
}
