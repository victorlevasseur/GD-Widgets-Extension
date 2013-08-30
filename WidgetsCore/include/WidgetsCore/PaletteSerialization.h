#ifndef PALETTESERIALIZATION_H
#define PALETTESERIALIZATION_H

#include "WidgetsCore/Defs.h"

#include <SFML/Graphics/Color.hpp>
#include "GDCpp/tinyxml/tinyxml.h"
#include "WidgetsCore/Palette.h"

namespace WCore
{

Palette WIDGETS_CORE_API LoadPaletteFromXml(const TiXmlElement *paletteElem);
void WIDGETS_CORE_API SavePaletteToXml(TiXmlElement *paletteElem, const Palette &palette);

std::string WIDGETS_CORE_API ColorToString(const sf::Color color);
sf::Color WIDGETS_CORE_API StringToColor(const std::string &str);

}

#endif // PALETTESERIALIZATION_H
