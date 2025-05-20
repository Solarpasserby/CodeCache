#include <iostream>
#include <string>
#include <vector>
#include <cmath>

struct Big
{
    static const int P = 10000; //定义进制，即单个数组元素的上界
    static const int PLEN = 4; //即$\log_{10}P$
    static const int MINMUL = 8; //定义递归终止条件 

    std::vector<int> data; //使用int存储数字0-9999，考虑到乘法可能会产生1e9的数据，因此使用int

    Big() {data.clear();}
    Big(const Big &other);

    //四则运算
    Big operator+(const Big &other) const;
    Big operator-(const Big &other) const;
    Big operator*(const Big &other) const;
    // Big operator/(const Big &other) const; TODO
};

Big::Big(const Big &other)
{
    for(auto a: other.data)
        data.push_back(a);
}

Big Big::operator+(const Big &other) const
{
    Big res;
    int maxl = std::max(data.size(), other.data.size());

    res.data.assign(maxl+1, 0);
    for(int i = 0; i < maxl; ++i)
    {
        int ta, tb;
        ta = i < data.size() ? data[i] : 0;
        tb = i < other.data.size() ? other.data[i] : 0;
        res.data[i] += ta + tb;
        if (res.data[i] >= Big::P) //超过上界P时进位
        {
            res.data[i+1] += 1; //前一位加1
            res.data[i] -= Big::P;
        }
    }
    while(res.data.back() == 0) res.data.pop_back();

    return res;
}

Big Big::operator-(const Big &other) const
{
    Big res;
    int maxl = std::max(data.size(), other.data.size());

    res.data.assign(maxl, 0);
    for(int i = 0; i < maxl; ++i)
    {
        int ta, tb;
        ta = i < data.size() ? data[i] : 0;
        tb = i < other.data.size() ? other.data[i] : 0;
        res.data[i] += ta - tb;
        if (res.data[i] < 0) //不够减时，向前一位借1
        {
            res.data[i+1] -= 1; //前一位减1
            res.data[i] += Big::P;
        }
    }
    while(res.data.back() == 0) res.data.pop_back();
    
    return res;
}

//Karatsuba 乘法
Big Big::operator*(const Big &other) const
{
    Big res;
    int maxl = data.size()+other.data.size();
    res.data.assign(maxl+1, 0);

    if (data.size() <= Big::MINMUL || other.data.size() <= Big::MINMUL) //数据规模较小时直接计算
    {
        for(int i = 0; i < maxl; ++i)
        {
            for(int j = 0; j <= i; ++j)
            {
                int ta, tb;
                ta = j < data.size() ? data[j] : 0;
                tb = i - j < other.data.size() ? other.data[i - j] : 0;
                res.data[i] += ta * tb;
                if (res.data[i] >= Big::P)
                {
                    res.data[i+1] += res.data[i] / Big::P;
                    res.data[i] %= Big::P;
                }
            }
        }
    }
    else
    {
        int m = std::max(data.size(), other.data.size()) / 2;
        m = std::min((int)std::min(data.size(), other.data.size()), m);
        Big X0, X1, Y0, Y1;
        X0.data.assign(data.begin(), data.begin()+m);
        X1.data.assign(data.begin()+m, data.end());
        Y0.data.assign(other.data.begin(), other.data.begin()+m);
        Y1.data.assign(other.data.begin()+m, other.data.end());

        Big Z0 = X0 * Y0;
        Big Z1 = (X0 + X1) * (Y0 + Y1);
        Big Z2 = X1 * Y1;
        Z1 = Z1 - Z0 - Z2;

        for (int i = 0; i < Z0.data.size(); ++i)
        res.data[i] += Z0.data[i];
        for (int i = 0; i < Z1.data.size(); ++i)
        res.data[i + m] += Z1.data[i];
        for (int i = 0; i < Z2.data.size(); ++i)
        res.data[i + 2 * m] += Z2.data[i];

        for (int i = 0; i < maxl; ++i)
        {
            if (res.data[i] >= Big::P)
            {
                res.data[i + 1] += res.data[i] / Big::P;
                res.data[i] %= Big::P;
            }
        }
    }
    while(res.data.back() == 0) res.data.pop_back();

    return res;
}

//重载输入
std::istream& operator>>(std::istream& is, Big& n)
{
    int len;
    std::string s;
    is >> s;

    len = s.length();
    n.data.resize((len+3)/4);
    for(int i = 0; i < len; ++i)
        n.data[i / Big::PLEN] += (s[len - i - 1] - '0') * pow(10, i % Big::PLEN);
    return is;
}

void outputEle(std::ostream&os, const int &a, int depth)
{
    if (depth == 4) return;
    outputEle(os, a / 10, depth + 1);
    os << (char)(a % 10 + 48);
}

void outputFirst(std::ostream&os, const int &a)
{
    if (a == 0) return;
    outputFirst(os, a / 10);
    os << (char)(a % 10 + 48);
}

//重载输出
std::ostream& operator<<(std::ostream& os, const Big& n)
{
    std::vector<int> tmp = n.data;
    int i = n.data.size()-1;
    if(n.data[i] == 0)
        os << '0';
    else
        outputFirst(os, n.data[i]);
    while(i)
        outputEle(os, n.data[--i], 0);
    return os;
}

int main()
{
    for(int i = 0; i < 1000; ++i)
    {
        Big a, b;
        std::cin >> a >> b;
        std::cout << a * b << '\n';
    }

    return 0;
}