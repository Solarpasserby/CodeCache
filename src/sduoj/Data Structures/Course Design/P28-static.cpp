#include <iostream>
#include <string>

struct Big
{
    static const int N = 1000; //定义最大有效位数为1000

    int l; //长度，记录当前有效位
    short num[N+5]; //使用1字节存储数字0-9

    Big();
    Big(const Big &other);

    //四则运算
    Big operator+(const Big &other);
    Big operator-(const Big &other);
    Big operator*(const Big &other);
    Big operator/(const Big &other);
};

Big::Big()
{
    for(int i = 0; i < Big::N; ++i)
        num[i] = 0;
    l = 0;
}

Big::Big(const Big &other)
{
    for(int i = 0; i < Big::N; ++i)
        num[i] = other.num[i];
    l = other.l;
}

Big Big::operator+(const Big &other)
{
    Big res;

    for(int i = 0; i < Big::N; ++i)
    {
        res.num[i] += num[i] + other.num[i];
        if (res.num[i] >= 10)
        {
            res.num[i+1] += 1;
            res.num[i] -= 10;
        }
        if (i >= std::max(l, other.l)) break;
        ++res.l;
    }
    if (res.num[res.l] != 0) ++res.l;

    return res;
}

Big Big::operator-(const Big &other)
{
    Big res;

    for(int i = 0; i < Big::N; ++i)
    {
        res.num[i] += num[i] - other.num[i];
        if (res.num[i] < 0)
        {
            res.num[i+1] -= 1;
            res.num[i] +=10;
        }
        if (i >= std::max(l, other.l)) break;
    }

    res.l = 1;
    for(int i = std::max(l, other.l); i > 0; --i)
    {
        if (res.num[i] != 0)
        {
            res.l = i + 1;
            break;
        }
    }
    
    return res;
}

Big Big::operator*(const Big &other)
{
    Big res;

    for(int i = 0; i < Big::N; ++i)
    {
        for(int j = 0; j <= i; ++j) res.num[i] += num[j] * other.num[i - j];
        if (res.num[i] >= 10)
        {
            res.num[i+1] += res.num[i] / 10;
            res.num[i] %= 10;
        }
        if (i >= l + other.l) break;
    }

    res.l = 1;
    for(int i = l + other.l; i > 0; --i)
    {
        if (res.num[i] != 0)
        {
            res.l = i + 1;
            break;
        }
    }

    return res;
}

Big Big::operator/(const Big &other)
{
    Big res;
    Big rest(*this);

    for(int i = l - other.l; i >= 0; --i)
    {
        short tmp = -1;
        while(rest.num[l] == 0)
        {
            for(int j = i; j < l; ++j)
            {
                rest.num[j] -= other.num[j - i];
                if(rest.num[j] < 0)
                {
                    rest.num[j+1] -= 1;
                    rest.num[j] += 10;
                }
            }
            ++tmp;
        }
        for(int j = i; j < l; ++j)
        {
            rest.num[j] += other.num[j - i];
            if(rest.num[j] >= 10)
            {
                rest.num[j+1] += 1;
                rest.num[j] -= 10;
            }
        }
        res.num[i] = tmp;
    }

    res.l = 1;
    for(int i = l - other.l; i >= 0; --i)
    {
        if (res.num[i] != 0)
        {
            res.l = i + 1;
            break;
        }
    }

    return res;
}

//重载输入
std::istream& operator>>(std::istream& is, Big& n)
{
    std::string s;
    is >> s;

    n.l = s.length();
    for(int i = 0; i < n.l && i < Big::N; ++i)
        n.num[i] = s[n.l - i - 1] - '0';
    return is;
}

//重载输出
std::ostream& operator<<(std::ostream& os, const Big& n)
{
    short tmp[Big::N];
    int i = 0;
    for(;i < n.l; ++i)
        tmp[i] = n.num[i];
    while(i)
        os << (char)(tmp[--i] + 48);
    return os;
}

int main()
{
    Big a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
    std::cout << a - b << '\n';
    std::cout << a * b << '\n';
    std::cout << a / b << '\n';

    return 0;
}