#include <iostream>
#include <windows.h>

void childProcess(const char* processName, int iterations) {
    for (int i = 0; i < iterations; ++i) {
        std::cout << "Идентификатор процесса " << processName << ": " << GetCurrentProcessId() << std::endl;
        Sleep(1000);  // Задержка в миллисекундах
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    const int iterationsParent = 100;
    const int iterationsChild1 = 50;
    const int iterationsChild2 = 125;


    STARTUPINFO si1, si2;
    PROCESS_INFORMATION pi1, pi2;

    ZeroMemory(&si1, sizeof(si1));
    ZeroMemory(&si2, sizeof(si2));
    si1.cb = sizeof(si1);
    si2.cb = sizeof(si2);

    // Создание процесса OS03_02_1
    if (!CreateProcess(
        nullptr,
        const_cast<char*>("OS03_02_1.exe"),
        nullptr,
        nullptr,
        FALSE,
        0,
        nullptr,
        nullptr,
        &si1,
        &pi1)) {
        std::cerr << "Не удалось создать процесс OS03_02_1." << std::endl;
        return 1;
    }

    // Создание процесса OS03_02_2
    if (!CreateProcess(
        nullptr,
        const_cast<char*>("OS03_02_2.exe"),
        nullptr,
        nullptr,
        FALSE,
        0,
        nullptr,
        nullptr,
        &si2,
        &pi2)) {
        std::cerr << "Не удалось создать процесс OS03_02_2." << std::endl;
        return 1;
    }

    // Выполнение цикла в основном процессе
    childProcess("OS03_02", iterationsParent);

    // Ожидание завершения дочерних процессов
    WaitForSingleObject(pi1.hProcess, INFINITE);
    WaitForSingleObject(pi2.hProcess, INFINITE);

    //// Закрытие дескрипторов дочерних процессов
    CloseHandle(pi1.hProcess);
    CloseHandle(pi2.hProcess);
}