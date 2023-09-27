#include <iostream>
#include <Windows.h>
#include "TlHelp32.h"
#include <iomanip>
using namespace std;

int main()
{
	DWORD pid = GetCurrentProcessId();
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);	// делает снапшот текущих процессов системы
	PROCESSENTRY32 peProcessEntry;						// структура со списком процессов из снапшота
	peProcessEntry.dwSize = sizeof(PROCESSENTRY32);		
	wcout << L"Current PID: " << pid << endl;

	try
	{
		if (!Process32First(snapshot, &peProcessEntry))	
			throw L"Process32First";
		do
		{
			if (peProcessEntry.th32ProcessID == pid)
				wcout << "  ! CURRENTLY RUNNING PROCESS !\n";
			wcout << L"Name\t\t" << peProcessEntry.szExeFile << "\n";
			wcout << L"PID\t\t" << peProcessEntry.th32ProcessID << "\n";
			wcout << L"Parent PID\t" << peProcessEntry.th32ParentProcessID << "\n";
			wcout << L"************************************\n";

		} while (Process32Next(snapshot, &peProcessEntry));
	}
	catch (char* errMessage)
	{
		wcout << L"[ERROR] " << errMessage;
	}

	system("pause");
	return 0;
}