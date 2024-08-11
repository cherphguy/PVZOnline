#include <windows.h>
#include "Windows.h"
#include "format"
#include <iostream>
#include "MinHook.h"
#include "Graphics.h"
#include "CGeometry.h"
#include "Plant.h"
#include "Listeners.h"
#include "ModConsts.h"
#include "DialogButton.h"
#include "Hooks.h"
#include "Utils.h"
#include "SeedChooserScreen.h"
using namespace Sexy;
const Rect cSeedClipRect = Rect(0, 119, 800, 426);

HookManager manager;

template <typename T>
void SetRect(Rect<T> ogRect, Rect<T> &newRect) {
    newRect.mX = ogRect.mX;
    newRect.mY = ogRect.mY;
    newRect.mW = ogRect.mW;
    newRect.mH = ogRect.mH;
}

class EldedListener : public ButtonListener {
public:
    virtual void __thiscall ButtonClick(int ID, int ClickType) override {
        std::cout << "HElo World!!!!!";
    };
    
    virtual void __thiscall ButtonPress(int ID) override {
        std::cout << "HeeElo World!!!!!";
    };
    virtual  void __thiscall  ButtonDepress(int ID) override {
        std::cout << "HElo World!!!!!";
    };
    virtual  void __thiscall ButtonDownTick(int ID) override {
        std::cout << "DOwn tck!!!!!";
    };
    virtual  void __thiscall ButtonMouseEnter(int ID) override {
        std::cout << "Mouse enter!!!!!";
    };
    virtual  void __thiscall ButtonMouseLeave(int ID) override {
        std::cout << "Mouse leave!!!!!";
    };
    virtual  void __thiscall ButtonMouseMove(int ID, int X, int Y) override {
        std::cout << std::format("Mouse Move!!!!! {} {}", X, Y) ;
    };
};

LawnStoneButton* btn;
typedef void(__stdcall* DrawPlant)(Plant* plant, Graphics* g);
DrawPlant drawPlant = nullptr;
DrawPlant DrawPlantTarget = reinterpret_cast<DrawPlant>(0x465a90);

void __stdcall DetourDrawCYS(Graphics* g) {
    SeedChooserScreen* cys;
    __asm mov cys, ecx;
    Lawn* lawn = cys->mBoard;
    g->mLinearBlend = true;
    if (!btn) {
        btn = LawnStoneButton::New(14, new EldedListener(), "COOP");
    }

    if (!btn->mParent) {
        btn->mBounds.mX = 200;
        btn->mBounds.mY = 100;
        btn->mBounds.mW = 200;
        btn->ResizeToFit();
        cys->AddChild(btn);
    };
    __asm mov ecx, cys;
    auto drawCYSEV = HookManager::GetOriginalFunction<HookTypes::DrawCYS>(HookPoints::DrawSeedChooserScreen);
    if (drawCYSEV.has_value()) {
        return drawCYSEV.value()(g);
    } else {
        HandleMinHookError(
            drawCYSEV.error()
        );
    }
}

void __stdcall DetourDrawPlant(Plant* plant, Graphics* g) {
    
    auto string = std::format("{}/{}", plant->mHealth, plant->mMaxHealth);
    g->DrawString(string, 69, 69);

    drawPlant(plant, g);
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    if (ul_reason_for_call != DLL_PROCESS_ATTACH) return TRUE;
    AllocConsole();

    FILE* O = nullptr;
    freopen_s(&O, "CONOUT$", "w", stdout);

    SetConsoleTitleA("PVZOnline");

    std::cout << "Mod Initialized" << "\n";

    HandleMinHookError(manager.Initialize());
    HandleMinHookError(
        manager.CreateHook(HookPoints::DrawSeedChooserScreen, &DetourDrawCYS)
    );

    HandleMinHookError(
        manager.CreateHook(HookPoints::DrawPlant, &DetourDrawPlant)
    );

   

    return TRUE;
};