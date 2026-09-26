#pragma once

#include <windows.h>
#include <string>

namespace ImageLoader {

std::wstring ExpandPath(const std::wstring& source);
bool FileExists(const std::wstring& path);
std::wstring MakeFileUri(const std::wstring& rawPath);

}  // namespace ImageLoader
