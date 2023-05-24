#include "../inc/Drivers/CurseDriver.h"
#include "../inc/Drivers/WidgetDriver.h"
#include "../inc/Utilities/FileUtility.h"

#include <stdlib.h>
#include <iostream>

CurseDriver *curseDriver = new CurseDriver();
WidgetDriver *widgetDriver = new WidgetDriver(*curseDriver);
FileUtility *fileUtility = new FileUtility();

int main()
{ 
    std::string directory = "home/quinn/Music/asd/";
    
    /* 
        TMP TESTING CODE, LMAO
    */  

    std::vector<std::string> fullNames = fileUtility->GetFileNamesFromDirectory("/home/quinn/Music/asd/");
    std::vector<std::string> shortNames = fileUtility->GetShortFileNames(fullNames);
    // std::cout << fullNames[0] << "\n";

    int row, col;
    getmaxyx(stdscr, row, col);

    // std::cout << row << " " << col << "\n";

    Sizing titleSizing = {5, col, 0, 0};
    Widget title;
    title.type = M_TEXTAREA;
    title.sizing = titleSizing;
    title.data = widgetDriver->CreateTextAreaData(
         "\nMagnus V1.0    -    Quinn Esselbrugge\n",
         false
    );
    widgetDriver->RegisterWidget(title);

    Sizing sizing = {row - 5, 25, 0, 5};
    Widget fileList;
    fileList.type = M_MENU;
    fileList.sizing = sizing;
    fileList.data = widgetDriver->CreateMenuData(
        shortNames,
        shortNames.size()
    );
    widgetDriver->RegisterWidget(fileList);


    Sizing textAreasizing = {row - 5, col - 25, 25, 5};
    Widget textArea;
    textArea.type = M_TEXTAREA;
    textArea.sizing = textAreasizing;
    textArea.data = widgetDriver->CreateTextAreaData(
        fileUtility->GetFileContents("/home/quinn/Desktop/mqtt.html"),
         true
    );
    widgetDriver->RegisterWidget(textArea);

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
