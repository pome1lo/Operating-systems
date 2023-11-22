#include <Windows.h>
#include <iostream>

void sh(HANDLE heap) {
    PROCESS_HEAP_ENTRY entry;
    entry.lpData = NULL;
    SIZE_T totalSize = 0, allocatedSize = 0, unallocatedSize = 0;

    while (HeapWalk(heap, &entry) != FALSE) {
        if (entry.wFlags & PROCESS_HEAP_REGION) {
            totalSize += entry.Region.dwCommittedSize;
            allocatedSize += entry.Region.dwCommittedSize - entry.Region.dwUnCommittedSize;
            unallocatedSize += entry.Region.dwUnCommittedSize;
        }
    }

    std::cout << "Общий размер heap: " << totalSize << std::endl;
    std::cout << "Размер распределенной области памяти heap: " << allocatedSize << std::endl;
    std::cout << "Размер нераспределенной области памяти heap: " << unallocatedSize << std::endl;
}

int main() {
    setlocale(LC_ALL, "rus");
    HANDLE heap = GetProcessHeap();

    std::cout << "Информация до размещения массива:" << std::endl;
    sh(heap);

    //SIZE_T size = 300000 * sizeof(int);
    //int* m = static_cast<int*>(HeapAlloc(heap, 0, size));
    int* m = new int[300000];

    std::cout << "Информация после размещения массива:" << std::endl;
    sh(heap);

    HeapFree(heap, 0, m);


    return 0;
}