/**

Game Develop - Text Object Extension
Copyright (c) 2008-2013 Florian Rival (Florian.Rival@gmail.com)

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not
    claim that you wrote the original software. If you use this software
    in a product, an acknowledgment in the product documentation would be
    appreciated but is not required.

    2. Altered source versions must be plainly marked as such, and must not be
    misrepresented as being the original software.

    3. This notice may not be removed or altered from any source
    distribution.

*/

#if defined(GD_IDE_ONLY)
#include "TextBoxObjectEditor.h" //Must be placed first, otherwise we get errors relative to "cannot convert 'const TCHAR*'..." in wx/msw/winundef.h
#include <wx/bitmap.h>
#endif
#include <SFML/Graphics.hpp>
#include "GDCpp/Object.h"

#include "GDCpp/ImageManager.h"
#include "GDCpp/tinyxml/tinyxml.h"
#include "GDCpp/FontManager.h"
#include "GDCpp/Position.h"
#include "GDCpp/Polygon.h"
#include "GDCpp/RuntimeScene.h"
#include "GDCpp/CommonTools.h"
#include "GDCpp/XmlMacros.h"

#include "TextBoxObject.h"

#include "WidgetsCore/PaletteSerialization.h"
#include "WidgetsCore/CameraTools.h"

#if defined(GD_IDE_ONLY)
#include "GDCore/IDE/ArbitraryResourceWorker.h"
#include "GDCore/CommonTools.h"
namespace gd { class MainFrameWrapper; }
#endif

using namespace std;

TextBoxObject::TextBoxObject(std::string name_) :
    Object(name_),
    m_textBox()
{
}

TextBoxObject::~TextBoxObject()
{
};

void TextBoxObject::DoLoadFromXml(gd::Project & project, const TiXmlElement * elem)
{
    if ( elem->FirstChildElement("Font") && elem->FirstChildElement("Font")->Attribute("value") )
        SetFontFilename(elem->FirstChildElement("Font")->Attribute("value"));

    if ( elem->FirstChildElement("String") && elem->FirstChildElement("String")->Attribute("value") )
        SetString(sf::String(elem->FirstChildElement("String")->Attribute("value")));

    if (elem->FirstChildElement("CharacterSize"))
    {
        float value = 30.f;
        elem->FirstChildElement("CharacterSize")->QueryFloatAttribute("value", &value);

        SetCharacterSize(value);
    }

    if (elem->FirstChildElement("BorderThickness"))
    {
        int value = 1;
        elem->FirstChildElement("BorderThickness")->QueryIntAttribute("value", &value);

        SetBorderThickness(value);
    }

    if ( elem->FirstChildElement("AllowTextSelection") && elem->FirstChildElement("AllowTextSelection")->Attribute("value") )
    {
        std::cout << elem->FirstChildElement("AllowTextSelection")->Attribute("value") << std::endl;

        if(std::string(elem->FirstChildElement("AllowTextSelection")->Attribute("value")) == "true")
            AllowTextSelection(true);
        else
            AllowTextSelection(false);
    }

    if (elem->FirstChildElement("HideCharacter"))
    {
        int value = 1;
        elem->FirstChildElement("HideCharacter")->QueryIntAttribute("value", &value);

        SetHideCharacter(sf::Uint32(value));
    }

    if ( elem->FirstChildElement("Placeholder") && elem->FirstChildElement("Placeholder")->Attribute("value") )
        SetPlaceholder(sf::String(elem->FirstChildElement("Placeholder")->Attribute("value")));

    if(elem->FirstChildElement("Palette"))
    {
        SetWidgetPalette(WCore::LoadPaletteFromXml(elem->FirstChildElement("Palette")));
    }
}

sf::String TextBoxObject::GetString() const
{
    return m_textBox.GetText();
}

void TextBoxObject::SetString(const sf::String &str)
{
    m_textBox.SetText(str);
}

float TextBoxObject::GetCharacterSize() const
{
    return m_textBox.GetCharacterSize();
}

void TextBoxObject::SetCharacterSize(float _size)
{
    m_textBox.SetCharacterSize(_size);
}

void TextBoxObject::SetBorderThickness(int thickness)
{
    m_textBox.SetBorderThickness(thickness);
}

int TextBoxObject::GetBorderThickness() const
{
    return m_textBox.GetBorderThickness();
}

void TextBoxObject::AllowTextSelection(bool allow)
{
    m_textBox.AllowTextSelection(allow);
}

bool TextBoxObject::IsAllowingTextSelection() const
{
    return m_textBox.IsAllowingTextSelection();
}

void TextBoxObject::SetHideCharacter(sf::Uint32 character)
{
    m_textBox.SetHideCharacter(character);
}

sf::Uint32 TextBoxObject::GetHideCharacter() const
{
    return m_textBox.GetHideCharacter();
}

void TextBoxObject::SetPlaceholder(sf::String placeholder)
{
    m_textBox.SetPlaceholder(placeholder);
}

sf::String TextBoxObject::GetPlaceholder() const
{
    return m_textBox.GetPlaceholder();
}

const WCore::Palette& TextBoxObject::GetWidgetPalette() const
{
    return m_textBox.GetPalette();
}

void TextBoxObject::SetWidgetPalette(WCore::Palette palette)
{
    m_textBox.SetPalette(palette);
}

#if defined(GD_IDE_ONLY)
void TextBoxObject::DrawInitialInstance(gd::InitialInstance & instance, sf::RenderTarget & renderTarget, gd::Project & project, gd::Layout & layout)
{
    m_textBox.SetPosition(sf::Vector2f(instance.GetX(), instance.GetY()));

    //Set the size
    if(instance.HasCustomSize())
    {
        m_textBox.SetSize(sf::Vector2f(instance.GetCustomWidth(), instance.GetCustomHeight()));
    }
    else
    {
        m_textBox.SetSize(GetInitialInstanceDefaultSize(instance, project, layout));
    }

    //Set the angle
    m_textBox.SetAngle(instance.GetAngle());

    m_textBox.Draw(renderTarget);
}

sf::Vector2f TextBoxObject::GetInitialInstanceDefaultSize(gd::InitialInstance & instance, gd::Project & project, gd::Layout & layout) const
{
    return sf::Vector2f(160, 30);
}

void TextBoxObject::LoadResources(gd::Project & project, gd::Layout & layout)
{
    if ( FontManager::GetInstance()->GetFont(fontName) )
        m_textBox.SetFont(*FontManager::GetInstance()->GetFont(fontName));
    else
        m_textBox.SetFont(*FontManager::GetInstance()->GetFont(""));
}

void TextBoxObject::DoSaveToXml(TiXmlElement * elem)
{
    TiXmlElement * fontElem = new TiXmlElement( "Font" );
    elem->LinkEndChild( fontElem );
    fontElem->SetAttribute("value", GetFontFilename().c_str());

    TiXmlElement * stringElem = new TiXmlElement( "String" );
    elem->LinkEndChild( stringElem );
    stringElem->SetAttribute("value", GetString().toAnsiString().c_str());

    TiXmlElement * charSizeElem = new TiXmlElement( "CharacterSize" );
    elem->LinkEndChild( charSizeElem );
    charSizeElem->SetDoubleAttribute("value", GetCharacterSize());

    TiXmlElement * borderElem = new TiXmlElement( "BorderThickness" );
    elem->LinkEndChild( borderElem );
    borderElem->SetAttribute("value", GetBorderThickness());

    TiXmlElement * txtSelElem = new TiXmlElement( "AllowTextSelection" );
    elem->LinkEndChild( txtSelElem );
    txtSelElem->SetAttribute("value", IsAllowingTextSelection() ? "true" : "false");

    TiXmlElement * hideCharElem = new TiXmlElement( "HideCharacter" );
    elem->LinkEndChild( hideCharElem );
    hideCharElem->SetAttribute("value", (int)GetHideCharacter());

    TiXmlElement * placeholderElem = new TiXmlElement( "Placeholder" );
    elem->LinkEndChild( placeholderElem );
    placeholderElem->SetAttribute("value", GetPlaceholder().toAnsiString().c_str());

    TiXmlElement * paletteElem = new TiXmlElement( "Palette" );
    elem->LinkEndChild( paletteElem );
    WCore::SavePaletteToXml(paletteElem, GetWidgetPalette());
}

void TextBoxObject::ExposeResources(gd::ArbitraryResourceWorker & worker)
{
    worker.ExposeResource(fontName);
}

bool TextBoxObject::GenerateThumbnail(const gd::Project & project, wxBitmap & thumbnail) const
{
    thumbnail = wxBitmap("CppPlatform/Extensions/TextBox24.png", wxBITMAP_TYPE_ANY);

    return true;
}

void TextBoxObject::EditObject( wxWindow* parent, gd::Project & game, gd::MainFrameWrapper & mainFrameWrapper )
{
    TextBoxObjectEditor dialog(parent, game, *this, mainFrameWrapper);
    dialog.ShowModal();
}
#endif

/* RuntimeTextBoxObject : */

RuntimeTextBoxObject::RuntimeTextBoxObject(RuntimeScene & scene, const gd::Object & object) :
    RuntimeObject(scene, object),
    m_textBox(),
    m_scene(&scene)
{
    const TextBoxObject & textBoxObject = static_cast<const TextBoxObject&>(object);

    m_textBox = textBoxObject.m_textBox;
    ChangeFont(textBoxObject.GetFontFilename());
}

bool RuntimeTextBoxObject::Draw( sf::RenderTarget& renderTarget )
{
    if ( hidden ) return true; //Don't draw anything if hidden

    m_textBox.Draw(renderTarget);
    return true;
}

void RuntimeTextBoxObject::OnPositionChanged()
{
    m_textBox.SetPosition(sf::Vector2f(GetX(), GetY()));
}

/**
 * RuntimeTextBoxObject provides a basic bounding box.
 */
std::vector<Polygon2d> RuntimeTextBoxObject::GetHitBoxes() const
{
    std::vector<Polygon2d> mask;
    Polygon2d rectangle = Polygon2d::CreateRectangle(GetWidth(), GetHeight());
    rectangle.Rotate(GetAngle()/180*3.14159);
    rectangle.Move(GetX()+GetCenterX(), GetY()+GetCenterY());

    mask.push_back(rectangle);
    return mask;
}

void RuntimeTextBoxObject::UpdateTime(float timeElapsed)
{
    const std::vector<sf::Event> & events = m_scene->GetRenderTargetEvents();
    for(unsigned int i = 0; i < events.size(); i++)
    {
        sf::Event event = events[i];

        //Map window coords to real world coords
        if(event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased)
        {
            sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
            sf::Vector2f worldPos(WCore::MapPixelsToCoords(mousePos, GetLayer(), *m_scene));

            event.mouseButton.x = worldPos.x;
            event.mouseButton.y = worldPos.y;
        }
        else if(event.type == sf::Event::MouseMoved || event.type == sf::Event::MouseEntered || event.type == sf::Event::MouseLeft)
        {
            sf::Vector2i mousePos(event.mouseMove.x, event.mouseMove.y);
            sf::Vector2f worldPos(WCore::MapPixelsToCoords(mousePos, GetLayer(), *m_scene));

            event.mouseMove.x = worldPos.x;
            event.mouseMove.y = worldPos.y;
        }
        else if(event.type == sf::Event::MouseWheelMoved)
        {
            sf::Vector2i mousePos(event.mouseWheel.x, event.mouseWheel.y);
            sf::Vector2f worldPos(WCore::MapPixelsToCoords(mousePos, GetLayer(), *m_scene));

            event.mouseWheel.x = worldPos.x;
            event.mouseWheel.y = worldPos.y;
        }

        //Proceed the event
        m_textBox.ProceedEvent(event);
    }

    m_textBox.ProceedTime(timeElapsed);
}

/**
 * Get the real X position of the sprite
 */
float RuntimeTextBoxObject::GetDrawableX() const
{
    return m_textBox.GetPosition().x;
}

/**
 * Get the real Y position of the text
 */
float RuntimeTextBoxObject::GetDrawableY() const
{
    return m_textBox.GetPosition().y;
}

/**
 * Width is the width of the current sprite.
 */
float RuntimeTextBoxObject::GetWidth() const
{
    return m_textBox.GetSize().x;
}

/**
 * Height is the height of the current sprite.
 */
float RuntimeTextBoxObject::GetHeight() const
{
    return m_textBox.GetSize().y;
}

void RuntimeTextBoxObject::SetWidth(float _width)
{
    m_textBox.SetSize(sf::Vector2f(_width, GetHeight()));
}

void RuntimeTextBoxObject::SetHeight(float _height)
{
    m_textBox.SetSize(sf::Vector2f(GetWidth(), _height));
}

bool RuntimeTextBoxObject::SetAngle(float newAngle)
{
    m_textBox.SetAngle(newAngle);
    return true;
}

float RuntimeTextBoxObject::GetAngle() const
{
    return m_textBox.GetAngle();
}

std::string RuntimeTextBoxObject::GetString() const
{
    return (std::string)m_textBox.GetText();
}

void RuntimeTextBoxObject::SetString(const std::string &str)
{
    m_textBox.SetText(sf::String(str));
}

std::string RuntimeTextBoxObject::GetSelectedString() const
{
    return m_textBox.GetSelectedText();
}

int RuntimeTextBoxObject::GetSelectionBegin() const
{
    return m_textBox.GetSelectionBegin();
}

int RuntimeTextBoxObject::GetSelectionEnd() const
{
    return m_textBox.GetSelectionEnd();
}

void RuntimeTextBoxObject::Select(int position)
{
    m_textBox.Select(position);
}

void RuntimeTextBoxObject::Select(int begin_, int end_)
{
    m_textBox.Select(begin_, end_);
}

void RuntimeTextBoxObject::ChangeFont(const std::string & fontName_)
{
    if (!m_textBox.GetFont() || fontName_ != fontName )
    {
        fontName = fontName_;
        m_textBox.SetFont(*FontManager::GetInstance()->GetFont(fontName));
        OnPositionChanged();
    }
}

float RuntimeTextBoxObject::GetCharacterSize() const
{
    return m_textBox.GetCharacterSize();
}

void RuntimeTextBoxObject::SetCharacterSize(float _size)
{
    m_textBox.SetCharacterSize(_size);
}

void RuntimeTextBoxObject::SetBorderThickness(int thickness)
{
    m_textBox.SetBorderThickness(thickness);
}

int RuntimeTextBoxObject::GetBorderThickness() const
{
    return m_textBox.GetBorderThickness();
}

void RuntimeTextBoxObject::AllowTextSelection(bool allow)
{
    m_textBox.AllowTextSelection(allow);
}

bool RuntimeTextBoxObject::IsAllowingTextSelection() const
{
    return m_textBox.IsAllowingTextSelection();
}

void RuntimeTextBoxObject::Enable(bool enable)
{
    if(enable)
        m_textBox.Enable();
    else
        m_textBox.Disable();
}

bool RuntimeTextBoxObject::IsEnabled() const
{
    return m_textBox.IsEnabled();
}

void RuntimeTextBoxObject::SetReadOnly(bool readonly)
{
    m_textBox.SetReadOnly(readonly);
}

bool RuntimeTextBoxObject::IsReadOnly() const
{
    return m_textBox.IsReadOnly();
}

void RuntimeTextBoxObject::SetHideCharacter(const std::string &character)
{
    sf::String hideCharStr(character);
    if(hideCharStr.isEmpty())
    {
        m_textBox.SetHideCharacter(0);
    }
    else
    {
        m_textBox.SetHideCharacter(hideCharStr[0]);
    }
}

std::string RuntimeTextBoxObject::GetHideCharacter() const
{
    if(m_textBox.GetHideCharacter() == 0)
        return std::string();

    sf::String hideCharStr(m_textBox.GetHideCharacter());
    return hideCharStr.toAnsiString();
}

void RuntimeTextBoxObject::SetPlaceholder(const std::string &placeholder)
{
    m_textBox.SetPlaceholder(placeholder);
}

std::string RuntimeTextBoxObject::GetPlaceholder() const
{
    return m_textBox.GetPlaceholder();
}

#if defined(GD_IDE_ONLY)
void RuntimeTextBoxObject::GetPropertyForDebugger(unsigned int propertyNb, string & name, string & value) const
{
    switch (propertyNb)
    {
    case 0:
        name = _("String");
        value = GetString();
        break;
    case 1:
        name = _("Hide character");
        value = GetHideCharacter().empty() ? "No hide character" : GetHideCharacter();
        break;
    case 2:
        name = _("Placeholder");
        value = GetPlaceholder();
        break;
    case 3:
        name = _("Character size");
        value = gd::ToString(GetCharacterSize());
        break;
    }
}

bool RuntimeTextBoxObject::ChangeProperty(unsigned int propertyNb, string newValue)
{
    switch (propertyNb)
    {
    case 0:
        SetString(newValue);
        break;
    case 1:
        if(newValue == "" || newValue.empty())
            SetHideCharacter(std::string());
        else
            SetHideCharacter(newValue);
        break;
    case 2:
        SetPlaceholder(newValue);
        break;
    case 3:
        SetCharacterSize(gd::ToDouble(newValue));
        break;
    }

    return true;
}

unsigned int RuntimeTextBoxObject::GetNumberOfProperties() const
{
    return 4;
}
#endif

void DestroyRuntimeTextBoxObject(RuntimeObject * object)
{
    delete object;
}

RuntimeObject * CreateRuntimeTextBoxObject(RuntimeScene & scene, const gd::Object & object)
{
    return new RuntimeTextBoxObject(scene, object);
}

/**
 * Function destroying an extension Object.
 * Game Develop does not delete directly extension object
 * to avoid overloaded new/delete conflicts.
 */
void DestroyTextBoxObject(gd::Object * object)
{
    delete object;
}

/**
 * Function creating an extension Object.
 * Game Develop can not directly create an extension object
 */
gd::Object * CreateTextBoxObject(std::string name)
{
    return new TextBoxObject(name);
}


