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
        names.push_back(directory->d_name);
    }

    std::vector<std::string> filtered = RemoveIllegalNames(names);

    closedir(dirInterface);

    return filtered;
}


std::vector<std::string> FileUtility::RemoveIllegalNames(std::vector<std::string> names)
{
    std::vector<std::string> filtered;
    // long unsigned int illegalIndex = 0;
    bool approved = true;
    
    for (long unsigned int i = 0; i < names.size(); i++)
    {
        approved = true;
        
        for (long unsigned int x = 0; x < m_illegals.size(); x++)
        {
            if (names[i].compare(m_illegals[x]) == 0)
            {
                approved = false;
            }   
        }

        if (approved == true)
        {
            filtered.push_back(names[i]);
        }

        // illegalIndex++;

        // if (illegalIndex >= m_illegals.size())
        // {
        //     illegalIndex = 0;
        // }
    }

    return filtered;
}
