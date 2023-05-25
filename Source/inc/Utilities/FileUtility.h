#ifndef FILE_UTILITY_H_
#define FILE_UTILITY_H_

#include <iostream>
#include <dirent.h> 
#include <vector>
#include <fstream>
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
        std::vector<std::string> GetShortFileNames(std::vector<std::string> names);
        std::string GetFileContents(std::string path);

    private:
        std::vector<std::string> m_illegals = {".", ".."};

        std::vector<std::string> RemoveIllegalNames(std::vector<std::string> names);

};

#endif
