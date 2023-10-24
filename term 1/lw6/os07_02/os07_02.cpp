﻿#include <iostream>
#include <Windows.h>
//Поочередно с 30 до 60

DWORD pid = NULL;

DWORD WINAPI ChildThrOne();
DWORD WINAPI ChildThrTwo();

CRITICAL_SECTION cs;

int main() {
	pid = GetCurrentProcessId();
	DWORD tid = GetCurrentThreadId();
	DWORD OneId = NULL, TwoId = NULL;

	HANDLE hOne = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThrOne, NULL, 0, &OneId);
	HANDLE hTwo = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThrTwo, NULL, 0, &TwoId);

	// инициализация критической секци
	InitializeCriticalSection(&cs);
	for (int i = 0; i < 90; i++) {
		if (i == 30) {
			EnterCriticalSection(&cs);
			std::cout << "\n\tMAIN THREAD is entering critical section\n";
			std::cout << "--------------------------------------------------------\n";
		}
		if (i == 60) {
			std::cout << "\n\MAIN THREAD is leaving critical section\n";
			LeaveCriticalSection(&cs);
		}

		std::cout << "Main PID = " << pid << ", Parent Thread: " << "tid - " << tid << ": " << i << '\n';
		Sleep(100);
	}

	WaitForSingleObject(hOne, INFINITE);
	WaitForSingleObject(hTwo, INFINITE);

	DeleteCriticalSection(&cs);

	CloseHandle(hOne);
	CloseHandle(hTwo);
	system("pause");
}

DWORD WINAPI ChildThrOne() {
	DWORD tid = GetCurrentThreadId();
	for (int i = 0; i < 90; i++) {
		if (i == 30) {
			EnterCriticalSection(&cs);
			std::cout << "\n\tThr_1 is entering critical section\n";
			std::cout << "--------------------------------------------------------\n";
		}

		if (i == 60) {
			std::cout << "\n\tThr_1 is leaving critical section\n";
			LeaveCriticalSection(&cs);
		}

		std::cout << "First PID = " << pid << ", Child Thread: tid- " << tid << ": " << i << '\n';
		Sleep(100);
	}
	LeaveCriticalSection(&cs);
	return 0;
}

DWORD WINAPI ChildThrTwo() {
	DWORD tid = GetCurrentThreadId();
	for (int i = 0; i < 90; i++) {
		if (i == 30) {
			EnterCriticalSection(&cs);
			std::cout << "\n\tThr_2 is entering critical section\n";
			std::cout << "--------------------------------------------------------\n";
		}
		if (i == 60) {
			std::cout << "\n\tThr_2 is leaving critical section\n";
			LeaveCriticalSection(&cs);
		}
			
		std::cout << "Second PID = " << pid << ", Child Thread: tid- " << tid << ": " << i << '\n';
		Sleep(100);
	}
	LeaveCriticalSection(&cs);
	return 0;
}