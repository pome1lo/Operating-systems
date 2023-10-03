#include <iostream>
#include <cstdlib>
#include "Windows.h"

using namespace std;

void main(int argc, char* argv[])
{
	try {
		if (argc == 4) {
			char buf[10];
			int p1 = atoi(argv[1]);
			int p2 = atoi(argv[2]);
			int p3 = atoi(argv[3]);
			if (!SetProcessAffinityMask(GetCurrentProcess(), p1)) {
				throw "SetProcessAffinityMask";
			}

			_itoa_s(p1, buf, 2);
			cout << "processAffinityMask: " << buf << endl;
			cout << "processPriorityClass1: " << p2 << endl;
			cout << "processPriorityClass2: " << p3 << endl;

			LPCWSTR an1 = L"D:\\FILES\\University\\3 course\\1 term\\OS\\lw5\\OS05_01\\x64\\Debug\\os05_02x.exe";
			LPCWSTR an2 = L"D:\\FILES\\University\\3 course\\1 term\\OS\\lw5\\OS05_01\\x64\\Debug\\os05_02x.exe";
			STARTUPINFO si1, si2;
			PROCESS_INFORMATION pi1, pi2;
			ZeroMemory(&si1, sizeof(STARTUPINFO)); ZeroMemory(&si2, sizeof(STARTUPINFO));
			si1.cb = sizeof(STARTUPINFO); si2.cb = sizeof(STARTUPINFO);

			if (CreateProcess(an1, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE | p2, NULL, NULL, &si1, &pi1)) {
				cout << "--Process os05_02 1 created\n";
			}
			else {
				cout << "--Process os05_02 1 not created\n";
			}

			if (CreateProcess(an2, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE | p3, NULL, NULL, &si2, &pi2)) {
				cout << "--Process os05_02 2 created\n";
			}
			else {
				cout << "--Process os05_02 2 not created\n";
			}

			WaitForSingleObject(pi1.hProcess, INFINITE);
			WaitForSingleObject(pi2.hProcess, INFINITE);

			CloseHandle(pi1.hProcess);
			CloseHandle(pi2.hProcess);
		}
		else {
			cout << "No arguments" << endl;
		}
	}
	catch (string err) {
		cout << err << endl;
	}
}