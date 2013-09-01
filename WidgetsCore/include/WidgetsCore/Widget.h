#ifndef WCORE_WIDGET_H
#define WCORE_WIDGET_H

#include "WidgetsCore/Defs.h"

#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include "WidgetsCore/Palette.h"

namespace WCore
{

class WIDGETS_CORE_API Widget
{
public:
    Widget();
    virtual ~Widget();

    virtual void Draw(sf::RenderTarget &wnd) = 0;

    void SetPosition(sf::Vector2f position);
    sf::Vector2f GetPosition() const;
    void SetAngle(float angle);
    float GetAngle() const;
    void SetSize(sf::Vector2f _size);
    sf::Vector2f GetSize() const;

    sf::Vector2f ConvertPoint(sf::Vector2f point) const;

    void ProceedEvent(sf::Event event);
    void ProceedTime(float time);

    void Enable();
    void Disable();
    bool IsEnabled() const;

    void GrabFocus();
    void LostFocus();
    bool HasFocus() const;

    bool IsHovered() const;

    ///Returns true if the point (relative to the widget (see ConvertPoint) ) is on the widget.
    virtual bool IsOnWidget(sf::Vector2f point) const;

    Palette& GetPalette();
    const Palette& GetPalette() const;
    void SetPalette(Palette &palette);
    void ApplyPalette();

protected:
    virtual void HandleMouseButtonEvent(sf::Mouse::Button button, bool pressed, int x, int y) {};
    virtual void HandleMouseMoveEvent(int x, int y) {};
    virtual void HandleKeyboardEvent(sf::Keyboard::Key button, bool pressed) {};
    virtual void HandleTextEntered(sf::Uint32 character) {};

    virtual void HandleStateChange() {};

    virtual void HandleSizeChange() {};
    virtual void HandlePositionChange() {};

    virtual void HandleTime(float time) {};

    virtual void UpdateDrawables() {};

    sf::Transform m_currentTransform;

    sf::Vector2f m_position;
    float m_angle;
    sf::Vector2f m_size;

    bool m_focus;
    bool m_enabled;
    bool m_hovered;

private:
    void UpdateTransform();

    Palette m_palette;
};

}

#endif // WCORE_WIDGET_H
