#ifndef COLORTOOLS_H
#define COLORTOOLS_H

#include "WidgetsCore/Defs.h"

#include <SFML/Graphics/Color.hpp>
#if defined(GD_IDE_ONLY)
#include <wx/colour.h>
#include <wx/variant.h>
#endif

namespace WCore
{

#if defined(GD_IDE_ONLY)
wxColour WIDGETS_CORE_API ToWxColour(sf::Color color);
sf::Color WIDGETS_CORE_API ToSfColor(wxColour colour);
sf::Color WIDGETS_CORE_API ToSfColor(wxVariant variant);
#endif

}

#endif // COLORTOOLS_H
