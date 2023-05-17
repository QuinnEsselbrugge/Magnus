#ifndef FILE_UTILITY_H_
#define FILE_UTILITY_H_

#include <iostream>
#include <dirent.h> 
#include <vector>
#include <string>
#include <string.h>


class FileUtility
{

    /*

        This file utility will assume full target names to find its targets...

    */


    public:
        FileUtility();
        ~FileUtility();

        std::vector<std::string> GetFileNamesFromDirectory(std::string directoryPath);


    private:
        std::vector<std::string> m_illegals = {".", ".."};
    // todo: disallow illegal characters, some kind of public mapping for stuff to be ignored...
        std::vector<std::string> RemoveIllegalNames(std::vector<std::string> names);

};

#endif
