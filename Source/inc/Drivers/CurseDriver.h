#ifndef CURSE_DRIVER_H_
#define CURSE_DRIVER_H_

#include "../Defines/HardDefines.h"
#include "../Defines/CurseDriverErrors.h"

#include <iostream>
#include <vector>
#include <menu.h>
#include <curses.h>
#include <panel.h>

struct Sizing
{
    int height;
    int width;
    int startX;
    int startY;
};

class CurseDriver
{
    public:
        CurseDriver();
        ~CurseDriver();

        CurseDriverErrors CreateMenu(int handle, std::vector<std::string> choices, int nrChoices, Sizing sizings);
        
        CurseDriverErrors DisplayMenu(int handle, bool checkInteraction = true);

        CurseDriverErrors CheckMenuInteraction(int handle);
        
    private:

        struct Menu
        {
            int handle;
            int nrItems;
            int colors[MAX_COLORS_MENU];
            int selectedIndex;
            std::vector<std::string> choices;
            WINDOW *curseWindow;
            MENU *curseMenu;
            ITEM **curseItems;
            Sizing sizing;
        };

        Menu m_menus[MAX_NR_MENUS];

        CurseDriverErrors InsertItemChoices(ITEM **curseItems, std::vector<std::string> choices, int nrChoices);
    
        void PrintString(std::string string, WINDOW *curseWindow, int y, int x, bool highlight);

        int GetStringWidth(std::string str);
        std::string StringElipsis(std::string str, int cutoffSize);
        std::string ShortenString(std::string str, int amount);
        
        int GetMenu(int handle);

        void DestroyMenus();
};



#endif