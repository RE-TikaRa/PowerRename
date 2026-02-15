#pragma once

#include "AboutPage.g.h"

namespace winrt::PowerRenameUI::implementation
{
    struct AboutPage : AboutPageT<AboutPage>
    {
        AboutPage();
    };
}

namespace winrt::PowerRenameUI::factory_implementation
{
    struct AboutPage : AboutPageT<AboutPage, implementation::AboutPage>
    {
    };
}
