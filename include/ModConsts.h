#pragma once
#include "ForwardDefinitions.h"
#include "Lunacy.hpp"
#include "Graphics.h"

using namespace Sexy;

namespace HookTypes {
    typedef void(__stdcall* DrawCYS)(Graphics* g);
    typedef void(__stdcall* DrawPlant)(Plant* plant, Graphics* g);
}

namespace HookPoints {
    void** DrawSeedChooserScreen = reinterpret_cast<void**>(0x484690);
    void** DrawPlant = reinterpret_cast<void**>(0x465a90); 
}
