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
                              _("Provides an object to allow the user to enter and edit a line of text."),
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

            obj.AddAction("String",
                           _("Modify the text"),
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
                           _("Test the text"),
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

            obj.AddAction("Font",
                           _("Font"),
                           _("Modify the font of the text."),
                           _("Change font of _PARAM0_ to _PARAM1_"),
                           _("Font"),
                           "res/actions/font24.png",
                           "res/actions/font.png")
                .AddParameter("object", _("Object"), "TextBox", false)
                .AddParameter("police", _("Font"))
                .codeExtraInformation.SetFunctionName("ChangeFont").SetIncludeFile("TextBoxObject/TextBoxObject.h");

            obj.AddAction("Size",
                           _("Size"),
                           _("Modify the size of the text."),
                           _("Do _PARAM1__PARAM2_ to the size of the text of _PARAM0_"),
                           _("Size"),
                           "res/actions/characterSize24.png",
                           "res/actions/characterSize.png")
                .AddParameter("object", _("Object"), "TextBox", false)
                .AddParameter("operator", _("Modification's sign"))
                .AddParameter("expression", _("Value"))
                .codeExtraInformation.SetFunctionName("SetCharacterSize").SetManipulatedType("number").SetAssociatedGetter("GetCharacterSize").SetIncludeFile("TextBoxObject/TextBoxObject.h");

            obj.AddCondition("Size",
                           _("Size"),
                           _("Test the size of the text"),
                           _("The size of the text of _PARAM0_ is _PARAM1__PARAM2_"),
                           _("Size"),
                           "res/conditions/characterSize24.png",
                           "res/conditions/characterSize.png")
                .AddParameter("object", _("Object"), "TextBox", false)
                .AddParameter("relationalOperator", _("Sign of the test"))
                .AddParameter("expression", _("Size to test"))
                .codeExtraInformation.SetFunctionName("GetCharacterSize").SetManipulatedType("number").SetIncludeFile("TextBoxObject/TextBoxObject.h");

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

        //supplementaryIncludeDirectories.push_back("CppPlatform/Extensions/include/WidgetsCommon");
        supplementaryLibFiles.push_back("libWidgetsCore.dll.a");
        supplementaryLibFiles.push_back("libSFWidgets.a");

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
