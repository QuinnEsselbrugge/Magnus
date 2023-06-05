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

    clear();
	cbreak();
    nodelay(stdscr, TRUE);

    keypad(stdscr, TRUE);
    
	mousemask(ALL_MOUSE_EVENTS, NULL);
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

    // Create windowCheckFocus
    menu->curseWindow = newwin(sizings.height, sizings.width, sizings.startY, sizings.startX);

    keypad(menu->curseWindow, true);
    nodelay(menu->curseWindow, true); // tmp, settings

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

    DisplayMenu(handle);

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

    keypad(textArea->curseWindow, true);
    nodelay(textArea->curseWindow, true); // tmp, settings

    scrollok(textArea->curseWindow, true);
    idlok(textArea->curseWindow, true);

    // tmp    
    m_textAreas[m_registeredTextAreas++] = *textArea;

    DisplayTextArea(handle);

    return CurseDriverErrors::NO_ERROR_CURSE;
}

/*!
    Displayers
*/

//todo : subdivide and improve
CurseDriverErrors CurseDriver::DisplayMenu(int handle)
{
    Menu& menu = m_menus[GetMenu(handle)];

    if (menu.handle < 0 && menu.handle > MAX_NR_MENUS)
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

// todo split
CurseDriverErrors CurseDriver::DisplayTextArea(int handle)
{
    TextArea& textArea = m_textAreas[GetTextArea(handle)];

    if (textArea.handle < 0 || textArea.handle > MAX_NR_TEXT_AREAS)
    {
        return CurseDriverErrors::DRIVER_INTERNAL_OPERATION_FAILURE_CURSE;
    }

    box(textArea.curseWindow, 0, 0);

    wclear(textArea.curseWindow);

    std::string append;
    int offset = 5; // todo settings
    int y = textArea.topOffset;

    for (long unsigned int i = 0; i < textArea.data.size(); i++)
    {
        if (textArea.data[i] == '\n' && y < textArea.sizing.height - 1)
        {
            PrintString(append, textArea.curseWindow, y, offset, false);

            if (textArea.toggleLines == true)
            {
                wattron(textArea.curseWindow, A_DIM);
                PrintString(std::to_string(y + -textArea.topOffset), textArea.curseWindow, y, (offset - offset) + 1, false);
                wattroff(textArea.curseWindow, A_DIM);  
            }

            append.clear();

            y++;
        } else
        {
            append.push_back(textArea.data[i]);
        }

        textArea.contentHeight++;
    }

    wrefresh(textArea.curseWindow);

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
    textArea->contentHeight = 0;
    textArea->topOffset = 1;
    
    return CurseDriverErrors::NO_ERROR_CURSE;
}


/*! 
    Deleting
*/

/*!
    Interactions
*/

CurseDriverErrors CurseDriver::CheckMenuInteraction(int handle)
{
    Menu& menu = m_menus[GetMenu(handle)];

    int c = wgetch(menu.curseWindow);

    if ((CheckInteractionFocusChange(menu.curseWindow, menu.sizing, c) == false) && m_focused != menu.curseWindow)
    {
        return CurseDriverErrors::NO_ERROR_CURSE;
    }
    
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
        break;
    }

    return CurseDriverErrors::NO_ERROR_CURSE;
}

CurseDriverErrors CurseDriver::CheckTextAreaInteraction(int handle)
{
    TextArea& textArea = m_textAreas[GetTextArea(handle)];

    int c = wgetch(textArea.curseWindow);

    if (CheckInteractionFocusChange(textArea.curseWindow, textArea.sizing, c) == false && m_focused != textArea.curseWindow)
    {
        return CurseDriverErrors::NO_ERROR_CURSE;
    }

    switch(c)
    {
        case KEY_DOWN:
            wscrl(textArea.curseWindow, -1);
            textArea.topOffset -= 1;

            DisplayTextArea(handle);
        break;

        case KEY_UP:
            if (textArea.topOffset < 1)
            {   
                wscrl(textArea.curseWindow, 1);
                textArea.topOffset += 1;

                DisplayTextArea(handle);
            }
        break;
    }

    return CurseDriverErrors::NO_ERROR_CURSE;
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

bool CurseDriver::CheckInteractionFocusChange(WINDOW *window, Sizing bounds, int c)
{
    MEVENT event;

    if(c == KEY_MOUSE)
    {
        if(getmouse(&event) == OK && ClickInBounds(event.y, event.x, bounds) == true)
        {
            m_focused = window;

            return true;
        }
    }

    return false;
}

bool CurseDriver::ClickInBounds(int y, int x, Sizing bounds)
{
    if (y >= bounds.startY && y <= (bounds.startY + bounds.height) && x >= bounds.startX && x <= (bounds.startX + bounds.width))
    {
        return true;
    }

    return false;
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