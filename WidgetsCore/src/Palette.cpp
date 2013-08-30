#include "WidgetsCore/Palette.h"

#include "WidgetsCore/Widget.h"

namespace WCore
{

State GetWidgetState(const Widget &widget)
{
    if(widget.IsEnabled())
    {
        if(widget.HasFocus())
        {
            if(widget.IsHovered())
            {
                return FOCUSED_HOVERED;
            }
            else
            {
                return FOCUSED;
            }
        }
        else
        {
            if(widget.IsHovered())
            {
                return HOVERED;
            }
            else
            {
                return ENABLED;
            }
        }
    }
    else
    {
        return DISABLED;
    }
}

Color::Color() : m_focusedColor(), m_focusedHoveredColor(), m_hoveredColor(), m_unfocusedColor(), m_disabledColor()
{

}

Color::~Color()
{

}

sf::Color Color::GetColor(State state) const
{
    switch (state)
    {
    case DISABLED:
        return m_disabledColor;
    case ENABLED:
        return m_unfocusedColor;
    case HOVERED:
        return m_hoveredColor;
    case FOCUSED:
        return m_focusedColor;
    case FOCUSED_HOVERED:
        return m_focusedHoveredColor;
    default:
        return sf::Color();
    }
}

void Color::SetColor(States states, sf::Color color)
{
    if(HasState(states, DISABLED))
    {
        m_disabledColor = color;
    }
    if(HasState(states, ENABLED))
    {
        m_unfocusedColor = color;
    }
    if(HasState(states, HOVERED))
    {
        m_hoveredColor = color;
    }
    if(HasState(states, FOCUSED))
    {
        m_focusedColor = color;
    }
    if(HasState(states, FOCUSED_HOVERED))
    {
        m_focusedHoveredColor = color;
    }
}

bool Color::HasState(States states, State state) const
{
    return ((states & state) != 0);
}

Palette::Palette() : m_colorPalette()
{

}

Palette::~Palette()
{

}

sf::Color Palette::GetColor(const std::string &color, State state)
{
    return m_colorPalette[color].GetColor(state);
}

sf::Color Palette::GetColor(const std::string &color, State state) const
{
    return m_colorPalette.at(color).GetColor(state);
}

Palette& Palette::SetColor(const std::string &colorName, States states, sf::Color color)
{
    m_colorPalette[colorName].SetColor(states, color);
    return *this;
}

std::vector<std::string> Palette::GetColorsNames() const
{
    std::vector<std::string> colorsList;

    for(std::map<std::string, Color>::const_iterator it = m_colorPalette.begin(); it != m_colorPalette.end(); it++)
    {
        colorsList.push_back(it->first);
    }

    return colorsList;
}

}
