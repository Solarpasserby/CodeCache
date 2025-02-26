/**
 * 思考一下
 * f[1][1] = 1 f[1][2] = 1
 * f[2][1] = 2 f[2][2] = choose(2 + 1, 2 * 2) = 4
 * f[3][1] = 3 f[3][2] = choose(3 + 4, 3 * 3) = 
 */

#include<iostream>

using namespace std;

int N, K;
int num[20];
bool reach[250];

int func()
{
    static int m = N, d = 2;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    cin >> N >> K;
    num[1] = 1;

    return 0;
}