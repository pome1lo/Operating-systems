#include <Windows.h>
#include <iostream>

void main()
{
    DWORD pid = GetCurrentProcessId();
    DWORD tid = GetCurrentThreadId();

    for (int i = 0; i < 10000; i++) {
        Sleep(200);
        std::cout << "PID = " << pid << ", TID = " << tid << "\n";     
    }
}