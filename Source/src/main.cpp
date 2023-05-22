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

    Sizing sizing = {row, 25, 0, 0};

    Widget fileList;
    fileList.type = M_LIST;
    fileList.sizing = sizing;
    fileList.choices = shortNames;
    fileList.nrChoices = shortNames.size();

    widgetDriver->RegisterWidget(fileList);

    Sizing textAreasizing = {row, col - 25, 25, 0};

    Widget textArea;
    textArea.type = M_TEXTAREA;
    textArea.sizing = textAreasizing;
    textArea.choices = shortNames;
    textArea.data = fileUtility->GetFileContents("/home/quinn/Desktop/yeet.txt"); // tmp
    textArea.nrChoices = shortNames.size();

    // std::cout << fileUtility->GetFileContents("/home/quinn/Desktop/yeet.txt") << "\n";
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
