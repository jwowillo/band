#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>

#include "band/interface.h"

namespace band {
namespace interface {

// The 'raylib' include is purposely excluded from the header file to prevent it
// from being included in other translation-units.

// WindowInfo describes a window.
struct WindowInfo {
  WindowArea area;
  Text name;
  Size fps;
  ImageId icon;
};

// RaylibInterface uses raylib to implement an interface.
class RaylibInterface : public Interface {
  public:
    RaylibInterface();

    // ~RaylibInterface closes the interface and frees resources.
    ~RaylibInterface() override;

    // Delete due to non-trivial destructor.
    RaylibInterface(const RaylibInterface&) = delete;
    RaylibInterface& operator=(const RaylibInterface&) = delete;
    RaylibInterface(const RaylibInterface&&) = delete;
    RaylibInterface& operator=(const RaylibInterface&&) = delete;

    // Open if not already open.
    void Open(const WindowInfo& window_info);
    // Close if not already closed.
    void Close();

    void StartDrawing() override;
    void StopDrawing() override;

    ImageId LoadImage(const File&) override;
    void DeleteImage(ImageId id) override;
    void DeleteAllImages() override;

    FontId LoadFont(const File&) override;
    void DeleteFont(FontId id) override;
    void DeleteAllFonts() override;

    TextureId CreateBlankTexture(const Area& area) override;
    TextureId CreateImageTexture(ImageId id, const Area& area) override;
    void DeleteTexture(TextureId id) override;
    void DeleteAllTextures() override;
    void SelectTexture(TextureId id) override;
    void UnselectTexture() override;
    void DrawTexture(TextureId id, const Point& position) override;

    void Clear(const Color& color) override;
    void DrawLine(
        const Line& line, const Dimension& thickness,
        const Leg& leg, const Color& color) override;
    void DrawCircle(
        const Circle& circle, const Leg& leg, const Color& color) override;
    void DrawRectangle(const Rectangle& rectangle, const Color& color) override;
    void DrawTriangle(const Triangle& triangle, const Color& color) override;
    void DrawText(
        const Text& text, const Point& position,
        const Dimension& dimension, const Color& color,
        FontId id) override;
    void DrawFps(const Point& position) override;

    Area MeasureText(
        const Text& text, const Dimension& dimension,
        FontId id) const override;
    bool HasAction(const Action& action) const override;
    std::optional<char> CharacterPressed() const override;
    Point MousePosition() const override;
    ::band::WindowArea WindowArea() const override;

  private:
    struct ImageType;
    struct TextureType;
    struct FontType;

    WindowInfo window_info_;
    bool is_open_;

    std::unordered_map<ImageId, std::unique_ptr<ImageType>> images_;
    std::unordered_map<TextureId, std::unique_ptr<TextureType>> textures_;
    std::unordered_map<FontId, std::unique_ptr<FontType>> fonts_;
    ImageId next_image_id_;
    TextureId next_texture_id_;
    FontId next_font_id_;

    std::optional<uint32_t> key_pressed_;

};

}  // namespace interface
}  // namespace band
