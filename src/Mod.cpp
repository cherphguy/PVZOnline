#include "Mod.h"
#include "Hooks.h"

void Mod::InitializeMod() {
	logger = Logger::ConsoleLogger();
	logger.log(LogLevel::info, "Mod Initialized");
	InitializeHooks();
	InitializeCYSPatch();
}
