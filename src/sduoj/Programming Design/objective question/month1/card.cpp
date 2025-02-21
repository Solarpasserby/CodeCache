#include<iostream>

using namespace std;

int A, B, a[30], b[4], p[10];
bool card[25][4];

#define Ann
// #define Cnn

void judgeType()
{
    int c2 = 0, c3 = 0;

    for (int i = 0; i < B; i++)
        if (b[i] == 5)
        {
            for (int j = 0; j < A; j++)
            {
                if (a[j] == 0) continue;
                else if (a[j+1] == 1 && a[j+2] == 1 && a[j+3] == 1 && a[j+4] == 1)
                {
                    ++p[1];
                    return;
                }
                else
                {
                    ++p[4];
                    return;
                }
            }
        }

    for (int i = 0; i < A; i++)
    {
        switch (a[i])
        {
        case 4:
            ++p[2];
            return;

        case 3:
            ++c3;
            break;

        case 2:
            ++c2;
            break;

        case 1:
            if (c2 || c3) continue;
            else if (a[i+1] == 1 && a[i+2] == 1 && a[i+3] == 1 && a[i+4] == 1)
            {
                ++p[5];
                return;
            }
            else continue;
        
        default:
            break;
        }
    }

    if (c3)
    {
        if (c2) ++p[3];
        else ++p[6];
        return;
    }
    if (c2)
    {
        if (c2 == 2) ++p[7];
        else ++p[8];
        return;
    }

    ++p[9];
    return;
}

void func()
{
    static int time = 2;
    ++time;

#ifdef Ann
    for (int i = 0; i < A; i++)
        for (int j = 0; j < B; j++)
        {
            if (card[i][j]) continue;
            else
            {
                ++a[i];
                ++b[j];
                if (time == 5) judgeType();
                else
                {
                    card[i][j] = true;
                    func();
                    card[i][j] = false;
                }
                --a[i];
                --b[j];
            }
        }
#endif

#ifdef Cnn
    for (int i = 0; i < A; i++)
        for (int j = 0; j < B; j++)
        {
            if (card[i][j]) continue;
            else
            {
                ++a[i];
                ++b[j];
                
                /**
                 * 好吧我不会写选择...
                 * 应该能写，但是感觉有点复杂
                 * 这里的实现是全排列然后再除以6...
                 */

                --a[i];
                --b[j];
            }
        }
#endif

    --time;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int a1, b1, a2, b2;

    cin >> A >> B >> a1 >> b1 >> a2 >> b2;
    card[a1][b1] = card[a2][b2] = true;
    ++a[a1], ++b[b1], ++a[a2], ++b[b2];
    
    func();
    for (int i = 1; i < 10; i++)
#ifdef Ann
        cout << p[i] / 6 << ' ';
#endif
#ifdef Cnn
        cout << p[i] << ' ';
#endif
    cout << '\n';

    return 0;
}