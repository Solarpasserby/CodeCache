/**
 * 思考一下
 * f[1][1] = 1 f[1][2] = 1
 * f[2][1] = 2 f[2][2] = choose(2 + 1, 2 * 2) = 4
 * f[3][1] = 3 f[3][2] = choose(3 + 4, 3 * 3) = 
 */

#include<iostream>

using namespace std;

int N, K, maxExp;
int num[20];

int func(int rLimit)
{
    static int cardNum = 1, maxReach = 0, reach = 0;
    static bool isContinue = true;
    for(int i = 0; i <= rLimit && isContinue; i++)
    {
        reach += num[i];
        if (cardNum != N)
        {
            ++cardNum;
            func(i);
            --cardNum;
        }
        else if(reach > maxReach)
        {
            if (reach - maxReach == 1) maxReach = reach;
            else isContinue = false;
        }
        reach -= num[i];
    }

    return maxReach;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    cin >> N >> K;
    num[1] = 1;
    num[2] = 4;
    num[3] = 5;

    maxExp = func(K);

    cout << maxExp << '\n'; 

    return 0;
}