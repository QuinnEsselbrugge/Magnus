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
    endwin();

    DestroyMenus();
}


/*!
    Creationists
*/

CurseDriverErrors CurseDriver::CreateMenu(int handle, std::string choices[MAX_LIST_ITEMS], int nrChoices, Sizing sizings, int colors[MAX_COLORS_MENU])
{
    Menu *menu = (Menu *) calloc(1, sizeof(Menu));
    
    // Init items
    menu->curseItems = (ITEM **) calloc(nrChoices + 1, sizeof(ITEM *));
    InsertItemChoices(menu->curseItems, choices, nrChoices);

    // menu.curseItems[nrChoices] = (ITEM *) NULL

    // Create menu
    menu->curseMenu = new_menu((ITEM **)menu->curseItems);

    // Create window
    menu->curseWindow = newwin(sizings.height, sizings.width, sizings.startY, sizings.startX);
    keypad(menu->curseWindow, TRUE);

    init_pair(handle, colors[0], colors[1]);

    std::copy(choices, choices + nrChoices, menu->choices);
    menu->nrItems = nrChoices;
    menu->sizing = sizings;
    menu->handle = handle;
    
    m_menus[0] = *menu;

    return CurseDriverErrors::NO_ERROR;
}

/*!
    Displayers
*/

CurseDriverErrors CurseDriver::DisplayMenu(int handle)
{
    Menu menu;

    // Todo convert to getter, WONT LET ME? IDK WHY
    int nrMenus = sizeof(m_menus) / sizeof(m_menus[0]);

    for (int i = 0; i < nrMenus; i++)
    {
        if (m_menus[i].handle == handle)
        {
            menu = m_menus[i];
        }
    }

    if (menu.handle == 0)
    {
        return CurseDriverErrors::DRIVER_INTERNAL_OPERATION_FAILURE;
    }

    // tmp pseudo
    int y = 2;
    int x = 2;

    box(menu.curseWindow, 0, 0);

    for (int i = 0; i < menu.nrItems; i++)
    {
        
        mvwprintw(menu.curseWindow, y, x, "%s", menu.choices[i].c_str());

        y++;
    }

    wrefresh(menu.curseWindow);


    return CurseDriverErrors::NO_ERROR;
}


/*!
    Helpers
*/

CurseDriverErrors CurseDriver::InsertItemChoices(ITEM **curseItems, std::string *choices, int nrChoices)
{   
    if (curseItems == nullptr && choices == nullptr && nrChoices <= 0)
    {
        return CurseDriverErrors::DRIVER_INTERNAL_OPERATION_FAILURE;
    }

    for (int i = 0; i < nrChoices; i++)
    {
        curseItems[i] = new_item(choices[i].c_str(), choices[i].c_str());
    }

    return CurseDriverErrors::NO_ERROR;
}


/*!
    Getters
*/



/*!
    Deconstructors
*/

void CurseDriver::DestroyMenus()
{
    for (int i = 0; i < MAX_NR_MENUS; i++)
    {
        delete m_menus[i].curseItems;
        m_menus[i].curseItems = nullptr;
    }
}