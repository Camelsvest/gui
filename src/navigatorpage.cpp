#include <stdlib.h>
#include "navigatorpage.h"

NavigatorPage::NavigatorPage()
    : m_title(NULL)
    , m_icon(0)
{
}

NavigatorPage::~NavigatorPage()
{
    if (m_title)
        free(m_title);
}

int NavigatorPage::onCreate(WPARAM wParam, LPARAM lParam)
{
    return 0;   
}

