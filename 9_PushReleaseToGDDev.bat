rem TextBoxObject
xcopy "E:\Developpement\Projets\Game Develop\GDSDK\Extensions\Widgets\TextBoxObject\*.h" "E:\Developpement\Projets\Game Develop\GDSDK\Binaries\Output\Release\CppPlatform\Extensions\include\TextBoxObject"

rem WidgetsCore
rem xcopy "E:\Developpement\Projets\Game Develop\GDSDK\Extensions\Widgets\WidgetsCore\include\WidgetsCore\*.h" "E:\Developpement\Projets\Game Develop\GDSDK\Binaries\Output\Release\CppPlatform\Extensions\include\WidgetsCommon\WidgetsCore"
xcopy "E:\Developpement\Projets\Game Develop\GDSDK\Extensions\Widgets\WidgetsCore\include\WidgetsCore\*.h" "E:\Developpement\Projets\Game Develop\GDSDK\Binaries\Output\Release\CppPlatform\include\GDCpp\WidgetsCore"

copy "E:\Developpement\Projets\Game Develop\GDSDK\Binaries\Output\Release\WidgetsCore.dll" "E:\Developpement\Projets\Game Develop\GDSDK\Binaries\Output\Release\CppPlatform\Extensions\WidgetsCore.dll"
copy "E:\Developpement\Projets\Game Develop\GDSDK\Binaries\Output\Release\libWidgetsCore.dll.a" "E:\Developpement\Projets\Game Develop\GDSDK\Binaries\Output\Release\CppPlatform\Extensions\libWidgetsCore.dll.a"

pause