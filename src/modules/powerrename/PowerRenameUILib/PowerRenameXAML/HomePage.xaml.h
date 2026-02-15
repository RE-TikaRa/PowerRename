#pragma once

#include "HomePage.g.h"

namespace winrt::PowerRenameUI::implementation
{
    struct HomePage : HomePageT<HomePage>
    {
        HomePage();

        void LaunchButton_Click(
            winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        void OpenFolderButton_Click(
            winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::PowerRenameUI::factory_implementation
{
    struct HomePage : HomePageT<HomePage, implementation::HomePage>
    {
    };
}
