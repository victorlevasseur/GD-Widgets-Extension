rem TextBoxObject
xcopy "E:\Developpement\Projets\Game Develop\GDSDK\Extensions\Widgets\TextBoxObject\*.h" "E:\Developpement\Projets\Game Develop\GDSDK\Binaries\Output\Release\CppPlatform\Extensions\include\TextBoxObject"

rem WidgetsCore
xcopy "E:\Developpement\Projets\Game Develop\GDSDK\Extensions\Widgets\WidgetsCore\include\WidgetsCore\*.h" "E:\Developpement\Projets\Game Develop\GDSDK\Binaries\Output\Release\CppPlatform\Extensions\include\WidgetsCore"

copy "E:\Developpement\Projets\Game Develop\GDSDK\Binaries\Output\Release\WidgetsCore.dll" "E:\Developpement\Projets\Game Develop\GDSDK\Binaries\Output\Release\CppPlatform\Extensions\WidgetsCore.dll"
copy "E:\Developpement\Projets\Game Develop\GDSDK\Binaries\Output\Release\libWidgetsCore.dll.a" "E:\Developpement\Projets\Game Develop\GDSDK\Binaries\Output\Release\CppPlatform\Extensions\libWidgetsCore.dll.a"

rem Resources
copy "E:\Developpement\Projets\Game Develop\GDSDK\Extensions\Widgets\TextBoxObject\TextBox.png" "E:\Developpement\Projets\Game Develop\GDSDK\Binaries\Output\Release\CppPlatform\Extensions\TextBox.png"
copy "E:\Developpement\Projets\Game Develop\GDSDK\Extensions\Widgets\TextBoxObject\TextBox24.png" "E:\Developpement\Projets\Game Develop\GDSDK\Binaries\Output\Release\CppPlatform\Extensions\TextBox24.png"

rem Translations
xcopy "E:\Developpement\Projets\Game Develop\GDSDK\Extensions\Widgets\Translations\fr_FR\*.mo" "E:\Developpement\Projets\Game Develop\GDSDK\Binaries\Output\Release\locale\fr_FR"

pause