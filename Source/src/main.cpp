#include "../inc/Drivers/CurseDriver.h"
#include "../inc/Drivers/WidgetDriver.h"
#include "../inc/Utilities/FileUtility.h"

#include <stdlib.h>
#include <iostream>

CurseDriver curseDriver = CurseDriver();
WidgetDriver *widgetDriver = new WidgetDriver(curseDriver);
FileUtility fileUtility = FileUtility();

int main()
{ 
    /* 
        TMP TESTING CODE, LMAO
    */  

   // todo: convert string array to vector, in cursedriver and widget driver :(

   std::vector<std::string> names = fileUtility.GetFileNamesFromDirectory("/home/quinn/Music/asd");

    int row, col;
    getmaxyx(stdscr, row, col);

    Sizing sizing = {row, 25, 0, 0};
    
    Widget fileList;
    fileList.type = M_LIST;
    fileList.sizing = sizing;
    fileList.choices = names;
    fileList.nrChoices = names.size();

    widgetDriver->RegisterWidget(fileList);
    
    // int ch;
    //ch = getch()) != KEY_F(1)
    while(1)
    {
        widgetDriver->DisplayWidgets();
    }

    /* 
        TMP TESTING CODE, LMAO
    */  
}
