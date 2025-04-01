#include <iostream>
#include <vector>
#include <string>
#include <cmath>

struct Big
{
    static const int P = 10000;  // 定义进制，即单个数组元素的上界
    static const int PLEN = 4;   // 即$\log_{10}P$
    static const int MINMUL = 8; // 定义递归终止条件

    std::vector<int> val; // 使用int存储数字0-9999，考虑到乘法可能会产生1e9的数据，因此使用int

    Big();
    Big(const Big &other)
    {
        val.clear();
        for (int i : other.val)
            val.push_back(i);
    }

    // 加法乘法
    Big operator+(const Big &other) const
    {
        
    }
    
    Big operator*(const Big &other) const
    {

    }

    friend std::istream &operator>>(std::istream &is, Big &b)
    {
        std::string s;
        is >> s;
        for (int i = s.length(); i > 0; i -= Big::PLEN)
        {
            int tmp = 0;
            for (int j = std::max(i - Big::PLEN, 0); j < i; ++j)
                tmp = tmp * 10 + (int)(s[j] - '0');
            b.val.push_back(tmp);
        }
    }

    static void output(std::ostream &os, const int &a, int depth)
    {
        if (depth == 4)
            return;
        output(os, a / 10, depth + 1);
        os << (char)(a % 10 + 48);
    }

    friend std::ostream &operator<<(std::ostream &os, const Big &b)
    {
        os << b.val.back();
        for (auto it = b.val.rbegin() + 1; it != b.val.rend(); ++it)
            output(os, *it, 0);
    }
};

Big Big::operator+(const Big &other) const
{
    Big res;

    for (int i = 0; i < Big::N; ++i)
    {
        res.num[i] += num[i] + other.num[i];
        if (res.num[i] >= Big::P) // 超过上界P时进位
        {
            res.num[i + 1] += 1; // 前一位加1
            res.num[i] -= Big::P;
        }
        if (i >= std::max(l, other.l))
            break;
        ++res.l;
    }
    if (res.num[res.l] != 0)
        ++res.l;

    return res;
}

Big Big::operator-(const Big &other) const
{
    Big res;

    for (int i = 0; i < Big::N; ++i)
    {
        res.num[i] += num[i] - other.num[i];
        if (res.num[i] < 0) // 不够减时，向前一位借1
        {
            res.num[i + 1] -= 1; // 前一位减1
            res.num[i] += Big::P;
        }
        if (i >= std::max(l, other.l))
            break;
    }

    res.l = std::max(l, other.l);
    while (res.l > 1 && res.num[res.l - 1] == 0)
        --res.l;

    return res;
}

// Karatsuba 乘法
Big Big::operator*(const Big &other) const
{
    Big res;

    if (l <= Big::MINMUL || other.l <= Big::MINMUL)
    // 数据规模较小时直接计算
    {
        for (int i = 0; i < Big::N; ++i)
        {
            for (int j = 0; j <= i; ++j)
                res.num[i] += num[j] * other.num[i - j];
            if (res.num[i] >= Big::P)
            {
                res.num[i + 1] += res.num[i] / Big::P;
                res.num[i] %= Big::P;
            }
            if (i >= l + other.l)
                break;
        }
    }
    else
    {
        int m = std::max(l, other.l) / 2;
        Big X0, X1, Y0, Y1;
        for (int i = 0; i < m; ++i)
        {
            X0.num[i] = num[i];
            Y0.num[i] = other.num[i];
        }
        for (int i = m; i < std::max(l, other.l); ++i)
        {
            X1.num[i] = num[i];
            Y1.num[i] = other.num[i];
        }
        X0.l = Y0.l = m;
        X1.l = l - m;
        Y1.l = other.l - m;

        Big Z0 = X0 * Y0;
        Big Z1 = (X0 + X1) * (Y0 + Y1);
        Big Z2 = X1 * Y1;

        for (int i = 0; i < Z0.l; ++i)
            res.num[i] += Z0.num[i];
        for (int i = 0; i < Z1.l; ++i)
            res.num[i + m] += Z1.num[i];
        for (int i = 0; i < Z2.l; ++i)
            res.num[i + 2 * m] += Z2.num[i];

        for (int i = 0; i < l + other.l; ++i)
        {
            if (res.num[i] >= Big::P)
            {
                res.num[i + 1] += res.num[i] / Big::P;
                res.num[i] %= Big::P;
            }
        }
    }

    res.l = l + other.l;
    while (res.l > 1 && res.num[res.l - 1] == 0)
        --res.l;

    return res;
}

int main()
{
    Big a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
    std::cout << a * b << '\n';
    // std::cout << a / b << '\n';

    return 0;
}