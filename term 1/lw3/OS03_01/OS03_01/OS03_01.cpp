#include <iostream>
#include <windows.h>

void main() {
    setlocale(LC_ALL, "rus");
    while (true) {
        std::cout << "Идентификатор процесса: " << GetCurrentProcessId() << std::endl;
        Sleep(1000);  // Задержка в миллисекундах
    }
}