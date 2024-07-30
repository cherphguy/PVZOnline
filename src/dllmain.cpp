#include <windows.h>
#include "Windows.h"
#include <iostream>
#include "MinHook.h"
#include "Graphics.h"

typedef void(__stdcall* DrawCYS)(Sexy::Graphics* g);
DrawCYS drawCYS = nullptr;
DrawCYS DrawCYSTarget = reinterpret_cast<DrawCYS>(0x484690);

typedef void(__stdcall* DrawPlant)(DWORD* plant, Sexy::Graphics* g);
DrawPlant drawPlant = nullptr;
DrawPlant DrawPlantTarget = reinterpret_cast<DrawPlant>(0x465a90);

void __stdcall DetourDrawCYS(Sexy::Graphics* g) {
    drawCYS(g);
    g->DrawString("Hello World", 69, 69);
}

void __stdcall DetourDrawPlant(DWORD* plant, Sexy::Graphics* g) {
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


    FILE* O = nullptr;
    freopen_s(&O, "CONOUT$", "w", stdout);

    SetConsoleTitleA("PVZOnline");

    std::cout << "Mod Initialized" << "\n";

    MH_Initialize();
    // MH_CreateHook(reinterpret_cast<void**>(DrawCYSTarget), &DetourDrawCYS, reinterpret_cast<void**>(&drawCYS));
    MH_CreateHook(reinterpret_cast<void**>(DrawPlantTarget), &DetourDrawPlant, reinterpret_cast<void**>(&drawPlant));

    MH_EnableHook(MH_ALL_HOOKS);
    return TRUE;
};