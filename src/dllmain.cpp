#include <windows.h>
#include "Windows.h"
#include <iostream>
#include "MinHook.h"
#include "Graphics.h"
#include "CGeometry.h"
#include "Plant.h"
#include "Listeners.h"
#include "DialogButton.h"
#include "SeedChooserScreen.h"
using namespace Sexy;
const Rect cSeedClipRect = Rect(0, 119, 800, 426);

class EldedListener : ButtonListener {
    virtual void __thiscall ButtonDepress() {
        std::cout << "HElo World!!!!!";
    };
};

EldedListener* elListener;
LawnStoneButton* btn;
const DWORD Getposx = 0x41c210;
typedef void(__stdcall* DrawCYS)(Graphics* g);
DrawCYS drawCYS = nullptr;
DrawCYS DrawCYSTarget = reinterpret_cast<DrawCYS>(0x484690);
typedef void(__stdcall* DrawPlant)(Plant* plant, Graphics* g);
DrawPlant drawPlant = nullptr;
DrawPlant DrawPlantTarget = reinterpret_cast<DrawPlant>(0x465a90);

void __stdcall DetourDrawCYS(Graphics* g) {
    SeedChooserScreen* cys;
    __asm mov cys, ecx;
    Lawn* lawn = cys->mBoard;
    g->mLinearBlend = true;
    if (!btn->mParent) {
        btn->mBounds.mX = 100;
        btn->mBounds.mY = 100;
        btn->ResizeToFit();
        btn->mParent = cys;
    };
    Image** image = (Image**)0x6a7460;
    Font** font = (Font**)0x6a79f4;
    g->mFont = *font;
    g->mColor = Color(255, 255, 0);
    g->DrawImage(*image, 0, 87);
    g->DrawString("Choose Your Plants", 129, 110);

    auto NumSeeds = lawn->mSeedBank->mNumPackets;
    for (int i = 0; NumSeeds > i; ++i) {
        int posx;
        __asm
        {
            mov eax, lawn
            mov edi, i
            call Getposx
            mov posx, eax
        }

        posx += lawn->mSeedBank->mX;
        posx -= cys->mBounds.mX;
        int posy = lawn->mSeedBank->mY - cys->mBounds.mY + 8;
        Image** img2 = reinterpret_cast<Image**>(0x6a72e8);

        g->DrawImage(*img2, posx, posy);
    }

}

void __stdcall DetourDrawPlant(Plant* plant, Graphics* g) {
    g->DrawString("Hello World", 69, 69);
    drawPlant(plant, g);
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    if (ul_reason_for_call != DLL_PROCESS_ATTACH) return TRUE;
    AllocConsole();

    btn = LawnStoneButton::New(1, (ButtonListener*)elListener, "Hello Elded");
    FILE* O = nullptr;
    freopen_s(&O, "CONOUT$", "w", stdout);

    SetConsoleTitleA("PVZOnline");

    std::cout << "Mod Initialized" << "\n";

    MH_Initialize();
    MH_CreateHook(reinterpret_cast<void**>(DrawCYSTarget), &DetourDrawCYS, reinterpret_cast<void**>(&drawCYS));
    MH_CreateHook(reinterpret_cast<void**>(DrawPlantTarget), &DetourDrawPlant, reinterpret_cast<void**>(&drawPlant));

    MH_EnableHook(MH_ALL_HOOKS);
    return TRUE;
};