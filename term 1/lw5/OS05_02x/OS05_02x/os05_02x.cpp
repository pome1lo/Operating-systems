﻿#include <iostream>
#include "Windows.h"

using namespace std;

void getProcessPriority(HANDLE hp); //приоритетный класс процесса 
void getThreadPriority(HANDLE ht);
void getAffinityMask(HANDLE hp, HANDLE ht);

void main()
{
	HANDLE hp = GetCurrentProcess();
	HANDLE ht = GetCurrentThread();
	DWORD pid = GetCurrentProcessId();
	DWORD tid = GetCurrentThreadId();

	for (int i = 0; i < 1000000; i++) {
		if (i % 1000 == 0) {
			cout << "Iteration: " << i << endl;
			cout << "PID: " << pid << endl << "TID: " << tid << endl;
			getProcessPriority(hp);
			getThreadPriority(ht);
			getAffinityMask(hp, ht);

			Sleep(200);
		}
	}
}

void getProcessPriority(HANDLE hp) {
	DWORD prty = GetPriorityClass(hp);

	cout << prty << endl;

	switch (prty) {
		case IDLE_PRIORITY_CLASS: cout << "ProcessPriority: IDLE_PRIORITY_CLASS\n"; break;
		case BELOW_NORMAL_PRIORITY_CLASS: cout << "ProcessPriority: BELOW_NORMAL_PRIORITY_CLASS\n"; break;
		case NORMAL_PRIORITY_CLASS: cout << "ProcessPriority: NORMAL_PRIORITY_CLASS\n"; break;
		case ABOVE_NORMAL_PRIORITY_CLASS: cout << "ProcessPriority: ABOVE_NORMAL_PRIORITY_CLASS\n"; break;
		case HIGH_PRIORITY_CLASS: cout << "ProcessPriority: HIGH_PRIORITY_CLASS\n"; break;
		case REALTIME_PRIORITY_CLASS: cout << "ProcessPriority: REALTIME_PRIORITY_CLASS\n"; break;
	default: cout << "?\n\n"; break;
	}
}

void getThreadPriority(HANDLE ht) {
	DWORD prty = GetPriorityClass(ht);
	cout << "ThreadPriority: " << GetThreadPriority(ht) << endl;
}

void getAffinityMask(HANDLE hp, HANDLE ht) {
	DWORD icpu = -1;
	icpu = SetThreadIdealProcessor(ht, MAXIMUM_PROCESSORS);
	cout << "Thread IdealProcessor: " << dec << icpu << endl << endl;
}