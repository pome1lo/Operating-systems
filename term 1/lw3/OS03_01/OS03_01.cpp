#include <iostream>
#include <Windows.h>
using namespace std;

void main()
{
	for (short i = 1; i <= 10000; ++i)
	{
		cout << i << ") PID = " << GetCurrentProcessId() << "\n";
		Sleep(1000);
	}
}
// 1. Task Manager:				Диспетчер задач -> Сведенья -> OS03_01.exe
// 2. Tasklist:					tasklist
// 3. PowerShell ISE:			Get-Process OS03_01  (chcp 1251 для кодировки)
// 4. Performance Monitor:		Монитор ресурсов