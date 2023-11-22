#include <iostream>
#include <vector>

void main() 
{
    setlocale(0, "");
    const int PAGES = 256;
    const int PAGE_SIZE = 4096;
    std::vector<int> memory(PAGES * PAGE_SIZE / sizeof(int));

    for (int i = 0; i < memory.size(); ++i) 
    {
        memory[i] = i;
    }

    memory[0] = 0xCF;  //п
    memory[1] = 0xF3;  //у
    memory[2] = 0xE7;  //з

    // номер страницы 207, смещение = 3902
    //int page = memory[0];
    //int offset = (memory[1] << 4) | memory[2];
    //int value = memory[page * PAGE_SIZE / sizeof(int) + offset];int
    auto v = memory[0] * 1024 + 3902; //34B3E
    std::cout << "Значение в байте с адресом "<< v << std::endl;// page << ", " << offset << ": " << value << std::endl; 
}