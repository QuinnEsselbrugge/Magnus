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

   std::vector<std::string> names = fileUtility.GetFileNamesFromDirectory("/home/quinn/Music/asd");

   for (long unsigned int i = 0; i < names.size(); i++)
   {
       std::cout << names[i] << "\n";
   }

    // std::string choices[MAX_LIST_ITEMS] = {"Yeett", "yote", "Yet", "AAAA", "ASDASDASDASDASD" , "asdasdsadsahbasdbhjadsabhjssdabhjdsabhjdasasd", "afiouihdfgyudhf7ewyr47r9ewqw4u83y574we", "LOL"};
    // int row, col;
    // getmaxyx(stdscr, row, col);

    // Sizing sizing = {row, 20, 0, 0};
    
    // Widget fileList;
    // fileList.type = M_LIST;
    // fileList.sizing = sizing;
    // std::copy(choices, choices + 8, fileList.choices);
    // fileList.nrChoices = 8;

    // widgetDriver->RegisterWidget(fileList);
    
    // int ch;
    // while((ch = getch()) != KEY_F(1))
    // {
    //     widgetDriver->DisplayWidgets();
    // }


    /* 
        TMP TESTING CODE, LMAO
    */  
}
