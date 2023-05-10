#include "CurseDriver.h"

struct Item
{
    char name[FILE_CHARACTER_LIMIT];
};

struct Menu
{
    Item items[MAX_LIST_ITEMS];

};


Menu m_menus[MAX_NR_MENUS];


// todo : implement building the file list and write base code for the curse driver...