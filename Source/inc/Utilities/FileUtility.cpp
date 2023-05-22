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
        names.push_back(directoryPath + directory->d_name);
    }

    closedir(dirInterface);

    return names;
}

std::vector<std::string> FileUtility::GetShortFileNames(std::vector<std::string> names)
{
    std::vector<std::string> filtered;

    if (names.size() <= 0)
    {
        return names;
    }

    for (long unsigned int i = 0; i < names.size(); i++)
    {

        int res = names[i].find_last_of("/");

        std::string out = names[i].substr(res + 1, names[i].size() - res);

        filtered.push_back(out);
    }

    filtered = RemoveIllegalNames(filtered);

    return filtered;
}


std::vector<std::string> FileUtility::RemoveIllegalNames(std::vector<std::string> names)
{
    std::vector<std::string> filtered;

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
    }

    return filtered;
}


std::string FileUtility::GetFileContents(std::string path)
{
    if (path.size() <= 0)
    {
        return path;
    }

      std::ifstream ifs(path);
      std::string content
      ( 
          (
              std::istreambuf_iterator<char>(ifs) 
          ),
          (
              std::istreambuf_iterator<char>()    
          ) 
        );

        return content;
}
