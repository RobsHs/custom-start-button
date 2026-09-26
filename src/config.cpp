#include "config.h"

ModSettings ConfigManager::s_settings;
std::mutex ConfigManager::s_mutex;
std::atomic<uint64_t> ConfigManager::s_generation{0};

static std::wstring GetStringSettingSafe(const wchar_t* name) {
    auto value = WindhawkUtils::StringSetting::make(name);
    return value.get() ? value.get() : L"";
}

void ConfigManager::LoadSettings() {
    ModSettings s;
    s.imagePath = GetStringSettingSafe(L"imagePath");
    s.enableCustomImage = Wh_GetIntSetting(L"enableCustomImage") != 0;

    std::wstring mode = GetStringSettingSafe(L"scalingMode");
    if (_wcsicmp(mode.c_str(), L"cover") == 0) {
        s.scalingMode = ScalingMode::Cover;
    } else if (_wcsicmp(mode.c_str(), L"stretch") == 0) {
        s.scalingMode = ScalingMode::Stretch;
    } else if (_wcsicmp(mode.c_str(), L"original") == 0) {
        s.scalingMode = ScalingMode::Original;
    } else {
        s.scalingMode = ScalingMode::Contain;
    }

    s.customWidth = std::clamp(Wh_GetIntSetting(L"customWidth"), 0, 256);
    s.customHeight = std::clamp(Wh_GetIntSetting(L"customHeight"), 0, 256);
    s.borderRadius = std::clamp(Wh_GetIntSetting(L"borderRadius"), 0, 50);

    std::wstring hover = GetStringSettingSafe(L"hoverEffect");
    if (_wcsicmp(hover.c_str(), L"none") == 0) {
        s.hoverEffect = HoverEffect::None;
    } else if (_wcsicmp(hover.c_str(), L"scale") == 0) {
        s.hoverEffect = HoverEffect::Scale;
    } else if (_wcsicmp(hover.c_str(), L"opacity") == 0) {
        s.hoverEffect = HoverEffect::Opacity;
    } else {
        s.hoverEffect = HoverEffect::Brightness;
    }

    s.hoverScale = std::clamp(Wh_GetIntSetting(L"hoverScale"), 100, 200);
    s.hoverBrightness = std::clamp(Wh_GetIntSetting(L"hoverBrightness"), -100, 100);
    s.hoverOpacity = std::clamp(Wh_GetIntSetting(L"hoverOpacity"), 0, 100);

    std::wstring pressed = GetStringSettingSafe(L"pressedEffect");
    if (_wcsicmp(pressed.c_str(), L"none") == 0) {
        s.pressedEffect = PressedEffect::None;
    } else if (_wcsicmp(pressed.c_str(), L"opacity") == 0) {
        s.pressedEffect = PressedEffect::Opacity;
    } else {
        s.pressedEffect = PressedEffect::Scale;
    }

    s.pressedScale = std::clamp(Wh_GetIntSetting(L"pressedScale"), 50, 100);
    s.enableAnimation = Wh_GetIntSetting(L"enableAnimation") != 0;
    s.animationDuration = std::clamp(Wh_GetIntSetting(L"animationDuration"), 50, 1000);
    s.useAlphaChannel = Wh_GetIntSetting(L"useAlphaChannel") != 0;
    s.customTooltip = GetStringSettingSafe(L"customTooltip");
    s.applyToSecondaryTaskbars = Wh_GetIntSetting(L"applyToSecondaryTaskbars") != 0;
    s.fallbackToDefault = Wh_GetIntSetting(L"fallbackToDefault") != 0;

    std::lock_guard<std::mutex> lock(s_mutex);
    s_settings = std::move(s);
    s_generation.fetch_add(1, std::memory_order_relaxed);
}

ModSettings ConfigManager::GetSettings() {
    std::lock_guard<std::mutex> lock(s_mutex);
    return s_settings;
}
