#include "pch.h"
#include "ApplicationEvent.h"

namespace as3d
{
    WindowResizeEvent::WindowResizeEvent(int width, int height)
        :width(width), height(height)
    {}
}