#ifndef WIDGET_DRIVER_H_
#define WIDGET_DRIVER_H_

#include "CurseDriver.h"
#include "WidgetErrors.h"
#include "HardDefines.h"

enum WidgetType
{
    M_LIST,
    M_PANEL,
    M_TEXT,
    M_TEXTAREA,
};

struct Widget
{
    WidgetType type;
    Sizing sizing;
    int handle;
    std::string choices[MAX_LIST_ITEMS] = {};
    int nrChoices = 0;
};

class WidgetDriver
{

    public:
        WidgetDriver(CurseDriver curseDriver);
        ~WidgetDriver();

        WidgetErrors RegisterWidget(Widget widget);
        WidgetErrors DisplayWidgets();

    private:

        Widget m_widgets[MAX_NR_WIDGETS];
        CurseDriver m_curseDriver;

        int m_registeredWidgets = 0;
        



};

#endif
