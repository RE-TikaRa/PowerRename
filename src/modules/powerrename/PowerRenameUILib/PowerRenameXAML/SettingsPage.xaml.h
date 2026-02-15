#pragma once

#include "SettingsPage.g.h"

namespace winrt::PowerRenameUI::implementation
{
    struct SettingsPage : SettingsPageT<SettingsPage>
    {
        SettingsPage();

        bool IsContextMenuRegistered();
        void IsContextMenuRegistered(bool value);

        bool ShowInExtendedContextMenu();
        void ShowInExtendedContextMenu(bool value);

        bool PersistState();
        void PersistState(bool value);

        bool MRUEnabled();
        void MRUEnabled(bool value);

        bool UseBoostLib();
        void UseBoostLib(bool value);

        hstring StatusMessage();
        void StatusMessage(hstring const& value);

        void ContextMenuToggle_Toggled(
            winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        void ExtendedMenuToggle_Toggled(
            winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        void PersistStateToggle_Toggled(
            winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        void MRUEnabledToggle_Toggled(
            winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        void UseBoostLibToggle_Toggled(
            winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        void ClearLogsButton_Click(
            winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

    private:
        void LoadSettings();
        void SaveSettings();
        bool CheckContextMenuRegistration();
        void RegisterContextMenu(bool enable);

        bool m_isContextMenuRegistered{ false };
        bool m_showInExtendedContextMenu{ false };
        bool m_persistState{ true };
        bool m_mruEnabled{ true };
        bool m_useBoostLib{ false };
        hstring m_statusMessage;
    };
}

namespace winrt::PowerRenameUI::factory_implementation
{
    struct SettingsPage : SettingsPageT<SettingsPage, implementation::SettingsPage>
    {
    };
}
