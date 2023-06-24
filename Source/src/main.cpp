#include "../inc/Drivers/CurseDriver.h"
#include "../inc/Drivers/WidgetDriver.h"
#include "../inc/Utilities/FileUtility.h"

#include <stdlib.h>
#include <iostream>

CurseDriver *curseDriver = new CurseDriver();
WidgetDriver *widgetDriver = new WidgetDriver(*curseDriver);
FileUtility *fileUtility = new FileUtility();


std::string oldFile;
std::string currentFile;

int main()
{ 
    std::string directory = "/home/quinn/Documents/hmvv";
    /* 
        TMP TESTING CODE, LMAO
    */  

    std::vector<std::string> fullNames = fileUtility->GetFileNamesFromDirectory("/home/quinn/Documents/hmvv/");
    std::vector<std::string> shortNames = fileUtility->GetShortFileNames(fullNames);

    int row, col;
    getmaxyx(stdscr, row, col);

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
    fileList.checkInteraction = true;
    fileList.data = widgetDriver->CreateMenuData(
        shortNames,
        shortNames.size()
    );
    int fileListHandle = widgetDriver->RegisterWidget(fileList);

    Sizing textAreasizing = {row - 5, col - 25, 25, 5};
    Widget textArea;
    textArea.type = M_TEXTAREA;
    textArea.sizing = textAreasizing;
    textArea.checkInteraction = true;
    textArea.data = widgetDriver->CreateTextAreaData(
        fileUtility->GetFileContents(fullNames[0]),
        true
    );
    currentFile = fullNames[0];

    int textAreaHandle = widgetDriver->RegisterWidget(textArea);

    while(1)
    {

        Widget fetchMenu = widgetDriver->GetWidget(fileListHandle);

        if (oldFile.compare(currentFile) != 0)
        {
            // hot reload textarea
            oldFile = currentFile;

            widgetDriver->SetTextAreaData(
                textAreaHandle,
                fileUtility->GetFileContents(currentFile),
                true
            );
        }
        // Checking blocks, until interaction
        widgetDriver->CheckWidgetInteraction();
        widgetDriver->DisplayWidgets();

        std::string selection = widgetDriver->FetchMenuSelection(fetchMenu);

        if (selection.size() > 0)
        {
            currentFile = directory + "/" + selection;
        }
        
    }

    /* 
        TMP TESTING CODE, LMAO
    */  
}
