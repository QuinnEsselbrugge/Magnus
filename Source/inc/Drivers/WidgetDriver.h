#ifndef WIDGET_DRIVER_H_
#define WIDGET_DRIVER_H_

#include "CurseDriver.h"
#include "../Defines/WidgetErrors.h"
#include "../Defines/HardDefines.h"

#include <string.h>
#include <vector>

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
    std::vector<std::string> choices;
    int nrChoices = 0;
};

class WidgetDriver
{

    public:
        WidgetDriver(CurseDriver curseDriver);
        ~WidgetDriver();

        WidgetErrors RegisterWidget(Widget widget);
        
        WidgetErrors DisplayWidgets();

        WidgetErrors CheckWidgetInteraction();

    private:

        Widget m_widgets[MAX_NR_WIDGETS];
        CurseDriver m_curseDriver;

        int m_registeredWidgets = 0;
        
        void DestroyWidgets();
        



};

#endif
