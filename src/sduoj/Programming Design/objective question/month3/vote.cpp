#include<iostream>

int main()
{
    int a, b, c;
    std::cin >> a >> b >> c;
    if(a > b && a > c) std::cout << "Bingo\n";
    else std::cout << "gugugu...\n";
    return 0; 
}