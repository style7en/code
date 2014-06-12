#include <Windows.h>
#include <stdio.h>
#include <assert.h>

void FindFile(char *cPath)
{
    assert(cPath != NULL);
    
    WIN32_FIND_DATA stWin32FindData;

    char cFileOrDir[MAX_PATH];
    sprintf_s(cFileOrDir, MAX_PATH, "%s*", cPath);

    HANDLE hFile = FindFirstFile(cFileOrDir, &stWin32FindData);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        return ;
    }

    do 
    {
        if (stWin32FindData.cFileName[0] == '.')
        {
            continue;
        }

        if (stWin32FindData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
        {
            sprintf_s(cFileOrDir, MAX_PATH, "%s%s\\", cPath, stWin32FindData.cFileName);
            FindFile(cFileOrDir);
        }
        else
        {
            printf("%s%s\n", cPath, stWin32FindData.cFileName);
        }        
    }while (FindNextFile(hFile, &stWin32FindData));
    
    FindClose(hFile);    
}

int main()
{
    FindFile("D:\\");
    return 0;
}