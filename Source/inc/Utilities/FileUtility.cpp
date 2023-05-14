#include "FileUtility.h"

FileUtility::FileUtility(){}

FileUtility::~FileUtility(){}



std::vector<std::string> FileUtility::GetFileNamesFromDirectory(std::string directoryPath)
{
    std::vector<std::string> names;
    
    DIR *dirInterface;
    struct dirent *directory;

    dirInterface = opendir(directoryPath.c_str());

    if (!dirInterface)
    {
        return names;
    }

    while ((directory = readdir(dirInterface)) != NULL)
    {
        // tmp illegal character mapping see .h
        if (strcmp(".", directory->d_name) || strcmp("..", directory->d_name) )
        {
            names.push_back(directory->d_name);
        }
    }

    closedir(dirInterface);

    return names;
}
