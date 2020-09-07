#pragma once

#include <optional>

#include "band/interface.h"

namespace band {
namespace interface {

// BaseInterfaceDecorator is a helper to implement interface-decorators.
//
// The reference to the decorated interface is stored in a protected variable.
// Every method is forwarded to the interface by default unless overridden.
template <typename T>
class BaseInterfaceDecorator : public Interface {
  public:
    explicit BaseInterfaceDecorator(T interface);

    void SetTargetFps(Size fps) override;
    void SetWindowArea(const ::band::WindowArea& area) override;
    void SetIcon(ImageId id) override;
    void SetTitle(const Text& text) override;
    void ToggleFullscreen() override;
    void StartDrawing() override;
    void StopDrawing() override;
    ImageId LoadImage(const File& file) override;
    void DeleteImage(ImageId id) override;
    void DeleteAllImages() override;
    Area ImageArea(ImageId id) const override;
    FontId LoadFont(const File& file) override;
    void DeleteFont(FontId id) override;
    void DeleteAllFonts() override;
    TextureId CreateBlankTexture(const Area& area) override;
    TextureId CreateImageTexture(ImageId id, const Area& area) override;
    void DeleteTexture(TextureId id) override;
    void DeleteAllTextures() override;
    void SelectTexture(TextureId id) override;
    void UnselectTexture() override;
    void DrawTexture(TextureId id, const Point& position) override;
    Area TextureArea(TextureId id) const override;
    void Clear(const Color& color) override;
    void DrawLine(
        const Line& line, const Dimension& thickness,
        const Leg& leg, const Color& color) override;
    void DrawCircle(
        const Circle& circle, const Leg& leg,
        const Color& color) override;
    void DrawRectangle(
        const Rectangle& rectangle, const Color& color) override;
    void DrawTriangle(
        const Triangle& triangle, const Color& color) override;
    void DrawText(
        const Text& text, const Point& position,
        const Dimension& dimension, const Color& color,
        FontId id) override;
    void DrawFps(const Point& position) override;
    band::Area MeasureText(
        const Text& text, const Dimension& dimension,
        FontId id) const override;
    bool HasAction(const Action& action) const override;
    std::optional<char> CharacterPressed() const override;
    Point MousePosition() const override;
    ::band::WindowArea WindowArea() const override;

  protected:
    T interface_;

};

}  // namespace interface
}  // namespace band

namespace band {
namespace interface {

template <typename T>
BaseInterfaceDecorator<T>::BaseInterfaceDecorator(T interface) :
  interface_{std::forward<T>(interface)} { }

template <typename T>
void BaseInterfaceDecorator<T>::SetTargetFps(Size fps) {
  interface_->SetTargetFps(fps);
}

template <typename T>
void BaseInterfaceDecorator<T>::SetWindowArea(const ::band::WindowArea& area) {
  interface_->SetWindowArea(area);
}

template <typename T>
void BaseInterfaceDecorator<T>::SetIcon(ImageId id) {
  interface_->SetIcon(id);
}

template <typename T>
void BaseInterfaceDecorator<T>::SetTitle(const Text& text) {
  interface_->SetTitle(text);
}

template <typename T>
void BaseInterfaceDecorator<T>::ToggleFullscreen() {
  interface_->ToggleFullscreen();
}

template <typename T>
void BaseInterfaceDecorator<T>::StartDrawing() {
  interface_->StartDrawing();
}

template <typename T>
void BaseInterfaceDecorator<T>::StopDrawing() {
  interface_->StopDrawing();
}

template <typename T>
ImageId BaseInterfaceDecorator<T>::LoadImage(const File& file) {
  return interface_->LoadImage(file);
}

template <typename T>
void BaseInterfaceDecorator<T>::DeleteImage(ImageId id) {
  interface_->DeleteImage(id);
}

template <typename T>
void BaseInterfaceDecorator<T>::DeleteAllImages() {
  interface_->DeleteAllImages();
}

template <typename T>
Area BaseInterfaceDecorator<T>::ImageArea(ImageId id) const {
  return interface_->ImageArea(id);
}

template <typename T>
FontId BaseInterfaceDecorator<T>::LoadFont(const File& file) {
  return interface_->LoadFont(file);
}

template <typename T>
void BaseInterfaceDecorator<T>::DeleteFont(FontId id) {
  interface_->DeleteFont(id);
}

template <typename T>
void BaseInterfaceDecorator<T>::DeleteAllFonts() {
  interface_->DeleteAllFonts();
}

template <typename T>
TextureId BaseInterfaceDecorator<T>::CreateBlankTexture(const Area& area) {
  return interface_->CreateBlankTexture(area);
}

template <typename T>
TextureId BaseInterfaceDecorator<T>::CreateImageTexture(
    ImageId id, const Area& area) {
  return interface_->CreateImageTexture(id, area);
}

template <typename T>
void BaseInterfaceDecorator<T>::DeleteTexture(TextureId id) {
  interface_->DeleteTexture(id);
}

template <typename T>
void BaseInterfaceDecorator<T>::DeleteAllTextures() {
  interface_->DeleteAllTextures();
}

template <typename T>
void BaseInterfaceDecorator<T>::SelectTexture(TextureId id) {
  interface_->SelectTexture(id);
}

template <typename T>
void BaseInterfaceDecorator<T>::UnselectTexture() {
  interface_->UnselectTexture();
}

template <typename T>
void BaseInterfaceDecorator<T>::DrawTexture(
    TextureId id, const Point& position) {
  interface_->DrawTexture(id, position);
}

template <typename T>
Area BaseInterfaceDecorator<T>::TextureArea(TextureId id) const {
  return interface_->TextureArea(id);
}

template <typename T>
void BaseInterfaceDecorator<T>::Clear(const Color& color) {
  interface_->Clear(color);
}

template <typename T>
void BaseInterfaceDecorator<T>::DrawLine(
    const Line& line, const Dimension& thickness,
    const Leg& leg, const Color& color) {
  interface_->DrawLine(line, thickness, leg, color);
}

template <typename T>
void BaseInterfaceDecorator<T>::DrawCircle(
    const Circle& circle, const Leg& leg,
    const Color& color) {
  interface_->DrawCircle(circle, leg, color);
}

template <typename T>
void BaseInterfaceDecorator<T>::DrawRectangle(
    const Rectangle& rectangle, const Color& color) {
  interface_->DrawRectangle(rectangle, color);
}

template <typename T>
void BaseInterfaceDecorator<T>::DrawTriangle(
    const Triangle& triangle, const Color& color) {
  interface_->DrawTriangle(triangle, color);
}

template <typename T>
void BaseInterfaceDecorator<T>::DrawText(
    const Text& text, const Point& position,
    const Dimension& dimension, const Color& color,
    FontId id) {
  interface_->DrawText(text, position, dimension, color, id);
}

template <typename T>
void BaseInterfaceDecorator<T>::DrawFps(const Point& position) {
  interface_->DrawFps(position);
}

template <typename T>
band::Area BaseInterfaceDecorator<T>::MeasureText(
    const Text& text, const Dimension& dimension,
    FontId id) const {
  return interface_->MeasureText(text, dimension, id);
}

template <typename T>
bool BaseInterfaceDecorator<T>::HasAction(const Action& action) const {
  return interface_->HasAction(action);
}

template <typename T>
std::optional<char> BaseInterfaceDecorator<T>::CharacterPressed() const {
  return interface_->CharacterPressed();
}

template <typename T>
band::Point BaseInterfaceDecorator<T>::MousePosition() const {
  return interface_->MousePosition();
}

template <typename T>
band::WindowArea BaseInterfaceDecorator<T>::WindowArea() const {
  return interface_->WindowArea();
}

}  // namespace interface
}  // namespace band
