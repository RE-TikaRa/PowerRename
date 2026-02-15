#include "pch.h"
#include "ManagementWindow.xaml.h"
#if __has_include("ManagementWindow.g.cpp")
#include "ManagementWindow.g.cpp"
#endif

#include "HomePage.xaml.h"
#include "SettingsPage.xaml.h"
#include "AboutPage.xaml.h"

#include <microsoft.ui.xaml.window.h>
#include <winrt/Microsoft.UI.Windowing.h>
#include <winrt/Microsoft.UI.Interop.h>

using namespace winrt;
using namespace winrt::Microsoft::UI::Xaml;
using namespace winrt::Microsoft::UI::Xaml::Controls;

namespace winrt::PowerRenameUI::implementation
{
    ManagementWindow::ManagementWindow()
    {
        InitializeComponent();
        SetupTitleBar();

        NavView().SelectedItem(NavItem_Home());
        ContentFrame().Navigate(xaml_typename<PowerRenameUI::HomePage>());
    }

    void ManagementWindow::SetupTitleBar()
    {
        ExtendsContentIntoTitleBar(true);
        SetTitleBar(AppTitleBar());

        auto appWindow = this->AppWindow();
        if (appWindow)
        {
            appWindow.SetIcon(L"Assets/PowerRename/PowerRenameUI.ico");
            appWindow.TitleBar().PreferredHeightOption(Microsoft::UI::Windowing::TitleBarHeightOption::Tall);
        }
    }

    void ManagementWindow::NavView_SelectionChanged(
        IInspectable const&,
        NavigationViewSelectionChangedEventArgs const& args)
    {
        if (auto selectedItem = args.SelectedItem().try_as<NavigationViewItem>())
        {
            auto tag = unbox_value<hstring>(selectedItem.Tag());

            if (tag == L"home")
            {
                ContentFrame().Navigate(xaml_typename<PowerRenameUI::HomePage>());
            }
            else if (tag == L"settings")
            {
                ContentFrame().Navigate(xaml_typename<PowerRenameUI::SettingsPage>());
            }
            else if (tag == L"about")
            {
                ContentFrame().Navigate(xaml_typename<PowerRenameUI::AboutPage>());
            }
        }
    }
}
