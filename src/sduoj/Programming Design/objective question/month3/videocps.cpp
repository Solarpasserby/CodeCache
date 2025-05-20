#include<bits/stdc++.h>

using namespace std;

const int N = 1030;

struct pixel
{
    pixel() {}
    pixel(int16_t _r, int16_t _g, int16_t _b) : R(_r), G(_g), B(_b) {}
    int16_t R, G, B;
};

pixel img[N][N];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int16_t h, w;
    cin >> h >> w;
    for(int i = 1; i <= h; ++i)
    {
        for(int j = 1; j <= w; ++j)
        {
            int16_t r, g, b;
            cin >> r >> g >> b;
            img[i][j] = pixel(r, g, b);
        }
    }

    int cost = 0;
    for(int i = 1; i <= h; ++i)
    {
        for(int j = 1; j <= w; ++j)
        {
            int16_t r, g, b;
            pixel p = img[i][j];
            cin >> r >> g >> b;
            if(p.R != r || p.G != g || p.B != b) ++cost;
        }
    }

    cout << h * w * 24 - cost * 48 << '\n'; 

    return 0;
}
