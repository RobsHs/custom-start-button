#pragma once

#include <windows.h>

namespace WindowsCompat {

DWORD GetBuildNumber();
bool IsWindows11OrGreater();

}  // namespace WindowsCompat
