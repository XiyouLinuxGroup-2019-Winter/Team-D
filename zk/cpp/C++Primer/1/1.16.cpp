#include <iostream>
#include "Sales_item.h"

int main()
{
    int v1 = 0;
    int sum = 0;
    while (std::cin >> v1) {
        sum += v1;
    }
    std::cout << sum << std::endl;
    return 0;
}

