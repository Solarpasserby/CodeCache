#include <iostream>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    char a, b, c;
    a = getchar();
    b = getchar();
    c = getchar();

    if (a == b && a == c) std::cout << "Won" << '\n';
    else std::cout << "Lost" << '\n';

    return 0;
}