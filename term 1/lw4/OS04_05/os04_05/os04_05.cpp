#include <Windows.h>
#include <iostream>

DWORD os04_05_T1() {
    DWORD pid = GetCurrentProcessId();
    DWORD tid = GetCurrentThreadId();

    for (int i = 0; i < 50; ++i) {
        Sleep(1000);
        std::cout << i << ". t1 PID = " << pid << ", TID = " << tid << std::endl;
    }

    return 0;
}

DWORD  os04_05_T2() {
    DWORD pid = GetCurrentProcessId();
    DWORD tid = GetCurrentThreadId();

    for (int i = 0; i < 125; ++i) {
        Sleep(1000);
        std::cout << i << ". t2 PID = " << pid << ", TID = " << tid << std::endl;
    }

    return 0;
}

void main() {
    DWORD pid = GetCurrentProcessId();
    DWORD tid = GetCurrentThreadId();

    DWORD childId_T1, childId_T2 = NULL;

    HANDLE hChild1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)os04_05_T1, NULL, 0, &childId_T1);
    HANDLE hChild2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)os04_05_T2, NULL, 0, &childId_T2);

    for (int i = 0; i < 100; ++i) {
        Sleep(200);
        std::cout << i << ". Parent Thread PID = " << pid << ", TID = " << tid << std::endl;

        if (i == 40) {
            std::cout << "\n-----------os04_05_T2 - Killed----------\n";
            TerminateThread(hChild2, -1);
        }
    }

    WaitForSingleObject(hChild1, INFINITE);
    WaitForSingleObject(hChild2, INFINITE);

    CloseHandle(hChild1);
    CloseHandle(hChild2); 
} 