#pragma once

#include "App.xaml.g.h"

namespace winrt::PowerRenameUI::implementation
{
    struct App : AppT<App>
    {
        App();

        void OnLaunched(Microsoft::UI::Xaml::LaunchActivatedEventArgs const&);

    private:
        winrt::Microsoft::UI::Xaml::Window m_mainWindow{ nullptr };
        winrt::Microsoft::UI::Xaml::Window m_managementWindow{ nullptr };
    };
}
