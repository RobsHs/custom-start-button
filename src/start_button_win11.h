#pragma once

#include <windows.h>

namespace Win11Subsystem {

bool HookTaskbarDllSymbols();
bool HookTaskbarViewSymbols(HMODULE module);
void ApplySettingsFromTaskbarThread();
void DetachAllInstances();

}  // namespace Win11Subsystem
