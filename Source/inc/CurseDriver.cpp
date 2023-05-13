#include "CurseDriver.h"




// todo : implement building the file list and write base code for the curse driver...
CurseDriver::CurseDriver() 
{
    // Start stdscr
    initscr();

    // Start color driver
    start_color();

    noecho();

    // Init keypad (F1, F2, Arrow keys etc)
    keypad(stdscr, TRUE);
}


// todo: fix the freeing of memory not executing properly see valgrind

CurseDriver::~CurseDriver()
{
    DestroyMenus();

    endwin();
}


/*!
    Creationists
*/

CurseDriverErrors CurseDriver::CreateMenu(int handle, std::string choices[MAX_LIST_ITEMS], int nrChoices, Sizing sizings)
{
    Menu *menu = (Menu *) calloc(1, sizeof(Menu));

    if (menu == nullptr)
    {
        return CurseDriverErrors::DRIVER_INTERNAL_OPERATION_FAILURE_CURSE;
    }
    
    // Init items
    menu->curseItems = (ITEM **) calloc(nrChoices + 1, sizeof(ITEM *));

    if (menu->curseItems == nullptr)
    {
        return CurseDriverErrors::DRIVER_INTERNAL_OPERATION_FAILURE_CURSE;
    }

    InsertItemChoices(menu->curseItems, choices, nrChoices);

    // Create menu
    menu->curseMenu = new_menu((ITEM **)menu->curseItems);

    // Create window
    menu->curseWindow = newwin(sizings.height, sizings.width, sizings.startY, sizings.startX);
    keypad(menu->curseWindow, TRUE);

    init_pair(handle, COLOR_BLACK, COLOR_WHITE);

    std::copy(choices, choices + nrChoices, menu->choices);
    menu->nrItems = nrChoices;
    menu->sizing = sizings;
    menu->handle = handle;

    set_menu_win(menu->curseMenu, menu->curseWindow);
    post_menu(menu->curseMenu);

    m_menus[0] = *menu;

    DisplayMenu(handle);

    return CurseDriverErrors::NO_ERROR_CURSE;
}

/*!
    Displayers
*/

CurseDriverErrors CurseDriver::DisplayMenu(int handle)
{
    Menu menu = m_menus[GetMenu(handle)];
    
    if (menu.handle == 0)
    {
        return CurseDriverErrors::DRIVER_INTERNAL_OPERATION_FAILURE_CURSE;
    }

    // tmp pseudo
    int y = 1;
    int x = 2;

    box(menu.curseWindow, 0, 0);

    for (int i = 0; i < menu.nrItems; i++)
    {
        std::string strOut = menu.choices[i];
        int stringWidth = GetStringWidth(menu.choices[i]);

        if (stringWidth > menu.sizing.width)
        {       
            strOut = StringElipsis(strOut, menu.sizing.width);
        }

        mvwprintw(menu.curseWindow, y, x, "%s", strOut.c_str());

        y++;
    }

    wrefresh(menu.curseWindow);

    return CurseDriverErrors::NO_ERROR_CURSE;
}


/*!
    Helpers
*/

CurseDriverErrors CurseDriver::InsertItemChoices(ITEM **curseItems, std::string *choices, int nrChoices)
{   
    if (curseItems == nullptr && choices == nullptr && nrChoices <= 0)
    {
        return CurseDriverErrors::DRIVER_INTERNAL_OPERATION_FAILURE_CURSE;
    }

    for (int i = 0; i < nrChoices; i++)
    {
        curseItems[i] = new_item(choices[i].c_str(), choices[i].c_str());
    }

    return CurseDriverErrors::NO_ERROR_CURSE;
}

std::string CurseDriver::StringElipsis(std::string str, int cutoffSize)
{
    std::string strOut;
    int stringWidth = GetStringWidth(str);

    // Rudimentary elipsis  
    int diff = stringWidth - cutoffSize;

    int elipsisWidth = GetStringWidth("...");

    diff = diff + elipsisWidth;

    // buffer of ~3 pixels. blame bash fuckiness
    strOut = ShortenString(str, diff + 3);

    strOut.append("...");

    return strOut;
}

int CurseDriver::GetStringWidth(std::string str)
{
    int total = 0;

    for (long unsigned int i = 0; i < str.length(); i++)
    {
        total += wcwidth(str[i]);
    }

    return total;
}

std::string CurseDriver::ShortenString(std::string str, int amount)
{
    int total = 0;
    int strIndex = 1;

    int strLen = str.length();

    for (int i = 0; i < strLen; i++)
    {
        total += wcwidth(str[strLen - strIndex]);
        str.pop_back();

        // todo fix why its not doing enough characters, lol
        strIndex++;

        if (total >= amount)
        { 
            return str;
        }
    }
    // for (long unsigned int i = str.length(); i > 0; i--)
    // {
    //     total += wcwidth(str[i]);
    //     std::cout << wcwidth(str[i + 1]) << "\n";
    //     str.pop_back();

    //     if (total >= amount - 1)
    //     {
    //         return str;
    //     }
    // }
    
    return str;
}


/*!
    Getters
*/
int CurseDriver::GetMenu(int handle)
{

    for (int i = 0; i < MAX_NR_MENUS; i++)
    {
        if (m_menus[i].handle == handle)
        {
            return i;
        }
    }

    return -1;
}



/*!
    Deconstructors
*/

void CurseDriver::DestroyMenus()
{
    for (long unsigned int i = 0; i < MAX_NR_MENUS; i++)
    {
        for (int x = 0; x < m_menus[i].nrItems; x++)
        {
            free_item(m_menus[i].curseItems[x]);    
        }

        unpost_menu(m_menus[i].curseMenu);
        free_menu(m_menus[i].curseMenu);
    }
}