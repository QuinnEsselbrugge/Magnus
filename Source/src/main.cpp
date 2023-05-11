#include <stdlib.h>
#include <iostream>
#include "../inc/CurseDriver.h"

CurseDriver curseDriver = CurseDriver();

int main()
{ 
    Sizing sizing = {30, 10, 0, 0};
    std::string choices[MAX_LIST_ITEMS] = {"Yeett", "yote", "Yet", "AAAA", "ASDASDASDASDASD" , "LOL"};
    int colors[MAX_COLORS_MENU] = {COLOR_BLACK, COLOR_WHITE};
    curseDriver.CreateMenu(1, choices, 6, sizing, colors);
    
    int ch;
    while((ch = getch()) != KEY_F(1))
    {
        curseDriver.DisplayMenu(1);
    }
}
