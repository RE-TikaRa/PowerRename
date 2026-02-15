#include "pch.h"
#include "SettingsPage.xaml.h"
#if __has_include("SettingsPage.g.cpp")
#include "SettingsPage.g.cpp"
#endif

#include <shellapi.h>
#include <filesystem>
#include <fstream>
#include <shlobj.h>

#include <common/utils/json.h>

using namespace winrt;
using namespace winrt::Microsoft::UI::Xaml;

namespace fs = std::filesystem;

namespace
{
    const wchar_t* SETTINGS_FOLDER = L"ALp_Studio\\PowerRename";
    const wchar_t* SETTINGS_FILE = L"power-rename-settings.json";
    const wchar_t* CONTEXT_MENU_PACKAGE_NAME = L"PowerRenameContextMenu";

    fs::path GetSettingsPath()
    {
        wchar_t* localAppData = nullptr;
        SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, nullptr, &localAppData);
        fs::path settingsPath = localAppData;
        CoTaskMemFree(localAppData);
        settingsPath /= SETTINGS_FOLDER;
        fs::create_directories(settingsPath);
        return settingsPath / SETTINGS_FILE;
    }

    fs::path GetLogsPath()
    {
        wchar_t* localAppData = nullptr;
        SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, nullptr, &localAppData);
        fs::path logsPath = localAppData;
        CoTaskMemFree(localAppData);
        logsPath /= SETTINGS_FOLDER;
        logsPath /= L"Logs";
        return logsPath;
    }
}

namespace winrt::PowerRenameUI::implementation
{
    SettingsPage::SettingsPage()
    {
        InitializeComponent();
        LoadSettings();
        m_isContextMenuRegistered = CheckContextMenuRegistration();
    }

    bool SettingsPage::IsContextMenuRegistered() { return m_isContextMenuRegistered; }
    void SettingsPage::IsContextMenuRegistered(bool value) { m_isContextMenuRegistered = value; }

    bool SettingsPage::ShowInExtendedContextMenu() { return m_showInExtendedContextMenu; }
    void SettingsPage::ShowInExtendedContextMenu(bool value) { m_showInExtendedContextMenu = value; }

    bool SettingsPage::PersistState() { return m_persistState; }
    void SettingsPage::PersistState(bool value) { m_persistState = value; }

    bool SettingsPage::MRUEnabled() { return m_mruEnabled; }
    void SettingsPage::MRUEnabled(bool value) { m_mruEnabled = value; }

    bool SettingsPage::UseBoostLib() { return m_useBoostLib; }
    void SettingsPage::UseBoostLib(bool value) { m_useBoostLib = value; }

    hstring SettingsPage::StatusMessage() { return m_statusMessage; }
    void SettingsPage::StatusMessage(hstring const& value) { m_statusMessage = value; }

    void SettingsPage::LoadSettings()
    {
        try
        {
            auto settingsPath = GetSettingsPath();
            if (!fs::exists(settingsPath))
            {
                return;
            }

            std::ifstream file(settingsPath);
            if (!file.is_open())
            {
                return;
            }

            std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            file.close();

            auto json = json::JsonObject::Parse(winrt::to_hstring(content));

            if (json.HasKey(L"ExtendedContextMenuOnly"))
            {
                m_showInExtendedContextMenu = json.GetNamedBoolean(L"ExtendedContextMenuOnly", false);
            }
            if (json.HasKey(L"PersistState"))
            {
                m_persistState = json.GetNamedBoolean(L"PersistState", true);
            }
            if (json.HasKey(L"MRUEnabled"))
            {
                m_mruEnabled = json.GetNamedBoolean(L"MRUEnabled", true);
            }
            if (json.HasKey(L"UseBoostLib"))
            {
                m_useBoostLib = json.GetNamedBoolean(L"UseBoostLib", false);
            }
        }
        catch (...)
        {
        }
    }

    void SettingsPage::SaveSettings()
    {
        try
        {
            json::JsonObject json;
            json.SetNamedValue(L"ExtendedContextMenuOnly", json::JsonValue::CreateBooleanValue(m_showInExtendedContextMenu));
            json.SetNamedValue(L"PersistState", json::JsonValue::CreateBooleanValue(m_persistState));
            json.SetNamedValue(L"MRUEnabled", json::JsonValue::CreateBooleanValue(m_mruEnabled));
            json.SetNamedValue(L"UseBoostLib", json::JsonValue::CreateBooleanValue(m_useBoostLib));

            auto settingsPath = GetSettingsPath();
            std::ofstream file(settingsPath);
            if (file.is_open())
            {
                auto jsonStr = winrt::to_string(json.Stringify());
                file << jsonStr;
                file.close();
            }
        }
        catch (...)
        {
        }
    }

    bool SettingsPage::CheckContextMenuRegistration()
    {
        HKEY hKey;
        LONG result = RegOpenKeyExW(
            HKEY_CURRENT_USER,
            L"Software\\ALp_Studio\\PowerRename",
            0,
            KEY_READ,
            &hKey);
        
        if (result != ERROR_SUCCESS)
        {
            return false;
        }
        
        DWORD value = 0;
        DWORD size = sizeof(value);
        result = RegQueryValueExW(
            hKey,
            L"ContextMenuRegistered",
            nullptr,
            nullptr,
            reinterpret_cast<LPBYTE>(&value),
            &size);
        
        RegCloseKey(hKey);
        return (result == ERROR_SUCCESS && value == 1);
    }

    void SettingsPage::RegisterContextMenu(bool enable)
    {
        wchar_t modulePath[MAX_PATH];
        GetModuleFileNameW(nullptr, modulePath, MAX_PATH);
        fs::path scriptPath(modulePath);
        scriptPath = scriptPath.parent_path() / (enable ? L"register.ps1" : L"unregister.ps1");

        if (!fs::exists(scriptPath))
        {
            StatusMessage(L"Script not found: " + hstring(scriptPath.wstring()));
            return;
        }

        std::wstring args = L"-ExecutionPolicy Bypass -File \"" + scriptPath.wstring() + L"\"";
        SHELLEXECUTEINFOW sei = { sizeof(sei) };
        sei.lpVerb = L"runas";
        sei.lpFile = L"powershell";
        sei.lpParameters = args.c_str();
        sei.nShow = SW_HIDE;
        sei.fMask = SEE_MASK_NOCLOSEPROCESS;

        if (ShellExecuteExW(&sei))
        {
            if (sei.hProcess)
            {
                WaitForSingleObject(sei.hProcess, INFINITE);
                CloseHandle(sei.hProcess);
            }
            m_isContextMenuRegistered = CheckContextMenuRegistration();
            StatusMessage(enable ? L"Registered" : L"Unregistered");
        }
        else
        {
            StatusMessage(L"Script execution failed");
        }
    }

    void SettingsPage::ContextMenuToggle_Toggled(IInspectable const&, RoutedEventArgs const&)
    {
        RegisterContextMenu(m_isContextMenuRegistered);
    }

    void SettingsPage::ExtendedMenuToggle_Toggled(IInspectable const&, RoutedEventArgs const&)
    {
        SaveSettings();
    }

    void SettingsPage::PersistStateToggle_Toggled(IInspectable const&, RoutedEventArgs const&)
    {
        SaveSettings();
    }

    void SettingsPage::MRUEnabledToggle_Toggled(IInspectable const&, RoutedEventArgs const&)
    {
        SaveSettings();
    }

    void SettingsPage::UseBoostLibToggle_Toggled(IInspectable const&, RoutedEventArgs const&)
    {
        SaveSettings();
    }

    void SettingsPage::ClearLogsButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        try
        {
            auto logsPath = GetLogsPath();
            if (!fs::exists(logsPath))
            {
                StatusMessage(L"Logs directory does not exist");
                return;
            }

            fs::remove_all(logsPath);
            StatusMessage(L"Logs directory deleted");
        }
        catch (const std::exception&)
        {
            StatusMessage(L"Failed to delete logs directory");
        }
    }
}
