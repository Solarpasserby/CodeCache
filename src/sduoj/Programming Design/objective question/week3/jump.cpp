#include<bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int cnt = 0, ans = 0;

    int input;
    do {
        cin >> input;
        switch (input)
        {
        case 0:
            cout << ans << '\n';
            break;

        case 1:
            cnt = 0;
            ans += 1;
            break;

        case 2:
            cnt++;
            ans += cnt * 2;
            break;
        
        default:
            break;
        }
    } while(input != 0);

    return 0;
}