#pragma once

#include <windhawk_utils.h>
#include <string>
#include <mutex>
#include <atomic>
#include <algorithm>

enum class ScalingMode {
    Contain,   // Fit within bounds preserving aspect ratio
    Cover,     // Fill bounds preserving aspect ratio
    Stretch,   // Stretch to fill exact bounds
    Original,  // Centered at original size
};

enum class HoverEffect {
    None,
    Brightness,
    Scale,
    Opacity,
};

enum class PressedEffect {
    None,
    Scale,
    Opacity,
};

struct ModSettings {
    std::wstring imagePath;
    bool enableCustomImage = true;
    ScalingMode scalingMode = ScalingMode::Contain;
    int customWidth = 0;
    int customHeight = 0;
    int borderRadius = 0;  // 0% to 50%
    HoverEffect hoverEffect = HoverEffect::Brightness;
    int hoverScale = 105;
    int hoverBrightness = 15;
    int hoverOpacity = 100;
    PressedEffect pressedEffect = PressedEffect::Scale;
    int pressedScale = 95;
    bool enableAnimation = true;
    int animationDuration = 120;
    bool useAlphaChannel = true;
    std::wstring customTooltip;
    bool applyToSecondaryTaskbars = true;
    bool fallbackToDefault = true;
};

class ConfigManager {
public:
    static void LoadSettings();
    static ModSettings GetSettings();

private:
    static ModSettings s_settings;
    static std::mutex s_mutex;
    static std::atomic<uint64_t> s_generation;
};
