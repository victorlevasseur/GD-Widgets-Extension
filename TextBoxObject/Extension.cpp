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

#include "GDCpp/ExtensionBase.h"
#include "GDCore/PlatformDefinition/PlatformExtension.h"
#include "GDCore/Tools/Version.h"

#include "TextBoxObject.h"
#include <boost/version.hpp>

/**
 * \brief This class declares information about the C++ extension.
 */
class CppExtension : public ExtensionBase
{
public:

    /**
     * Constructor of an extension declares everything the extension contains : Objects, actions, conditions and expressions.
     */
    CppExtension()
    {
        SetExtensionInformation("TextBoxObject",
                              _("Widgets - TextBox object"),
                              _("Part of the Widgets extension.\nProvides an object to allow the user to enter and edit a line of text."),
                              "Victor Levasseur",
                              "zlib/libpng License ( Open Source )");


        //Declaration of all objects available
        {
            gd::ObjectMetadata & obj = AddObject("TextBox",
                       _("Text Box"),
                       _("Allows the user to edit a text"),
                       "CppPlatform/Extensions/TextBox.png",
                       &CreateTextBoxObject,
                       &DestroyTextBoxObject);

            AddRuntimeObject(obj, "RuntimeTextBoxObject", CreateRuntimeTextBoxObject, DestroyRuntimeTextBoxObject);

            #if defined(GD_IDE_ONLY)

            obj.SetIncludeFile("TextBoxObject/TextBoxObject.h");

            /** String **/

            obj.AddAction("String",
                           _("Text"),
                           _("Modify the text of a Text Box object."),
                           _("Do _PARAM1__PARAM2_ to the text of _PARAM0_"),
                           _("Text"),
                           "res/actions/text24.png",
                           "res/actions/text.png")
                .AddParameter("object", _("Object"), "TextBox", false)
                .AddParameter("operator", _("Modification's sign"))
                .AddParameter("string", _("Text"))
                .codeExtraInformation.SetFunctionName("SetString").SetManipulatedType("string").SetAssociatedGetter("GetString").SetIncludeFile("TextBoxObject/TextBoxObject.h");

            obj.AddCondition("String",
                           _("Text"),
                           _("Test the text of a Text Box object."),
                           _("The text of _PARAM0_ is _PARAM1__PARAM2_"),
                           _("Text"),
                           "res/conditions/text24.png",
                           "res/conditions/text.png")
                .AddParameter("object", _("Object"), "TextBox", false)
                .AddParameter("relationalOperator", _("Sign of the test"))
                .AddParameter("string", _("Text to test"))
                .codeExtraInformation.SetFunctionName("GetString").SetManipulatedType("string").SetIncludeFile("TextBoxObject/TextBoxObject.h");

            obj.AddStrExpression("String", _("Text"), _("Text"), _("Text"), "res/texteicon.png")
                .AddParameter("object", _("Object"), "TextBox", false)
                .codeExtraInformation.SetFunctionName("GetString").SetIncludeFile("TextBoxObject/TextBoxObject.h");

            /** Hide Character **/

            obj.AddAction("HideCharacter",
                           _("Hide Character"),
                           _("Modify the hide character (character hiding the text) of a Text Box object.\nPut an empty hide character to disable it."),
                           _("Set _PARAM1_ as the hide character of _PARAM0_"),
                           _("Text"),
                           "res/actions/text24.png",
                           "res/actions/text.png")
                .AddParameter("object", _("Object"), "TextBox", false)
                .AddParameter("string", _("Hide character"))
                .codeExtraInformation.SetFunctionName("SetHideCharacter").SetIncludeFile("TextBoxObject/TextBoxObject.h");

            obj.AddCondition("HideCharacter",
                           _("Hide Character"),
                           _("Test the hide character (character hiding the text) of a Text Box object."),
                           _("The hide character of _PARAM0_ is _PARAM1__PARAM2_"),
                           _("Text"),
                           "res/conditions/text24.png",
                           "res/conditions/text.png")
                .AddParameter("object", _("Object"), "TextBox", false)
                .AddParameter("relationalOperator", _("Sign of the test"))
                .AddParameter("string", _("Hide character to test"))
                .codeExtraInformation.SetFunctionName("GetHideCharacter").SetManipulatedType("string").SetIncludeFile("TextBoxObject/TextBoxObject.h");

            obj.AddStrExpression("HideCharacter", _("Hide character"), _("Hide character (character hiding the string in the Text Box)"), _("Text"), "res/texteicon.png")
                .AddParameter("object", _("Object"), "TextBox", false)
                .codeExtraInformation.SetFunctionName("GetHideCharacter").SetIncludeFile("TextBoxObject/TextBoxObject.h");

            /** Placeholder **/

            obj.AddAction("Placeholder",
                           _("Placeholder"),
                           _("Modify the placeholder (text shown when there is no text) of a Text Box object."),
                           _("Do _PARAM1__PARAM2_ to the placeholder of _PARAM0_"),
                           _("Text"),
                           "res/actions/text24.png",
                           "res/actions/text.png")
                .AddParameter("object", _("Object"), "TextBox", false)
                .AddParameter("operator", _("Modification's sign"))
                .AddParameter("string", _("Placeholder"))
                .codeExtraInformation.SetFunctionName("SetPlaceholder").SetManipulatedType("string").SetAssociatedGetter("GetPlaceholder").SetIncludeFile("TextBoxObject/TextBoxObject.h");

            obj.AddCondition("Placeholder",
                           _("Placeholder"),
                           _("Test the placeholder (text shown when there is no text) of a Text Box object."),
                           _("The placeholder of _PARAM0_ is _PARAM1__PARAM2_"),
                           _("Text"),
                           "res/conditions/text24.png",
                           "res/conditions/text.png")
                .AddParameter("object", _("Object"), "TextBox", false)
                .AddParameter("relationalOperator", _("Sign of the test"))
                .AddParameter("string", _("Placeholder to test"))
                .codeExtraInformation.SetFunctionName("GetPlaceholder").SetManipulatedType("string").SetIncludeFile("TextBoxObject/TextBoxObject.h");

            obj.AddStrExpression("Placeholder", _("Placeholder"), _("Placeholder (text shown when the Text Box is empty)"), _("Text"), "res/texteicon.png")
                .AddParameter("object", _("Object"), "TextBox", false)
                .codeExtraInformation.SetFunctionName("GetPlaceholder").SetIncludeFile("TextBoxObject/TextBoxObject.h");

            /** Allow Text Selection **/

            obj.AddAction("AllowTextSelection",
                           _("Enable/disable text selection"),
                           _("Enable or disable the text selection.\nIf disabled, you can move the cursor but can't select a text by dragging."),
                           _("Enable the text selection of _PARAM0_ ? _PARAM1_"),
                           _("Selection/Cursor"),
                           "res/actions/text24.png",
                           "res/actions/text.png")
                .AddParameter("object", _("Object"), "TextBox", false)
                .AddParameter("yesorno", _("Enable ?"))
                .codeExtraInformation.SetFunctionName("AllowTextSelection").SetIncludeFile("TextBoxObject/TextBoxObject.h");

            obj.AddCondition("AllowTextSelection",
                           _("Text selection enabled"),
                           _("Test if the text selection is enabled"),
                           _("The text selection of _PARAM0_ is enabled"),
                           _("Selection/Cursor"),
                           "res/conditions/text24.png",
                           "res/conditions/text.png")
                .AddParameter("object", _("Object"), "TextBox", false)
                .codeExtraInformation.SetFunctionName("IsAllowingTextSelection").SetIncludeFile("TextBoxObject/TextBoxObject.h");

            /** Enable/Disable **/

            obj.AddAction("Enable",
                           _("Enable/Disable"),
                           _("Enable or disable the text box object."),
                           _("Enable _PARAM0_ ? _PARAM1_"),
                           _("State"),
                           "res/actions/text24.png",
                           "res/actions/text.png")
                .AddParameter("object", _("Object"), "TextBox", false)
                .AddParameter("yesorno", _("Enable ?"))
                .codeExtraInformation.SetFunctionName("Enable").SetIncludeFile("TextBoxObject/TextBoxObject.h");

            obj.AddCondition("IsEnabled",
                           _("Enabled"),
                           _("Test if the text object is enabled"),
                           _("_PARAM0_ is enabled"),
                           _("State"),
                           "res/conditions/text24.png",
                           "res/conditions/text.png")
                .AddParameter("object", _("Object"), "TextBox", false)
                .codeExtraInformation.SetFunctionName("IsEnabled").SetIncludeFile("TextBoxObject/TextBoxObject.h");

            /** Read-only **/

            obj.AddAction("ReadOnly",
                           _("Read-only"),
                           _("Set if the user can edit the text (read-only)."),
                           _("Set _PARAM0_ read-only ? _PARAM1_"),
                           _("State"),
                           "res/actions/text24.png",
                           "res/actions/text.png")
                .AddParameter("object", _("Object"), "TextBox", false)
                .AddParameter("yesorno", _("Enable ?"))
                .codeExtraInformation.SetFunctionName("SetReadOnly").SetIncludeFile("TextBoxObject/TextBoxObject.h");

            obj.AddCondition("IsReadOnly",
                           _("Read-only"),
                           _("Test if the text can be edited by the user."),
                           _("_PARAM0_ is read-only"),
                           _("State"),
                           "res/conditions/text24.png",
                           "res/conditions/text.png")
                .AddParameter("object", _("Object"), "TextBox", false)
                .codeExtraInformation.SetFunctionName("IsReadOnly").SetIncludeFile("TextBoxObject/TextBoxObject.h");

            /** Selected String **/

            obj.AddCondition("SelectedString",
                           _("Selected text"),
                           _("Test the selected text of a Text Box object."),
                           _("The selected text of _PARAM0_ is _PARAM1__PARAM2_"),
                           _("Selection/Cursor"),
                           "res/conditions/text24.png",
                           "res/conditions/text.png")
                .AddParameter("object", _("Object"), "TextBox", false)
                .AddParameter("relationalOperator", _("Sign of the test"))
                .AddParameter("string", _("Text to test"))
                .codeExtraInformation.SetFunctionName("GetSelectedString").SetManipulatedType("string").SetIncludeFile("TextBoxObject/TextBoxObject.h");

            obj.AddStrExpression("SelectedString", _("Selected text"), _("Selected text"), _("Selection/Cursor"), "res/texteicon.png")
                .AddParameter("object", _("Object"), "TextBox", false)
                .codeExtraInformation.SetFunctionName("GetSelectedString").SetIncludeFile("TextBoxObject/TextBoxObject.h");

            /** Selection **/

            obj.AddAction("MoveCursor",
                           _("Move the cursor"),
                           _("Move the cursor at a specific position."),
                           _("Move the cursor of _PARAM0_ to _PARAM1_"),
                           _("Selection/Cursor"),
                           "res/actions/text24.png",
                           "res/actions/text.png")
                .AddParameter("object", _("Object"), "TextBox", false)
                .AddParameter("expression", _("Position"))
                .codeExtraInformation.SetFunctionName("Select").SetIncludeFile("TextBoxObject/TextBoxObject.h");

            obj.AddAction("ChangeSelection",
                           _("Change the selection position"),
                           _("Change the selection position (beginning and ending)."),
                           _("Set the selection of _PARAM0_ from _PARAM1_ to _PARAM2_"),
                           _("Selection/Cursor"),
                           "res/actions/text24.png",
                           "res/actions/text.png")
                .AddParameter("object", _("Object"), "TextBox", false)
                .AddParameter("expression", _("Begin position"))
                .AddParameter("expression", _("End position"))
                .codeExtraInformation.SetFunctionName("Select").SetIncludeFile("TextBoxObject/TextBoxObject.h");

            obj.AddExpression("SelectionBegin", _("Selection begin"), _("Selected begin position"), _("Selection/Cursor"), "res/texteicon.png")
                .AddParameter("object", _("Object"), "TextBox", false)
                .codeExtraInformation.SetFunctionName("GetSelectionBegin").SetIncludeFile("TextBoxObject/TextBoxObject.h");

            obj.AddExpression("SelectionEnd", _("Selection end"), _("Selected end position"), _("Selection/Cursor"), "res/texteicon.png")
                .AddParameter("object", _("Object"), "TextBox", false)
                .codeExtraInformation.SetFunctionName("GetSelectionEnd").SetIncludeFile("TextBoxObject/TextBoxObject.h");

            /** Font **/

            obj.AddAction("Font",
                           _("Font"),
                           _("Modify the font of a Text Box object."),
                           _("Change text font of _PARAM0_ to _PARAM1_"),
                           _("Font"),
                           "res/actions/font24.png",
                           "res/actions/font.png")
                .AddParameter("object", _("Object"), "TextBox", false)
                .AddParameter("police", _("Font"))
                .codeExtraInformation.SetFunctionName("ChangeFont").SetIncludeFile("TextBoxObject/TextBoxObject.h");

            /** Character size **/

            obj.AddAction("Size",
                           _("Font size"),
                           _("Modify the font size of a Text Box object."),
                           _("Do _PARAM1__PARAM2_ to the font size of _PARAM0_"),
                           _("Font"),
                           "res/actions/characterSize24.png",
                           "res/actions/characterSize.png")
                .AddParameter("object", _("Object"), "TextBox", false)
                .AddParameter("operator", _("Modification's sign"))
                .AddParameter("expression", _("Value"))
                .codeExtraInformation.SetFunctionName("SetCharacterSize").SetManipulatedType("number").SetAssociatedGetter("GetCharacterSize").SetIncludeFile("TextBoxObject/TextBoxObject.h");

            obj.AddCondition("Size",
                           _("Font size"),
                           _("Test the font size of a Text Box object."),
                           _("The font size of _PARAM0_ is _PARAM1__PARAM2_"),
                           _("Font"),
                           "res/conditions/characterSize24.png",
                           "res/conditions/characterSize.png")
                .AddParameter("object", _("Object"), "TextBox", false)
                .AddParameter("relationalOperator", _("Sign of the test"))
                .AddParameter("expression", _("Size to test"))
                .codeExtraInformation.SetFunctionName("GetCharacterSize").SetManipulatedType("number").SetIncludeFile("TextBoxObject/TextBoxObject.h");

            /** Angle **/

            obj.AddAction("Angle",
                           _("Angle"),
                           _("Modify the angle of a Text Box object."),
                           _("Do _PARAM1__PARAM2_ to the angle of _PARAM0_"),
                           _("Rotation"),
                           "res/actions/rotate24.png",
                           "res/actions/rotate.png")
                .AddParameter("object", _("Object"), "TextBox", false)
                .AddParameter("operator", _("Modification's sign"))
                .AddParameter("expression", _("Value"))
                .codeExtraInformation.SetFunctionName("SetAngle").SetManipulatedType("number").SetAssociatedGetter("GetAngle").SetIncludeFile("TextBoxObject/TextBoxObject.h");

            obj.AddCondition("Angle",
                           _("Angle"),
                           _("Test the value of the angle of a Text Box object."),
                           _("The angle of _PARAM0_ is _PARAM1__PARAM2_"),
                           _("Rotation"),
                           "res/conditions/rotate24.png",
                           "res/conditions/rotate.png")
                .AddParameter("object", _("Object"), "TextBox", false)
                .AddParameter("relationalOperator", _("Sign of the test"))
                .AddParameter("expression", _("Value to test"))
                .codeExtraInformation.SetFunctionName("GetAngle").SetManipulatedType("number").SetIncludeFile("TextBoxObject/TextBoxObject.h");

            obj.AddExpression("Angle", _("Angle"), _("Angle"), _("Rotation"), "res/actions/rotate.png")
                .AddParameter("object", _("Object"), "TextBox", false)
                .codeExtraInformation.SetFunctionName("GetAngle").SetIncludeFile("TextBoxObject/TextBoxObject.h");

        #endif
        }

        GD_COMPLETE_EXTENSION_COMPILATION_INFORMATION();

        #if defined(GD_IDE_ONLY)
        supplementaryLibFiles.push_back("libWidgetsCore.dll.a");
        supplementaryRuntimeFiles.push_back(std::pair<std::string, std::string>("Windows", "CppPlatform/Extensions/Runtime/WidgetsCore.dll"));

        #endif // defined
    };
    virtual ~CppExtension() {};
};

/**
 * Used by Game Develop to create the extension class
 * -- Do not need to be modified. --
 */
extern "C" ExtensionBase * GD_EXTENSION_API CreateGDExtension() {
    return new CppExtension;
}

/**
 * Used by Game Develop to destroy the extension class
 * -- Do not need to be modified. --
 */
extern "C" void GD_EXTENSION_API DestroyGDExtension(ExtensionBase * p) {
    delete p;
}
