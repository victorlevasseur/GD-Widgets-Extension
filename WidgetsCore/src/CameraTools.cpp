#include "WidgetsCore/CameraTools.h"

#include <iostream>
#include "GDCpp/Project.h"

namespace WCore
{

sf::Vector2f MapPixelsToCoords(sf::Vector2i position, const std::string &layer, const RuntimeScene &scene_)
{
    RuntimeScene &scene = const_cast<RuntimeScene&>(scene_);

    if(position.x < 0 || position.y < 0 || position.x > scene.game->GetMainWindowDefaultWidth() || position.y > scene.game->GetMainWindowDefaultHeight())
        return sf::Vector2f(position.x, position.y);

    int camerasNumber = scene.GetRuntimeLayer(layer).GetCameraCount();
    sf::Vector2f newPos = sf::Vector2f(position.x, position.y);

    for(int a = 0; a < camerasNumber; a++)
    {
        sf::IntRect rect((float)scene.GetRuntimeLayer(layer).GetCamera(a).GetSFMLView().getViewport().left * (float)scene.game->GetMainWindowDefaultWidth(),
                         (float)scene.GetRuntimeLayer(layer).GetCamera(a).GetSFMLView().getViewport().top * (float)scene.game->GetMainWindowDefaultHeight(),
                         (float)scene.GetRuntimeLayer(layer).GetCamera(a).GetSFMLView().getViewport().width * (float)scene.game->GetMainWindowDefaultWidth(),
                         (float)scene.GetRuntimeLayer(layer).GetCamera(a).GetSFMLView().getViewport().height * (float)scene.game->GetMainWindowDefaultHeight());

        if(rect.contains(position))
        {
            newPos = scene.renderWindow->convertCoords(position, scene.GetRuntimeLayer(layer).GetCamera(a).GetSFMLView());
            break;
        }
    }

    return newPos;
}

}
