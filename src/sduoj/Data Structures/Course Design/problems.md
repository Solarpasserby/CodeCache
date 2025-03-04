## 数据结构课程设计

### 1.跳表的实现与分析

- **问题描述**

  实现并分析跳表。

- **基本要求**

  1. 构造并实现跳表ADT，跳表ADT 中应包括初始化、查找、插入、删除指定关键字的元素、删除关键字最小的元素、删除关键字最大的元素等基本操作。
  2. 分析各基本操作的时间复杂性。

  3. 能对跳表维护动态数据集合的效率进行实验验证，获得一定量的实验数据，如给定随机产生1000 个数据并将其初始化为严格跳表，在此基础上进行一系列插入、删除、查找操作（操作序列也可以随机生成），获得各种操作的平均时间（或统计其基本操作个数）；获得各操作执行时间的变化情况。应该是越来越大，当大到一定程度后应该进行适当的整理，需设计相应的整理算法，并从数量上确定何时较为合适；能和其他简单线性数据结构，如排序数组上的折半查找进行各类操作效率上的数量对比。

------

### 2.外排序

- **问题描述**

  应用竞赛树结构模拟实现外排序。

- **基本要求**

  1. 设计并实现最小输者树结构ADT，ADT中应包括初始化、返回赢者，重构等基本操作。
  2. 应用最小输者树设计实现外排序，外部排序中的生成最初归并串以及K路归并都应用竞赛树结构实现。
  3. 随机创建一个较长的文件作为外排序的初始数据；设置归并路数以及缓冲区的大小；获得外排序的访问磁盘的次数并进行分析。可采用小文件来模拟磁盘块。

------

### 28.大整数加乘法问题

- **问题描述**

  完成大整数加法和乘法运算。

- **基本要求**

  构建自己的大整数类。