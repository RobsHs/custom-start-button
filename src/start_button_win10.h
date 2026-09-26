#pragma once

#include <windows.h>

namespace Win10Subsystem {

void EnsureGdiplusInitialized();
void EnsureGdiplusShutdown();
void EnumerateAndSubclassTaskbars();
void EnumerateAndDetachTaskbars();

}  // namespace Win10Subsystem
