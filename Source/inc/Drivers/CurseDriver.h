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
        CurseDriverErrors CreateTextArea(int handle, std::string data, bool toggleLines, Sizing sizings);
        
        CurseDriverErrors DisplayMenu(int handle);
        CurseDriverErrors DisplayTextArea(int handle);

        CurseDriverErrors UpdateTextArea(int handle, std::string data, bool toggleLines, Sizing sizings);

        CurseDriverErrors DeleteTextArea(int handle);

        CurseDriverErrors CheckMenuInteraction(int handle);
        CurseDriverErrors CheckTextAreaInteraction(int handle);

        std::string FetchMenuSelection(int handle);
        
    private:

        struct Menu
        {
            int handle;
            int nrItems;
            int colors[MAX_COLORS_MENU];
            int selectedIndex;
            std::string *menuResult;
            std::vector<std::string> choices;
            WINDOW *curseWindow;
            MENU *curseMenu;
            ITEM **curseItems;
            Sizing sizing;
        };

        struct TextArea
        {
            int handle;
            std::string data;
            bool toggleLines;
            int topOffset = 0;
            int contentHeight; // todo
            WINDOW * curseWindow;
            Sizing sizing;
        };

        Menu m_menus[MAX_NR_MENUS];
        TextArea m_textAreas[MAX_NR_TEXT_AREAS];

        void *m_focused;

        int m_registeredMenus = 0;
        int m_registeredTextAreas = 0;

        CurseDriverErrors InsertItemChoices(ITEM **curseItems, std::vector<std::string> choices, int nrChoices);
    
        void PrintString(std::string string, WINDOW *curseWindow, int y, int x, bool highlight);

        int GetStringWidth(std::string str);
        std::string StringElipsis(std::string str, int cutoffSize);
        std::string ShortenString(std::string str, int amount);
        
        bool CheckInteractionFocusChange(WINDOW *window, Sizing bounds, int c);
        bool ClickInBounds(int y, int x, Sizing bounds);

        int GetMenu(int handle);
        int GetTextArea(int handle);

        void DestroyMenus();
        void DestroyTextAreas();
};



#endif
