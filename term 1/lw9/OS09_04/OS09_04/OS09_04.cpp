#define _CRT_NON_CONFORMING_WCSTOK
#define _CRT_SECURE_NO_WARNINGS


#include <iostream>
#include <cstdlib>
#include "Windows.h"

BOOL printWatchRowFileTxt(LPWSTR FileName,DWORD mlsec);

int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    LPWSTR fileName = (LPWSTR)L"D:\\FILES\\University\\3 course\\1 term\\OS\\lab_9\\OS09_01\\OS09_01.txt";

    printWatchRowFileTxt(fileName,50000); 
}

BOOL printWatchRowFileTxt(LPWSTR FileName, DWORD mlsec) 
{
    PLARGE_INTEGER fileSize = new LARGE_INTEGER();
    LPWSTR path = new wchar_t[MAX_PATH + 1];
    LPWSTR cFileName = new wchar_t[wcslen(FileName) * sizeof(char) + 1];

    int i = 0;
    int lenName = 0;
    while (true)
    {
        path[lenName++] = FileName[i++];
        if (FileName[i] == '\0')
        {
            while (path[--lenName] != '\\')
            {
                path[lenName] = '\0';
            }
            path[lenName] = '\0';
            break;
        }
    }
    printf("File catalog:%ls \n", path);
    try
    {
        HANDLE notif = FindFirstChangeNotification(path,false,FILE_NOTIFY_CHANGE_SIZE);
        clock_t t1 = clock();
        clock_t t2 = clock();
        DWORD dwWaitStatus;
        while (true)
        {
            printf("\nWatch started timestamp %d:", t1);
            dwWaitStatus = WaitForSingleObject(notif, INFINITE);
            switch (dwWaitStatus)
            {
                case WAIT_OBJECT_0:
                {
                    if (FindNextChangeNotification(notif) == FALSE)
                    {
                        break;
                    }
                    else
                    {
                        int position = 0;
                        int rowCount = 0;
                        HANDLE of = CreateFile(
                            FileName,
                            GENERIC_READ,
                            FILE_SHARE_READ | FILE_SHARE_WRITE,
                            NULL,
                            OPEN_ALWAYS,
                            FILE_ATTRIBUTE_NORMAL,
                            NULL);
                        if (of == INVALID_HANDLE_VALUE)
                        {
                            CloseHandle(of);
                            throw "Open file failed";
                        }
                        if (GetFileSizeEx(of, fileSize))
                        {
                            char* buf = new char[(fileSize->QuadPart + 1) * sizeof(char)];
                            ZeroMemory(buf, (fileSize->QuadPart + 1) * sizeof(char));
                            DWORD n = NULL;
                            if (ReadFile(of, buf, fileSize->QuadPart, &n, NULL))
                            {
                                while (buf[position++] != '\0')
                                {
                                    if (buf[position] == '\n')
                                    {
                                        rowCount++;
                                    }
                                }
                            }
                        }
                        printf("\n Row quantity: %d", rowCount);
                        CloseHandle(of);
                    }
                }
            }
            t2 = clock();
            if (t2 - t1 > mlsec)
            {
                break;
            }
            mlsec -= (t2 - t1);
        }
        CloseHandle(notif);
        printf("\n Watch ended timestamp %d:", t2);
    }
    catch (const char* err)
    {
        std::cout << "--- Error:\n" << err << "\n";
        return false;
    }
    return true;
}
