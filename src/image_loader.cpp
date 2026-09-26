#include "image_loader.h"

namespace ImageLoader {

std::wstring ExpandPath(const std::wstring& source) {
    if (source.empty()) {
        return L"";
    }

    DWORD required = ExpandEnvironmentStringsW(source.c_str(), nullptr, 0);
    if (!required) {
        return source;
    }

    std::wstring result(required, L'\0');
    DWORD written = ExpandEnvironmentStringsW(source.c_str(), result.data(), required);
    if (!written || written > required) {
        return source;
    }

    result.resize(written - 1);
    return result;
}

bool FileExists(const std::wstring& path) {
    if (path.empty()) {
        return false;
    }
    DWORD attribs = GetFileAttributesW(path.c_str());
    return (attribs != INVALID_FILE_ATTRIBUTES && !(attribs & FILE_ATTRIBUTE_DIRECTORY));
}

std::wstring MakeFileUri(const std::wstring& rawPath) {
    std::wstring path = ExpandPath(rawPath);
    if (path.empty()) {
        return L"";
    }

    if (_wcsnicmp(path.c_str(), L"http://", 7) == 0 ||
        _wcsnicmp(path.c_str(), L"https://", 8) == 0 ||
        _wcsnicmp(path.c_str(), L"file:///", 8) == 0) {
        return path;
    }

    std::wstring result;
    result.reserve(path.size() + 16);
    result = L"file:///";

    for (wchar_t c : path) {
        switch (c) {
            case L'\\':
                result += L'/';
                break;
            case L' ':
                result += L"%20";
                break;
            case L'#':
                result += L"%23";
                break;
            case L'%':
                result += L"%25";
                break;
            default:
                result += c;
                break;
        }
    }

    return result;
}

}  // namespace ImageLoader
