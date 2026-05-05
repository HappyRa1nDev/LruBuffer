#include "LruBuffer.h"
#include <iostream>

int main() {
    LruBuffer<int, int> buffer(2);

    buffer.set(1, 10);
    buffer.set(2, 20);

    std::cout << buffer.get(1) << std::endl;

    buffer.set(3, 30);

    std::cout << buffer.check(1) << std::endl;
    std::cout << buffer.check(2) << std::endl;
    std::cout << buffer.check(3) << std::endl;

    buffer.erase(1);
    std::cout << buffer.check(1) << std::endl;

    return 0;
}
