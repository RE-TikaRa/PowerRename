#include "pch.h"
#include "HomePage.xaml.h"
#if __has_include("HomePage.g.cpp")
#include "HomePage.g.cpp"
#endif

#include <shellapi.h>
#include <filesystem>

using namespace winrt;
using namespace winrt::Microsoft::UI::Xaml;

namespace winrt::PowerRenameUI::implementation
{
    HomePage::HomePage()
    {
        InitializeComponent();
    }

    void HomePage::LaunchButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        wchar_t modulePath[MAX_PATH];
        GetModuleFileNameW(nullptr, modulePath, MAX_PATH);
        std::filesystem::path exePath(modulePath);
        exePath = exePath.parent_path() / L"PowerToys.PowerRename.exe";

        if (std::filesystem::exists(exePath))
        {
            ShellExecuteW(nullptr, L"open", exePath.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
        }
    }

    void HomePage::OpenFolderButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        wchar_t modulePath[MAX_PATH];
        GetModuleFileNameW(nullptr, modulePath, MAX_PATH);
        std::filesystem::path folderPath(modulePath);
        folderPath = folderPath.parent_path();

        ShellExecuteW(nullptr, L"explore", folderPath.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
    }
}
