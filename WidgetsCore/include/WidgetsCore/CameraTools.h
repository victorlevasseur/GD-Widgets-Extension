#ifndef WCORE_CAMERATOOLS_H
#define WCORE_CAMERATOOLS_H

#include "WidgetsCore/Defs.h"

#include "GDCpp/RuntimeLayer.h"
#include "GDCpp/RuntimeScene.h"
#include "GDCpp/RuntimeGame.h"

namespace WCore
{

sf::Vector2f WIDGETS_CORE_API MapPixelsToCoords(sf::Vector2i pos, const std::string &layer, const RuntimeScene &scene_);

}

#endif // WCORE_CAMERATOOLS_H
