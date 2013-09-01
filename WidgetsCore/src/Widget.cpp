#include "WidgetsCore/Widget.h"

namespace WCore
{

Widget::Widget() : m_currentTransform(), m_position(0, 0), m_angle(0), m_size(0, 0), m_focus(false), m_enabled(true), m_hovered(false), m_palette()
{
    UpdateTransform();
}

Widget::~Widget()
{

}

void Widget::SetPosition(sf::Vector2f position)
{
    m_position = position;
    UpdateTransform();
    HandlePositionChange();
}

sf::Vector2f Widget::GetPosition() const
{
    return m_position;
}

void Widget::SetAngle(float angle)
{
    m_angle = angle;
    UpdateTransform();
}

float Widget::GetAngle() const
{
    return m_angle;
}

void Widget::SetSize(sf::Vector2f _size)
{
    m_size = _size;
    UpdateTransform();
    HandleSizeChange();
}

sf::Vector2f Widget::GetSize() const
{
    return m_size;
}

sf::Vector2f Widget::ConvertPoint(sf::Vector2f point) const
{
    return m_currentTransform.getInverse().transformPoint(point);
}

void Widget::ProceedEvent(sf::Event event)
{
    //Manage widget's focus
    if(event.type == sf::Event::MouseButtonPressed)
    {
        sf::Vector2f mousePosition(event.mouseButton.x, event.mouseButton.y);
        sf::Vector2f mouseRelative = ConvertPoint(mousePosition);

        if(IsOnWidget(mouseRelative) && !m_focus)
        {
            GrabFocus();
        }
        if(!IsOnWidget(mouseRelative) && m_focus)
        {
            LostFocus();
        }
    }

    //Manage widget hovering
    if(event.type == sf::Event::MouseWheelMoved)
    {
        sf::Vector2f mousePosition(event.mouseWheel.x, event.mouseWheel.y);
        sf::Vector2f mouseRelative = ConvertPoint(mousePosition);

        event.mouseWheel.x = mouseRelative.x;
        event.mouseWheel.y = mouseRelative.y;

        if(IsOnWidget(mouseRelative) && !m_hovered)
        {
            m_hovered = true;
            UpdateDrawables();

            HandleStateChange();
        }
        else if(!IsOnWidget(mouseRelative) && m_hovered)
        {
            m_hovered = false;
            UpdateDrawables();

            HandleStateChange();
        }
    }
    else if(event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased )
    {
        sf::Vector2f mousePosition(event.mouseButton.x, event.mouseButton.y);
        sf::Vector2f mouseRelative = ConvertPoint(mousePosition);

        event.mouseButton.x = mouseRelative.x;
        event.mouseButton.y = mouseRelative.y;

        if(IsOnWidget(mouseRelative) && !m_hovered)
        {
            m_hovered = true;
            UpdateDrawables();

            HandleStateChange();
        }
        else if(!IsOnWidget(mouseRelative) && m_hovered)
        {
            m_hovered = false;
            UpdateDrawables();

            HandleStateChange();
        }
    }
    else if(event.type == sf::Event::MouseMoved || event.type == sf::Event::MouseEntered || event.type == sf::Event::MouseLeft)
    {
        sf::Vector2f mousePosition(event.mouseMove.x, event.mouseMove.y);
        sf::Vector2f mouseRelative = ConvertPoint(mousePosition);

        event.mouseMove.x = mouseRelative.x;
        event.mouseMove.y = mouseRelative.y;

        if(IsOnWidget(mouseRelative) && !m_hovered)
        {
            m_hovered = true;
            UpdateDrawables();

            HandleStateChange();
        }
        else if(!IsOnWidget(mouseRelative) && m_hovered)
        {
            m_hovered = false;
            UpdateDrawables();

            HandleStateChange();
        }
    }

    //Send event info to event's handlers
    if(event.type == sf::Event::MouseButtonPressed)
    {
        HandleMouseButtonEvent(event.mouseButton.button, true, event.mouseButton.x, event.mouseButton.y);
    }
    else if(event.type == sf::Event::MouseButtonReleased)
    {
        HandleMouseButtonEvent(event.mouseButton.button, false, event.mouseButton.x, event.mouseButton.y);
    }
    else if(event.type == sf::Event::MouseMoved)
    {
        HandleMouseMoveEvent(event.mouseMove.x, event.mouseMove.y);
    }
    else if(event.type == sf::Event::KeyPressed)
    {
        HandleKeyboardEvent(event.key.code, true);
    }
    else if(event.type == sf::Event::KeyReleased)
    {
        HandleKeyboardEvent(event.key.code, false);
    }
    else if(event.type == sf::Event::TextEntered)
    {
        HandleTextEntered(event.text.unicode);
    }
}

void Widget::ProceedTime(float time)
{
    HandleTime(time);
}

void Widget::GrabFocus()
{
    m_focus = true;
    UpdateDrawables();
    HandleStateChange();
}

void Widget::LostFocus()
{
    m_focus = false;
    UpdateDrawables();
    HandleStateChange();
}

bool Widget::HasFocus() const
{
    return m_focus;
}

void Widget::Enable()
{
    m_enabled = true;
    UpdateDrawables();
    HandleStateChange();
}

void Widget::Disable()
{
    m_enabled = false;
    m_focus = false;
    m_hovered = false;
    UpdateDrawables();
    HandleStateChange();
}

bool Widget::IsEnabled() const
{
    return m_enabled;
}

bool Widget::IsHovered() const
{
    return m_hovered;
}

bool Widget::IsOnWidget(sf::Vector2f point) const
{
    if(point.x <= m_size.x && point.y <= m_size.y && point.x >= 0 && point.y >= 0)
        return true;
    else
        return false;
}

Palette& Widget::GetPalette()
{
    return m_palette;
}

const Palette& Widget::GetPalette() const
{
    return m_palette;
}

void Widget::SetPalette(Palette &palette)
{
    m_palette = palette;
    UpdateDrawables();
}

void Widget::ApplyPalette()
{
    UpdateDrawables();
}

void Widget::UpdateTransform()
{
    m_currentTransform = sf::Transform();
    m_currentTransform.translate((m_size / 2.f) + m_position);
    m_currentTransform.rotate(m_angle);
    m_currentTransform.translate(-(m_size / 2.f));
}

}
