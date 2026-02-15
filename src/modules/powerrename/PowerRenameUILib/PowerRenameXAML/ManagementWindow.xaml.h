#pragma once

#include "ManagementWindow.g.h"

namespace winrt::PowerRenameUI::implementation
{
    struct ManagementWindow : ManagementWindowT<ManagementWindow>
    {
        ManagementWindow();

        void NavView_SelectionChanged(
            winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs const& args);

    private:
        void SetupTitleBar();
    };
}

namespace winrt::PowerRenameUI::factory_implementation
{
    struct ManagementWindow : ManagementWindowT<ManagementWindow, implementation::ManagementWindow>
    {
    };
}
