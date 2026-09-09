#include <iostream>
#include <fstream>
#include <string>
#include <nonstd/expected.hpp>

#include "coolutil.hpp"
//#include <os.hpp>

#include <sys/stat.h>
#include <sys/types.h>

#if defined(_WIN32)
#include <direct.h>
#include <io.h>
#include <lmcons.h>
#include <shlobj.h>
#include <shlwapi.h>
#include <windows.h>
#elif defined(__HAIKU__)
#include <FindDirectory.h>
#include <Path.h>
#else
#include <dirent.h>
#include <pwd.h>
#include <unistd.h>
#endif

bool fileExists(const std::string& filename)
{
    std::ifstream file(filename);
    return file.is_open();
}

std::string parentPath(const std::string &path)
{
    size_t pos = path.find_last_of("/\\");
    if (std::string::npos != pos) return path.substr(0, pos);
    return "";
}

nonstd::expected<std::vector<std::string>, std::string> listDirectory(const std::string &path) //stolen from scratch everywhere
{
    std::vector<std::string> files;

    #if defined(_WIN32)
    std::string searchPath = path;
    if (searchPath.empty()) {
        searchPath = ".";
    }
    if (searchPath.back() != '/' && searchPath.back() != '\\') {
        searchPath += "/*";
    } else {
        searchPath += "*";
    }

    std::wstring wsearchPath(searchPath.size(), L' ');
    wsearchPath.resize(std::mbstowcs(&wsearchPath[0], searchPath.c_str(), searchPath.size()));

    WIN32_FIND_DATAW findData;
    HANDLE hFind = FindFirstFileW(wsearchPath.c_str(), &findData);

    if (hFind == INVALID_HANDLE_VALUE) {
        return nonstd::make_unexpected("Failed to open directory, " + path + ", " + std::to_string(GetLastError()));
    }

    do {
        int size_needed = WideCharToMultiByte(CP_UTF8, 0, findData.cFileName, -1, NULL, 0, NULL, NULL);
        std::string fileName(size_needed - 1, 0);
        WideCharToMultiByte(CP_UTF8, 0, findData.cFileName, -1, &fileName[0], size_needed, NULL, NULL);

        if (fileName != "." && fileName != "..") {
            files.push_back(fileName);
        }
    } while (FindNextFileW(hFind, &findData) != 0);

    FindClose(hFind);

    #else
    DIR *dir = opendir(path.c_str());
    if (dir == nullptr) {
        return nonstd::make_unexpected("Failed to open directory, " + path + ", " + std::to_string(errno));
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != nullptr) {
        const std::string fileName = entry->d_name;
        if (fileName != "." && fileName != "..") {
            files.push_back(fileName);
        }
    }

    closedir(dir);
    #endif

    return files;
}