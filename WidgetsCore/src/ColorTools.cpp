#include "WidgetsCore/ColorTools.h"

namespace WCore
{

#if defined(GD_IDE_ONLY)
wxColour ToWxColour(sf::Color color)
{
    return wxColour(color.r, color.g, color.b, color.a);
}

sf::Color ToSfColor(wxColour colour)
{
    return sf::Color(colour.Red(), colour.Green(), colour.Blue(), colour.Alpha());
}

sf::Color ToSfColor(wxVariant variant)
{
    wxColour colour;
    colour << variant;

    return ToSfColor(colour);
}
#endif

}
