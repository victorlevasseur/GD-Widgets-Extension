#include "WidgetsCore/PaletteSerialization.h"

#include <string>
#include <vector>

#include "GDCore/CommonTools.h"

namespace WCore
{

Palette LoadPaletteFromXml(const TiXmlElement *paletteElem)
{
    Palette palette;

    for(const TiXmlElement* e = paletteElem->FirstChildElement("Color"); e != NULL; e = e->NextSiblingElement("Color"))
    {
        std::string colorName = std::string(e->Attribute("name"));

        {
            std::string colorStr = std::string(e->Attribute("disabled"));
            palette.SetColor(colorName, DISABLED, StringToColor(colorStr));
        }
        {
            std::string colorStr = std::string(e->Attribute("enabled"));
            palette.SetColor(colorName, ENABLED, StringToColor(colorStr));
        }
        {
            std::string colorStr = std::string(e->Attribute("focused"));
            palette.SetColor(colorName, FOCUSED, StringToColor(colorStr));
        }
        {
            std::string colorStr = std::string(e->Attribute("hovered"));
            palette.SetColor(colorName, HOVERED, StringToColor(colorStr));
        }
        {
            std::string colorStr = std::string(e->Attribute("focusedhovered"));
            palette.SetColor(colorName, FOCUSED_HOVERED, StringToColor(colorStr));
        }
    }

    return palette;
}

void SavePaletteToXml(TiXmlElement *paletteElem, const Palette &palette)
{
    std::vector<std::string> colorsList = palette.GetColorsNames();

    for(unsigned int a = 0; a < colorsList.size(); a++)
    {
        TiXmlElement *colorElem = new TiXmlElement("Color");
        paletteElem->LinkEndChild(colorElem);

        std::string &colorName = colorsList.at(a);

        colorElem->SetAttribute("name", colorName.c_str());

        colorElem->SetAttribute("disabled", ColorToString(palette.GetColor(colorName, DISABLED)).c_str());
        colorElem->SetAttribute("enabled", ColorToString(palette.GetColor(colorName, ENABLED)).c_str());
        colorElem->SetAttribute("hovered", ColorToString(palette.GetColor(colorName, HOVERED)).c_str());
        colorElem->SetAttribute("focused", ColorToString(palette.GetColor(colorName, FOCUSED)).c_str());
        colorElem->SetAttribute("focusedhovered", ColorToString(palette.GetColor(colorName, FOCUSED_HOVERED)).c_str());
    }
}

std::string ColorToString(const sf::Color color)
{
    return std::string(gd::ToString<int>(color.r) + ";" + gd::ToString<int>(color.g) + ";" + gd::ToString<int>(color.b) + ";" + gd::ToString<int>(color.a));
}

sf::Color StringToColor(const std::string &str)
{
    std::vector<std::string> components;
    std::istringstream f(str);
    std::string s;
    while (std::getline(f, s, ';'))
    {
        components.push_back(s);
    }

    if(components.size() != 4)
    {
        return sf::Color();
    }

    return sf::Color(gd::ToInt(components[0]), gd::ToInt(components[1]), gd::ToInt(components[2]), gd::ToInt(components[3]));
}

}
