#include <stdlib.h>
#include <iostream>
#include "../inc/CurseDriver.h"
#include "../inc/WidgetDriver.h"

CurseDriver curseDriver = CurseDriver();
WidgetDriver widgetDriver = WidgetDriver(curseDriver);

int main()
{ 
    std::string choices[MAX_LIST_ITEMS] = {"Yeett", "yote", "Yet", "AAAA", "ASDASDASDASDASD" , "asdasdsadsahbasdbhjadsabhjssdabhjdsabhjdasasd", "afiouihdfgyudhf7ewyr47r9ewqw4u83y574we", "LOL"};

    Sizing sizing = {10, 10, 0, 0};
    
    Widget fileList;
    fileList.type = M_LIST;
    fileList.sizing = sizing;
    std::copy(choices, choices + 8, fileList.choices);
    fileList.nrChoices = 8;

    std::cout << "HERE" << "\n";
    // todo figure out why the menu is not displaying thru the widget driver...

    widgetDriver.RegisterWidget(fileList);
    
    // int colors[MAX_COLORS_MENU] = {COLOR_BLACK, COLOR_WHITE};
    // curseDriver.CreateMenu(1, choices, 8, sizing, colors);
    
    int ch;
    while((ch = getch()) != KEY_F(1))
    {
        widgetDriver.DisplayWidgets();
        // curseDriver.DisplayMenu(1);
    }
}
