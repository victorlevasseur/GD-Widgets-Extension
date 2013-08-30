#ifndef WCORE_PALETTE_H
#define WCORE_PALETTE_H

#include "WidgetsCore/Defs.h"

#include <map>
#include <vector>
#include <string>

#include <SFML/Graphics/Color.hpp>

namespace WCore
{

class Widget;

typedef int States;

enum State
{
    DISABLED = 1,
    ENABLED = 2,
    HOVERED = 4,
    FOCUSED = 8,
    FOCUSED_HOVERED = 16
};

State WIDGETS_CORE_API GetWidgetState(const Widget &widget);

class WIDGETS_CORE_API Color
{

public:
    Color();
    ~Color();

    sf::Color GetColor(State state) const;
    void SetColor(States states, sf::Color color);

private:

    bool HasState(States states, State state) const;

    sf::Color m_focusedColor;
    sf::Color m_focusedHoveredColor;
    sf::Color m_hoveredColor;
    sf::Color m_unfocusedColor;
    sf::Color m_disabledColor;
};

class WIDGETS_CORE_API Palette
{

public:
    Palette();
    ~Palette();

    /// Get the color
    sf::Color GetColor(const std::string &color, State state);
    sf::Color GetColor(const std::string &color, State state) const;

    /// Set the color
    Palette& SetColor(const std::string &colorName, States states, sf::Color color);

    std::vector<std::string> GetColorsNames() const;

private:
    std::map<std::string, Color> m_colorPalette;

};

}

#endif
