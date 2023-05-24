#ifndef WIDGET_DRIVER_H_
#define WIDGET_DRIVER_H_

#include "CurseDriver.h"
#include "../Defines/WidgetErrors.h"
#include "../Defines/HardDefines.h"

#include <string.h>
#include <vector>

enum WidgetType
{
    M_MENU,
    M_PANEL,
    M_TEXT,
    M_TEXTAREA,
};

struct Menu
{
    std::vector<std::string> choices;
    int nrChoices = 0;
};

struct TextArea
{
    std::string data;
    bool toggleLines = false;
};

struct Panel
{
    WidgetType type;
    Sizing sizing;
};

struct Text
{
    WidgetType type;
    Sizing sizing;
};

struct Widget // parent-ish
{
    int handle;
    WidgetType type;
    Sizing sizing;
    void *data;
};


class WidgetDriver
{

    public:
        WidgetDriver(CurseDriver curseDriver);
        ~WidgetDriver();

        WidgetErrors RegisterWidget(Widget widget);
        
        WidgetErrors DisplayWidgets();

        WidgetErrors CheckWidgetInteraction();

        void *CreateMenuData(std::vector<std::string> choices, int nrChoices);
        void *CreateTextAreaData(std::string data, bool enableLineNumbers);

    private:

        Widget m_widgets[MAX_NR_WIDGETS];
        CurseDriver m_curseDriver;

        int m_registeredWidgets = 0;
        
        void DestroyWidgets();
        



};

#endif
