## Week1
#### Question1

(1)
$$
O(\log(\log(n)))\\
O(n)\\
O(n^8)\\
O(n!)\\
O(n^{16})\\
O(e^n)
$$

(2)
$$
f_4(n)=n^8+n!\\
f_6(n)=e^n+e^{16}\\
f_5(n)=n^{16}+n\log n\\
f_3(n)=n^8\\
f_2(n)=2^{\log_{2}n}\\
f_1(n)=\log(\log(n))
$$

------

#### Question2

(1)

$O(\sqrt{n})$

(2)

算法描述的应该是求解n的算术立方根的两个相邻的整数，其中变量y和j记录结果，且每次变化加一。因此可以得到函数步数 $f(x)=\lfloor \sqrt{n} \rfloor$，故时间复杂度为 $O(\sqrt{n})$

------

#### Question3

(1)

$O(n^2\log n)$

(2)

先处理外层循环，k初值为$n^2$，每次循环除以2，相当于进行$\lfloor \log_{2}n \rfloor$次循环。再看内层循环，其中j以步长1从0加至$n^2$，进行了$n^2+1$ 次循环。故得到总函数步数$f(x)= (n^2+1)\lfloor \log_{2}n \rfloor$，时间复杂度为$O(n^2\log n)$

------

#### Question4

(1)

$O(1)$

(2)

整个程序的运行步数与n无关，为固定常数，因此时间复杂度为$O(1)$

------

#### Question5

说明张三编写的程序不能处理题面下的所有情况。体面提供的样例只是题面有限的情况，张三的程序在题面样例的情况下可以返回正确结果，但对于某些题面中的特殊情况便稍显逊色。这很可能是在一些细节的处理上的不准确造成的，包括但不限于输入输出的范围，题面的解决方法，程序的逻辑与复杂度等，重新思考一下这些细节，可能对完成题目有所帮助。

------

#### Question6

```c++
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream ifile("/P1000.in");
    ofstream ofile("/P1000.txt");
    
    cin.rdbuf(ifile.rdbuf());
    
    // my code
    
    cout.rdbuf(ofile.rdbuf());
    
    ifile.close();
    ofile.close();
    return 0;
}
```
