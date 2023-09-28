#include <Windows.h>
#include <iostream>

DWORD  os04_03_T1() {
    DWORD pid = GetCurrentProcessId();
    DWORD tid = GetCurrentThreadId();

    for (int i = 0; i < 50; ++i) {
        Sleep(300);
        std::cout << i << ". t1 PID = " << pid << ", TID = " << tid << std::endl;
    }

    return 0;
}

DWORD  os04_03_T2() {
    DWORD pid = GetCurrentProcessId();
    DWORD tid = GetCurrentThreadId();

    for (int i = 0; i < 125; ++i) {
        Sleep(300);
        std::cout << i << ". t2 PID = " << pid << ", TID = " << tid << std::endl;
    }

    return 0;
}

void main() {
    DWORD pid = GetCurrentProcessId();
    DWORD tid = GetCurrentThreadId();

    DWORD childId_T1, childId_T2 = NULL;

    HANDLE hChild1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)os04_03_T1, NULL, 0, &childId_T1);
    HANDLE hChild2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)os04_03_T2, NULL, 0, &childId_T2);

    for (int i = 0; i < 100; ++i) {
        Sleep(300);
        std::cout << i << ". Parent Thread PID = " << pid << ", TID = " << tid << std::endl;

        if (i == 20) {
            SuspendThread(hChild1);
            SuspendThread(hChild1);
            std::cout << "\n-----------Suspend Thread Child1-------------\n";
        }
        if (i == 60) {
            ResumeThread(hChild1);
            std::cout << "\n-----------Resume Thread Child1-------------\n";
        }
        if (i == 40) {
            SuspendThread(hChild2);
            std::cout << "\n-----------Suspend Thread Child2-------------\n";
        }
    }
    ResumeThread(hChild2);
    std::cout << "\n-----------Resume Thread Child2-------------\n";

    WaitForSingleObject(hChild1, INFINITE);
    WaitForSingleObject(hChild2, INFINITE);

    CloseHandle(hChild1);
    CloseHandle(hChild2); 
}