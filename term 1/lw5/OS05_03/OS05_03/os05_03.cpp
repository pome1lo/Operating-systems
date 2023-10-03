#include <iostream>
#include <cstdlib>
#include "Windows.h"

using namespace std;

HANDLE createThread(int threadPriority);
DWORD WINAPI os05_03();

void getProcessPriority(HANDLE hp);
void getThreadPriority(HANDLE ht);
void getAffinityMask(HANDLE hp, HANDLE ht);

void main(int argc, char* argv[])
{
	if (argc == 5) {
		char buf[10];
		int p1 = atoi(argv[1]);
		int p2 = atoi(argv[2]);
		int p3 = atoi(argv[3]);
		int p4 = atoi(argv[4]);

		_itoa_s(p1, buf, 2);
		cout << "processAffinityMask: " << buf << endl;
		cout << "processPriorityClass: " << p2 << endl;
		cout << "threadPriority1: " << p3 << endl;
		cout << "threadPriority2: " << p4 << endl;

		HANDLE h = GetCurrentProcess();

		SetPriorityClass(h, p2);
		SetProcessAffinityMask(h, p1);

		HANDLE thread1 = createThread(p3);
		HANDLE thread2 = createThread(p4);

		ResumeThread(thread1);
		ResumeThread(thread2);

		HANDLE threads[] = { thread1, thread2 };

		WaitForMultipleObjects(2, threads, TRUE, INFINITY);
		CloseHandle(thread1);
		CloseHandle(thread2);
	}
	else {
		cout << "No arguments" << endl;
	} 

	system("pause");
}

HANDLE createThread(int threadPriority) {

	DWORD ChildId = NULL;
	HANDLE h = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)os05_03, NULL, CREATE_SUSPENDED, &ChildId);

	SetThreadPriority(h, threadPriority);

	return h;
}

DWORD WINAPI os05_03() {

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

	system("pause");
	return 0;
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
