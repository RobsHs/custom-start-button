#include "windows_compat.h"

namespace WindowsCompat {

DWORD GetBuildNumber() {
    // Read build number directly from shared user data for maximum reliability
    const auto* sharedUserData = reinterpret_cast<const BYTE*>(0x7FFE0000);
    return *reinterpret_cast<const DWORD*>(sharedUserData + 0x0260);
}

bool IsWindows11OrGreater() {
    return GetBuildNumber() >= 22000;
}

}  // namespace WindowsCompat
