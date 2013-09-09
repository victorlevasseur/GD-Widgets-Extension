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

#ifndef TextBoxObject_H
#define TextBoxObject_H

#include <SFML/Graphics/Text.hpp>
#include "GDCpp/Object.h"
#include "GDCpp/RuntimeObject.h"

#include "TextBox.h"
#include "WidgetsCore/Palette.h"

class ImageManager;
class RuntimeScene;
namespace gd { class Object; }
namespace gd { class ImageManager; }
namespace gd { class InitialInstance; }
#if defined(GD_IDE_ONLY)
class wxBitmap;
namespace gd { class Project; }
class wxWindow;
namespace gd { class MainFrameWrapper; }
namespace gd {class ResourcesMergingHelper;}
#endif

/**
 * Text Object
 */
class GD_EXTENSION_API TextBoxObject : public gd::Object
{
    friend class RuntimeTextBoxObject;

public :

    TextBoxObject(std::string name_);
    virtual ~TextBoxObject();
    virtual gd::Object * Clone() const { return new TextBoxObject(*this); }

    #if defined(GD_IDE_ONLY)
    virtual void DrawInitialInstance(gd::InitialInstance & instance, sf::RenderTarget & renderTarget, gd::Project & project, gd::Layout & layout);
    virtual sf::Vector2f GetInitialInstanceDefaultSize(gd::InitialInstance & instance, gd::Project & project, gd::Layout & layout) const;
    virtual void ExposeResources(gd::ArbitraryResourceWorker & worker);
    virtual bool GenerateThumbnail(const gd::Project & project, wxBitmap & thumbnail) const;
    virtual void EditObject( wxWindow* parent, gd::Project & game_, gd::MainFrameWrapper & mainFrameWrapper_ );
    virtual void LoadResources(gd::Project & project, gd::Layout & layout);
    #endif

    sf::String GetString() const;
    void SetString(const sf::String &str);

    inline std::string GetFontFilename() const {return fontName; };
    void SetFontFilename(const std::string & fontFilename) { fontName = fontFilename; };

    float GetCharacterSize() const;
    void SetCharacterSize(float _size);

    void SetBorderThickness(int thickness);
    int GetBorderThickness() const;

    void AllowTextSelection(bool allow);
    bool IsAllowingTextSelection() const;

    void SetHideCharacter(sf::Uint32 character);
    sf::Uint32 GetHideCharacter() const;

    void SetPlaceholder(sf::String placeholder);
    sf::String GetPlaceholder() const;

    const WCore::Palette& GetWidgetPalette() const;
    void SetWidgetPalette(WCore::Palette palette);

private:

    virtual void DoLoadFromXml(gd::Project & project, const TiXmlElement * elemScene);
    #if defined(GD_IDE_ONLY)
    virtual void DoSaveToXml(TiXmlElement * elemScene);
    #endif

    TextBox m_textBox;
    std::string fontName;
};

class GD_EXTENSION_API RuntimeTextBoxObject : public RuntimeObject
{
public :

    RuntimeTextBoxObject(RuntimeScene & scene, const gd::Object & object);
    virtual ~RuntimeTextBoxObject() {};
    virtual RuntimeObject * Clone() const { return new RuntimeTextBoxObject(*this);}

    virtual bool Draw(sf::RenderTarget & renderTarget);

    virtual void OnPositionChanged();

    virtual float GetWidth() const;
    virtual float GetHeight() const;

    virtual void SetWidth(float _width);
    virtual void SetHeight(float _height);

    virtual float GetDrawableX() const;
    virtual float GetDrawableY() const;

    virtual bool SetAngle(float newAngle);
    virtual float GetAngle() const;

    std::string GetString() const;
    void SetString(const std::string &str);

    std::string GetSelectedString() const;
    int GetSelectionBegin() const;
    int GetSelectionEnd() const;

    void Select(int position);
    void Select(int begin_, int end_);

    void ChangeFont(const std::string & fontFilename);
    inline std::string GetFontFilename() const {return fontName;};

    float GetCharacterSize() const;
    void SetCharacterSize(float _size);

    void SetBorderThickness(int thickness);
    int GetBorderThickness() const;

    void AllowTextSelection(bool allow);
    bool IsAllowingTextSelection() const;

    void SetHideCharacter(const std::string &character);
    std::string GetHideCharacter() const;

    void SetPlaceholder(const std::string &placeholder);
    std::string GetPlaceholder() const;

    virtual std::vector<Polygon2d> GetHitBoxes() const;

    virtual void UpdateTime(float timeElapsed);

    #if defined(GD_IDE_ONLY)
    virtual void GetPropertyForDebugger (unsigned int propertyNb, std::string & name, std::string & value) const;
    virtual bool ChangeProperty(unsigned int propertyNb, std::string newValue);
    virtual unsigned int GetNumberOfProperties() const;
    #endif

private:
    TextBox m_textBox;
    std::string fontName;

    const RuntimeScene *m_scene;
};

void DestroyTextBoxObject(gd::Object * object);
gd::Object * CreateTextBoxObject(std::string name);

void DestroyRuntimeTextBoxObject(RuntimeObject * object);
RuntimeObject * CreateRuntimeTextBoxObject(RuntimeScene & scene, const gd::Object & object);

#endif // TextBoxObject_H

