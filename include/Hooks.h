#pragma once
#include "Mod.h"
#include "MinHook.h"
#include "Graphics.h"

typedef void(__stdcall* DrawSeedChooser)(Sexy::Graphics* g);
DrawSeedChooser pDrawSeedChooser = nullptr;
DrawSeedChooser pDrawSeedChooserTarget = reinterpret_cast<DrawSeedChooser>(0x484690);

void __stdcall DetourDrawSeedChooserScreen(Sexy::Graphics* g) {
	g->DrawString("Hello World!!!!!!", 69, 69);
}

void HandleMinHookError(const char* string, MH_STATUS status) {
	if (status != MH_OK) {
		const char* StatusAsString = MH_StatusToString(status);
		Mod::logger.log(LogLevel::error, string, StatusAsString);
	}
}

void InitializeHooks() {
	MH_STATUS MinHookInitializationStatus = MH_Initialize();
	return HandleMinHookError("Error Occured While Initializing MinHook: ", MinHookInitializationStatus);

}

void InitializeCYSPatch() {
	MH_STATUS InitializeCYSPatchStatus = MH_CreateHook(reinterpret_cast<void**>(pDrawSeedChooserTarget), &DetourDrawSeedChooserScreen, reinterpret_cast<void**>(&pDrawSeedChooser));
	return HandleMinHookError("Error Occured While Initializing Draw SeedChooser Patch: ", InitializeCYSPatchStatus);
}