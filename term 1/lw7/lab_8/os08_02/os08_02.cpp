#include <Windows.h>
#include <iostream>
#include <ctime>

void main() {
	clock_t start = clock();

	int k = 0;
	bool flag5 = true, flag10 = true;
	while (true) {
		k++;
		if ((clock() - start) / CLOCKS_PER_SEC == 5 && flag5) {
			std::cout << "@ Iterations after 5 sec = " << k << '\n';
			flag5 = false;
		}
		if ((clock() - start) / CLOCKS_PER_SEC == 10 && flag10) {
			std::cout << "@ Iterations after 10 sec = " << k << '\n';
			flag10 = false;
		}
		if ((clock() - start) / CLOCKS_PER_SEC == 15) {
			std::cout << "@ Iterations after 15 sec = " << k << '\n';
			break;
		}
	}
	std::cout << "os08_02 done\n"; 
}