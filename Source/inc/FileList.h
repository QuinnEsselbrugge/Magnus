#ifndef FILE_LIST_H
#define FILE_LIST_H_

#include "WidgetErrors.h"

// Stddef for widgets

class FileList
{

    public:
        FileList(/* args */);
        ~FileList();
        
        WidgetErrors Build(int *pos);

    private:
};


#endif