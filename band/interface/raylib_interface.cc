#include "band/interface/raylib_interface.h"

#include <cmath>

#include "raylib.h"

#include <iostream>

#define STBI_IMAGE_IMPLEMENTATION
#include "external/stb_image.h"

#define STBTT_STATIC
#define STB_TRUETYPE_IMPLEMENTATION
#include "external/stb_truetype.h"

namespace band {
namespace interface {

namespace {

Real ConvertDimensionToPixel(const Dimension& dimension, Real pixels) {
  return dimension.unit == Unit::kPixel ?
    dimension.scalar : dimension.scalar * pixels;
}

::Image LoadImageFromFile(const File& file) {
  // Stolen directly from raylib's image handling since they don't provide a way
  // to load an image with bytes.

  ::Image image{};

  int comp = 0;

  image.data = stbi_load_from_memory(
      file.bytes, file.n, &image.width, &image.height, &comp, 0);
  image.mipmaps = 1;
  if (comp == 1) {
    image.format = UNCOMPRESSED_GRAYSCALE;
  } else if (comp == 2) {
    image.format = UNCOMPRESSED_GRAY_ALPHA;
  } else if (comp == 3) {
    image.format = UNCOMPRESSED_R8G8B8;
  } else if (comp == 4) {
    image.format = UNCOMPRESSED_R8G8B8A8;
  }

  return image;
}

::Font LoadFontFromFile(const File& file) {
  // Stolen directly from raylib's font handling since they don't provide a way
  // to load a font with bytes.

  ::CharInfo* chars = nullptr;
  float font_size = 128.0;
  int char_count = 95;

  {
    stbtt_fontinfo font_info{};
    if (stbtt_InitFont(
          &font_info,
          reinterpret_cast<const unsigned char*>(file.bytes), 0)) {
      float scale_factor = stbtt_ScaleForPixelHeight(&font_info, font_size);

      int ascent = 0;
      int descent = 0;
      int line_gap = 0;
      stbtt_GetFontVMetrics(&font_info, &ascent, &descent, &line_gap);

      int* font_chars = reinterpret_cast<int*>(RL_MALLOC(char_count*sizeof(int)));
      for (int i = 0; i < char_count; i++) {
        font_chars[i] = i + 32;
      }

      chars = reinterpret_cast<CharInfo*>(RL_MALLOC(char_count*sizeof(::CharInfo)));
      for (int i = 0; i < char_count; i++) {
        int chw = 0;
        int chh = 0;
        int ch = font_chars[i];
        chars[i].value = ch;
        chars[i].image.data = stbtt_GetCodepointBitmap(
            &font_info, scale_factor, scale_factor,
            ch, &chw, &chh, &chars[i].offsetX, &chars[i].offsetY);
        stbtt_GetCodepointHMetrics(&font_info, ch, &chars[i].advanceX, nullptr);
        chars[i].advanceX = static_cast<int>(static_cast<float>(
              chars[i].advanceX*scale_factor));
        chars[i].image.width = chw;
        chars[i].image.height = chh;
        chars[i].image.mipmaps = 1;
        chars[i].image.format = UNCOMPRESSED_GRAYSCALE;
        chars[i].offsetY += static_cast<int>(static_cast<float>(ascent*scale_factor));
        if (ch == 32) {
          ::Image image{};
          image.data = calloc(chars[i].advanceX*font_size, 2);
          image.width = chars[i].advanceX;
          image.height = static_cast<int>(std::round(font_size));
          image.format = UNCOMPRESSED_GRAYSCALE;
          image.mipmaps = 1;

          chars[i].image = image;
        }
      }

      RL_FREE(font_chars);
    }
  }

  ::Font font{};
  font.baseSize = font_size;
  font.charsCount = char_count;
  font.chars = chars;

  ::Image atlas = ::GenImageFontAtlas(
      font.chars, &font.recs, font.charsCount, font.baseSize, 2, 0);
  font.texture = ::LoadTextureFromImage(atlas);
  for (int i = 0; i < font.charsCount; i++) {
    ::UnloadImage(font.chars[i].image);
    font.chars[i].image = ::ImageFromImage(atlas, font.recs[i]);
  }

  ::UnloadImage(atlas);

  return font;
}

}  // namespace

struct RaylibInterface::ImageType {
  ::Image image;
};

struct RaylibInterface::TextureType {
  ::RenderTexture2D target;
};

struct RaylibInterface::FontType {
  ::Font font;
};

RaylibInterface::RaylibInterface() :
  is_open_{false},
  images_{}, textures_{}, fonts_{},
  next_image_id_{}, next_texture_id_{}, next_font_id_{},
  key_pressed_{}, selected_texture_{} { }

RaylibInterface::~RaylibInterface() {
  Close();
}

void RaylibInterface::Open() {
  ::SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  // Need to set this to have at-least one value so the window isn't
  // auto-fullscreened.
  ::InitWindow(1024, 1024, "");

  is_open_ = true;
}

void RaylibInterface::Close() {
  if (!is_open_) {
    return;
  }

  // Deleting resources on exit causes segfaults.

  ::CloseWindow();

  is_open_ = false;
}

void RaylibInterface::SetTargetFps(Size fps) {
  ::SetTargetFPS(fps);
}

void RaylibInterface::SetWindowArea(const ::band::WindowArea& area) {
  ::SetWindowSize(
      static_cast<int>(std::round(area.width)),
      static_cast<int>(std::round(area.height)));
}

void RaylibInterface::SetIcon(ImageId id) {
  if (images_.find(id) == images_.end()) {
    return;
  }

  ::SetWindowIcon(images_.at(id)->image);
}

void RaylibInterface::SetTitle(const Text& text) {
  ::SetWindowTitle(text.c_str());
}

void RaylibInterface::ToggleFullscreen() {
  ::ToggleFullscreen();
}

ImageId RaylibInterface::LoadImage(const File& file) {
  ImageId id = next_image_id_;
  next_image_id_++;

  ::Image image = LoadImageFromFile(file);

  std::unique_ptr<ImageType> image_type = std::make_unique<ImageType>();
  image_type->image = image;
  images_[id] = std::move(image_type);

  return id;
}

FontId RaylibInterface::LoadFont(const File& file) {
  FontId id = next_font_id_;
  next_font_id_++;

  ::Font font = LoadFontFromFile(file);

  std::unique_ptr<FontType> font_type = std::make_unique<FontType>();
  font_type->font = font;
  fonts_[id] = std::move(font_type);

  return id;
}

void RaylibInterface::StartDrawing() {
  key_pressed_ = static_cast<char>(::GetKeyPressed());
  ::BeginDrawing();
}

void RaylibInterface::StopDrawing() {
  ::EndDrawing();
}

void RaylibInterface::DeleteImage(ImageId id) {
  if (images_.find(id) == images_.end()) {
    return;
  }

  ::UnloadImage(images_.at(id)->image);
  images_.erase(id);
}

void RaylibInterface::DeleteAllImages() {
  for (const auto& pair : images_) {
    DeleteImage(pair.first);
  }
}

void RaylibInterface::DeleteFont(FontId id) {
  if (fonts_.find(id) == fonts_.end()) {
    return;
  }

  ::UnloadFont(fonts_.at(id)->font);
  fonts_.erase(id);
}

void RaylibInterface::DeleteAllFonts() {
  for (const auto& pair : fonts_) {
    DeleteFont(pair.first);
  }
}

TextureId RaylibInterface::CreateBlankTexture(const Area& area) {
  ::band::WindowArea draw_area = DrawArea();

  Real width = ConvertDimensionToPixel(area.width, draw_area.width);
  Real height = ConvertDimensionToPixel(area.height, draw_area.height);

  ::RenderTexture2D texture_target = ::LoadRenderTexture(
      std::round(width), std::round(height));

  std::unique_ptr<TextureType> texture_type = std::make_unique<TextureType>();
  texture_type->target = texture_target;
  textures_[texture_target.texture.id] = std::move(texture_type);

  return texture_target.texture.id;
}

TextureId RaylibInterface::CreateImageTexture(ImageId id, const Area& area) {
  if (images_.find(id) == images_.end()) {
    return 0u;
  }

  ::band::WindowArea draw_area = DrawArea();
  Real width = ConvertDimensionToPixel(area.width, draw_area.width);
  Real height = ConvertDimensionToPixel(area.height, draw_area.height);

  ::Image copy = ::ImageCopy(images_.at(id)->image);
  ::ImageResize(&copy, std::round(width), std::round(height));

  ::Texture2D texture = ::LoadTextureFromImage(copy);

  TextureId texture_id = CreateBlankTexture(area);
  SelectTexture(texture_id);

  ::DrawTextureRec(
      texture,
      ::Rectangle{
        .x = 0.0f, .y = 0.0f,
        .width = static_cast<float>(width),
        .height = static_cast<float>(height)
      },
      ::Vector2{ .x = 0.0f, .y = 0.0f },
      ::Color{ .r = 0xff, .g = 0xff, .b = 0xff, .a = 0xff });

  UnselectTexture();
  ::UnloadImage(copy);
  ::UnloadTexture(texture);

  return texture_id;
}

void RaylibInterface::DeleteTexture(TextureId id) {
  if (textures_.find(id) == textures_.end()) {
    return;
  }

  ::UnloadRenderTexture(textures_.at(id)->target);
  textures_.erase(id);
}

void RaylibInterface::DeleteAllTextures() {
  for (const auto& pair : textures_) {
    DeleteTexture(pair.first);
  }
}

void RaylibInterface::SelectTexture(TextureId id) {
  if (selected_texture_.has_value() ||
      textures_.find(id) == textures_.end()) {
    return;
  }

  ::BeginTextureMode(textures_.at(id)->target);
  selected_texture_ = id;
}

void RaylibInterface::UnselectTexture() {
  if (!selected_texture_.has_value()) {
    return;
  }

  ::EndTextureMode();
  selected_texture_ = std::nullopt;
}

void RaylibInterface::DrawTexture(TextureId id, const Point& position) {
  if (textures_.find(id) == textures_.end()) {
    return;
  }

  ::band::WindowArea draw_area = DrawArea();

  Real x = ConvertDimensionToPixel(position.x, draw_area.width);
  Real y = ConvertDimensionToPixel(position.y, draw_area.height);

  DrawTextureRec(
      textures_.at(id)->target.texture,
      ::Rectangle{
        .x = 0.0f, .y = 0.0f,
        .width = static_cast<float>(textures_.at(id)->target.texture.width),
        .height = -static_cast<float>(textures_.at(id)->target.texture.height)
      },
      ::Vector2{ .x = static_cast<float>(x), .y = static_cast<float>(y) },
      ::Color{ .r = 0xff, .g = 0xff, .b = 0xff, .a = 0xff });
}

void RaylibInterface::Clear(const Color& color) {
  ::ClearBackground(
      ::Color{ .r = color.r, .g = color.g, .b = color.b, .a = color.a });
}

void RaylibInterface::DrawLine(
    const Line& line, const Dimension& thickness,
    const Leg& leg, const Color& color) {
  ::band::WindowArea draw_area = DrawArea();

  Real ax = ConvertDimensionToPixel(line.a.x, draw_area.width);
  Real ay = ConvertDimensionToPixel(line.a.y, draw_area.height);

  Real bx = ConvertDimensionToPixel(line.b.x, draw_area.width);
  Real by = ConvertDimensionToPixel(line.b.y, draw_area.height);

  Real real_thickness = leg == Leg::kWidth ?
    ConvertDimensionToPixel(thickness, draw_area.width) :
    ConvertDimensionToPixel(thickness, draw_area.height);

  DrawLineEx(
      ::Vector2{
        .x = static_cast<float>(ax),
        .y = static_cast<float>(ay)
      },
      ::Vector2{
        .x = static_cast<float>(bx),
        .y = static_cast<float>(by)
      },
      static_cast<float>(real_thickness),
      ::Color{ .r = color.r, .g = color.g, .b = color.b, .a = color.a });
}

void RaylibInterface::DrawCircle(
    const Circle& circle, const Leg& leg, const Color& color) {
  ::band::WindowArea draw_area = DrawArea();

  Real x = ConvertDimensionToPixel(circle.center.x, draw_area.width);
  Real y = ConvertDimensionToPixel(circle.center.y, draw_area.height);

  Real radius = leg == Leg::kWidth ?
    ConvertDimensionToPixel(circle.radius, draw_area.width) :
    ConvertDimensionToPixel(circle.radius, draw_area.height);

  ::DrawCircleV(
      ::Vector2{
        .x = static_cast<float>(x),
        .y = static_cast<float>(y)
      },
      static_cast<float>(radius),
      ::Color{ .r = color.r, .g = color.g, .b = color.b, .a = color.a });
}

void RaylibInterface::DrawRectangle(
    const Rectangle& rectangle, const Color& color) {
  ::band::WindowArea draw_area = DrawArea();

  Real ax = ConvertDimensionToPixel(rectangle.bottom_left.x, draw_area.width);
  Real ay = ConvertDimensionToPixel(rectangle.bottom_left.y, draw_area.height);
  Real bx = ConvertDimensionToPixel(rectangle.top_right.x, draw_area.width);
  Real by = ConvertDimensionToPixel(rectangle.top_right.y, draw_area.height);

  ::DrawRectangleV(
      ::Vector2{
        .x = static_cast<float>(ax),
        .y = static_cast<float>(ay)
      },
      ::Vector2{
        .x = static_cast<float>(bx - ax),
        .y = static_cast<float>(by - ay)
      },
      ::Color{ .r = color.r, .g = color.g, .b = color.b, .a = color.a });
}

void RaylibInterface::DrawTriangle(
    const Triangle& triangle, const Color& color) {
  ::band::WindowArea draw_area = DrawArea();

  Real ax = ConvertDimensionToPixel(triangle.a.x, draw_area.width);
  Real ay = ConvertDimensionToPixel(triangle.a.y, draw_area.height);
  Real bx = ConvertDimensionToPixel(triangle.b.x, draw_area.width);
  Real by = ConvertDimensionToPixel(triangle.b.y, draw_area.height);
  Real cx = ConvertDimensionToPixel(triangle.c.x, draw_area.width);
  Real cy = ConvertDimensionToPixel(triangle.c.y, draw_area.height);

  ::DrawTriangle(
      ::Vector2{ .x = static_cast<float>(ax), .y = static_cast<float>(ay) },
      ::Vector2{ .x = static_cast<float>(bx), .y = static_cast<float>(by) },
      ::Vector2{ .x = static_cast<float>(cx), .y = static_cast<float>(cy) },
      ::Color{ .r = color.r, .g = color.g, .b = color.b, .a = color.a });
}

void RaylibInterface::DrawText(
    const Text& text, const Point& position,
    const Dimension& dimension, const Color& color,
    FontId id) {
  if (fonts_.find(id) == fonts_.end()) {
    return;
  }

  ::Font font = fonts_.at(id)->font;

  ::band::WindowArea draw_area = DrawArea();

  Real x = ConvertDimensionToPixel(position.x, draw_area.width);
  Real y = ConvertDimensionToPixel(position.y, draw_area.height);
  Size size = static_cast<Size>(ConvertDimensionToPixel(dimension, draw_area.height));

  float spacing = size / 10.0;
  ::Vector2 p{ .x = static_cast<float>(x), .y = static_cast<float>(y) };

  ::DrawTextEx(
      font, text.c_str(),
      p, size, spacing,
      ::Color{ .r = color.r, .g = color.g, .b = color.b, .a = color.a });
}

void RaylibInterface::DrawFps(const Point& position) {
  ::band::WindowArea draw_area = DrawArea();

  Real x = ConvertDimensionToPixel(position.x, draw_area.width);
  Real y = ConvertDimensionToPixel(position.y, draw_area.height);

  ::DrawFPS(std::round(x), std::round(y));
}

Area RaylibInterface::MeasureText(
    const Text& text, const Dimension& dimension,
    FontId id) const {
  if (fonts_.find(id) == fonts_.end()) {
    return Area{};
  }

  ::Font font = fonts_.at(id)->font;

  ::band::WindowArea draw_area = DrawArea();

  float size = static_cast<float>(ConvertDimensionToPixel(dimension, draw_area.height));

  float spacing = size / 10.0;

  ::Vector2 measured = ::MeasureTextEx(font, text.c_str(), size, spacing);
  Size lines = 1u;

  for (char c : text) {
    if (c != '\n') {
      continue;
    }

    lines++;
  }

  return Area{
    .width = Dimension{
      .scalar = static_cast<Real>(measured.x),
      .unit = Unit::kPixel
    },
    .height = Dimension{
      .scalar = static_cast<Real>(lines*size),
      .unit = Unit::kPixel
    }
  };
}

bool RaylibInterface::HasAction(const Action& action) const {
  switch (action) {
  case Action::kLeftClick:
    return ::IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
  case Action::kRightClick:
    return !::IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
      ::IsMouseButtonPressed(MOUSE_RIGHT_BUTTON);
  case Action::kBackspace:
    return ::IsKeyDown(KEY_BACKSPACE);
  case Action::kClose:
    return !is_open_ || ::WindowShouldClose();
  default:
    return false;
  }
}

std::optional<char> RaylibInterface::CharacterPressed() const {
  if (!key_pressed_.has_value()) {
    return std::nullopt;
  }

  char key = key_pressed_.value();

  if (key < ' ' || key > '~') {
    return std::nullopt;
  }

  return key;
}

Point RaylibInterface::MousePosition() const {
  return Point{
    .x = Dimension{
      .scalar = static_cast<Real>(::GetMouseX()),
      .unit = Unit::kPixel
    },
    .y = Dimension{
      .scalar = static_cast<Real>(::GetMouseY()),
      .unit = Unit::kPixel
    }
  };
}

::band::WindowArea RaylibInterface::WindowArea() const {
  return ::band::WindowArea{
    .width = static_cast<Real>(::GetScreenWidth()),
    .height = static_cast<Real>(::GetScreenHeight())
  };
}

::band::WindowArea RaylibInterface::DrawArea() const {
  return ::band::WindowArea{
    .width = static_cast<Real>(::GetScreenWidth()),
    .height = static_cast<Real>(::GetScreenHeight())
  };
}

}  // namespace interface
}  // namespace band
