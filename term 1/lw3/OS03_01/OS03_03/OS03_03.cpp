#include <iostream>
#include <windows.h>

int main() {
    DWORD processes[1024];
    DWORD cbNeeded;

    if (!EnumProcesses(processes, sizeof(processes), &cbNeeded)) {
        std::cerr << "Не удалось получить список процессов." << std::endl;
        return 1;
    }

    DWORD count = cbNeeded / sizeof(DWORD);

    for (DWORD i = 0; i < count; ++i) {
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processes[i]);

        if (hProcess) {
            TCHAR szProcessName[MAX_PATH];
            if (GetModuleBaseName(hProcess, nullptr, szProcessName, sizeof(szProcessName) / sizeof(TCHAR))) {
                std::wcout << szProcessName << std::endl;
            }

            CloseHandle(hProcess);
        }
    }

    return 0;
}