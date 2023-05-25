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

};

struct Text
{

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

        int RegisterWidget(Widget widget);
        
        WidgetErrors DisplayWidgets();

        WidgetErrors CheckWidgetInteraction();

        // Menu related
        void *CreateMenuData(std::vector<std::string> choices, int nrChoices);
        std::string FetchMenuSelection(Widget widget);
        
        // Text area related
        void *CreateTextAreaData(std::string data, bool enableLineNumbers);
        void SetTextAreaData(int handle, std::string data, bool toggleLines);

        // General
        Widget GetWidget(int handle);

    private:

        Widget m_widgets[MAX_NR_WIDGETS];
        CurseDriver m_curseDriver;

        int m_registeredWidgets = 0;
        
        void DestroyWidgets();
};

#endif
