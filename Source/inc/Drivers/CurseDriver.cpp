#include "CurseDriver.h"




// todo : implement building the file list and write base code for the curse driver...
CurseDriver::CurseDriver() 
{
    // Start stdscr
    initscr();

    curs_set(0);

    // Start color driver
    start_color();

    noecho();

    // Init keypad (F1, F2, Arrow keys etc)
    keypad(stdscr, TRUE);
}


CurseDriver::~CurseDriver()
{
    DestroyMenus();
    DestroyTextAreas();

    endwin();
}

/*!
    Creationists
*/

CurseDriverErrors CurseDriver::CreateMenu(int handle, std::vector<std::string> choices, int nrChoices, Sizing sizings)
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

    set_menu_mark(menu->curseMenu, " * ");

    menu->choices = choices;
    menu->nrItems = nrChoices;
    menu->sizing = sizings;
    menu->handle = handle;
    menu->menuResult = (std::string *) calloc(1, FILE_CHARACTER_LIMIT);
    menu->selectedIndex = 0;

    set_menu_win(menu->curseMenu, menu->curseWindow);
    post_menu(menu->curseMenu);

    m_menus[m_registeredMenus++] = *menu;

    DisplayMenu(handle, false);

    return CurseDriverErrors::NO_ERROR_CURSE;
}

CurseDriverErrors CurseDriver::CreateTextArea(int handle, std::string data, bool toggleLines, Sizing sizings)
{
    TextArea *textArea = (TextArea *) calloc(1, sizeof(TextArea));

    if (textArea == nullptr)
    {
        return CurseDriverErrors::DRIVER_INTERNAL_OPERATION_FAILURE_CURSE;
    }

    textArea->handle = handle;
    textArea->data = data;
    textArea->sizing = sizings;
    textArea->toggleLines = toggleLines;
    textArea->curseWindow = newwin(sizings.height, sizings.width, sizings.startY, sizings.startX);

    // tmp    
    m_textAreas[m_registeredTextAreas++] = *textArea;

    DisplayTextArea(handle, false);

    return CurseDriverErrors::NO_ERROR_CURSE;
}

/*!
    Displayers
*/

//todo : subdivide and improve
CurseDriverErrors CurseDriver::DisplayMenu(int handle, bool checkInteraction)
{
    Menu& menu = m_menus[GetMenu(handle)];

    if (menu.handle < 0 && menu.handle > MAX_NR_MENUS)
    {
        return CurseDriverErrors::DRIVER_INTERNAL_OPERATION_FAILURE_CURSE;
    }

    if (checkInteraction == true)
    {
        CheckMenuInteraction(handle);
    }

    // tmp pseudo
    int y = 1;
    int x = 2;

    box(menu.curseWindow, 0, 0);

    for (int i = 0; i < menu.nrItems; i++)
    {
        std::string strOut = menu.choices[i];
        int stringWidth = GetStringWidth(menu.choices[i]);

        if (stringWidth + BASH_STR_WIDTH_BUFFER > menu.sizing.width)
        {       
            strOut = StringElipsis(strOut, menu.sizing.width);
        }

        bool highlight = menu.selectedIndex == i ? true : false;
        PrintString(strOut, menu.curseWindow, y, x, highlight);

        y++;
    }

    wrefresh(menu.curseWindow);

    return CurseDriverErrors::NO_ERROR_CURSE;
}

CurseDriverErrors CurseDriver::DisplayTextArea(int handle, bool checkInteraction)
{
    TextArea& textArea = m_textAreas[GetTextArea(handle)];

    if (textArea.handle < 0 || textArea.handle > MAX_NR_TEXT_AREAS)
    {
        return CurseDriverErrors::DRIVER_INTERNAL_OPERATION_FAILURE_CURSE;
    }

    wclear(textArea.curseWindow);

    box(textArea.curseWindow, 0, 0);

    std::string append;
    int x = 6;
    int y = 1;

    for (long unsigned int i = 0; i < textArea.data.size(); i++)
    {
        if (textArea.data[i] == '\n' && y < textArea.sizing.height - 1)
        {
            PrintString(append, textArea.curseWindow, y, x, false);

            if (textArea.toggleLines == true)
            {
                wattron(textArea.curseWindow, A_DIM);
                PrintString(std::to_string(y), textArea.curseWindow, y, (x - x) + 1, false);
                wattroff(textArea.curseWindow, A_DIM);
            }

            append.clear();

            y++;
        } else
        {
            append.push_back(textArea.data[i]);
        }
    }

    wrefresh(textArea.curseWindow);

    checkInteraction = checkInteraction;

    return CurseDriverErrors::NO_ERROR_CURSE;
}

// todo, add existing check, code is currently very ambigious 

/*! 
    Updating
*/

CurseDriverErrors CurseDriver::UpdateTextArea(int handle, std::string data, bool toggleLines, Sizing sizings)
{
    if (handle < 0)
    {
        return CurseDriverErrors::DRIVER_INTERNAL_OPERATION_FAILURE_CURSE;
    }

    TextArea *textArea = &m_textAreas[GetTextArea(handle)];

    textArea->data = data;
    textArea->sizing = sizings;
    textArea->toggleLines = toggleLines;
    
    return CurseDriverErrors::NO_ERROR_CURSE;
}


/*! 
    Deleting
*/
// CurseDriverErrors DeleteTextArea(int handle);

/*!
    Interactions
*/

CurseDriverErrors CurseDriver::CheckMenuInteraction(int handle)
{
    Menu& menu = m_menus[GetMenu(handle)];
    int c = getch();

    switch(c)
    {
        case KEY_DOWN:
                menu.selectedIndex = menu.selectedIndex + 1;

                if (menu.selectedIndex >= menu.nrItems)
                {
                    menu.selectedIndex = 0;
                }
        break;

        case KEY_UP:
                menu.selectedIndex--;

                if (menu.selectedIndex <= -1)
                {
                    menu.selectedIndex = menu.nrItems - 1;
                }
        break;
 
        case 10:
            std::string *ptr = menu.menuResult;
            *ptr = menu.choices[menu.selectedIndex];

            // std::cout << "                     " <<  *menu.menuResult << "\n\n\n\r\n";
            // wmove(menu.curseWindow, 20, 0);
            // wclrtoeol(menu.curseWindow);
            // std::cout<< item_name(current_item(menu.curseMenu)) << "\n";
            // mvprintw(20, 0, "Item selected is : %s", 
            //                 item_name(current_item(menu.curseMenu)));
            // pos_menu_cursor(menu.curseMenu);
        break;
    }

    return CurseDriverErrors::CREATION_FAILED_CURSE;
}

/*
    Stuff for now
*/
std::string CurseDriver::FetchMenuSelection(int handle)
{
    // this will fuck up later, have fun future me lol
    Menu& menu = m_menus[GetMenu(handle)];

    if (menu.menuResult == nullptr)
    {
        return std::string();
    }

    return *menu.menuResult;
}

/*!
    Helpers
*/

CurseDriverErrors CurseDriver::InsertItemChoices(ITEM **curseItems, std::vector<std::string> choices, int nrChoices)
{   
    if (curseItems == nullptr && nrChoices <= 0)
    {
        return CurseDriverErrors::DRIVER_INTERNAL_OPERATION_FAILURE_CURSE;
    }

    for (int i = 0; i < nrChoices; i++)
    {
        curseItems[i] = new_item(choices[i].c_str(), choices[i].c_str());
    }

    return CurseDriverErrors::NO_ERROR_CURSE;
}

void CurseDriver::PrintString(std::string string, WINDOW *curseWindow, int y, int x, bool highlight)
{
    if (highlight == true)
    {
        wattron(curseWindow, A_REVERSE);
        mvwprintw(curseWindow, y, x, "%s", string.c_str());
        wattroff(curseWindow, A_REVERSE);
    } else
    {
        mvwprintw(curseWindow, y, x, "%s", string.c_str());
    }
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
    strOut = ShortenString(str, diff + BASH_STR_WIDTH_BUFFER);

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

        strIndex++;

        if (total >= amount)
        { 
            return str;
        }
    }
    
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

int CurseDriver::GetTextArea(int handle)
{
    for (int i = 0; i < MAX_NR_TEXT_AREAS; i++)
    {
        if (m_textAreas[i].handle == handle)
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

        free(m_menus[i].menuResult);
        m_menus[i].menuResult = nullptr;
    }
}

void CurseDriver::DestroyTextAreas()
{
    for (int i = 0; i < m_registeredTextAreas; i++)
    {
        delete &m_textAreas[i];
    }
}