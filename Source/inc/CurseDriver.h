#ifndef CURSE_DRIVER_H_
#define CURSE_DRIVER_H_

#include "HardDefines.h"
#include "CurseDriverErrors.h"

#include <iostream>
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

        CurseDriverErrors CreateMenu(int handle, std::string choices[MAX_LIST_ITEMS], int nrChoices, Sizing sizings, int colors[MAX_COLORS_MENU]);
        
        CurseDriverErrors DisplayMenu(int handle);
        
    private:

        struct Menu
        {
            int handle;
            int nrItems;
            int colors[MAX_COLORS_MENU];
            std::string choices[MAX_LIST_ITEMS];
            WINDOW *curseWindow;
            MENU *curseMenu;
            ITEM **curseItems;
            Sizing sizing;
        };

        Menu m_menus[MAX_NR_MENUS];

        CurseDriverErrors InsertItemChoices(ITEM **curseItems, std::string *choices, int nrChoices);

        void DestroyMenus();
};



#endif
