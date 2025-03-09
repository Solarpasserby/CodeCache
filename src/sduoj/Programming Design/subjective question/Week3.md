## Week3

#### Question1

广度优先搜索，优先在广度方向上进行搜索，再在深度方向上进行搜索。因此当第一次遍历到目标节点时，广度优先搜索已经遍历了所有可能的到达该节点的所有路径，故可以求得最短路径。

#### Question2

**可行性剪枝**是指在搜索过程中，当前条件已经无法满足题目要求时，及时终止当前搜索的一种搜索的优化手段；**最优性剪枝**是指在搜索过程中，当前条件已经不满足最优条件时（通常是与先前记入的局部最优解进行比较），及时终止当前搜索的一种搜索的优化手段。

#### Question3

- **解法**

  这是一道搜索问题，由于题目要求求最少次数，且数据规模相对较小，因此可以利用广度优先搜索算法求解。具体来说，使用一个队列存取接下来要遍历的节点，一个数组来记录到达当前节点的最少次数，其中未到达值设为$-1$。将起始节点加入队列，后云行广度优先搜索算法，将其后继节点加入队列，并更新数组，记录次数，直至队列为空或到达目标节点。

- **时间复杂度**

  对于单个测试用例，进行一次广度优先搜索。对于一次搜索，最坏情况下须遍历所有$N$个节点，每个节点进行$2$次判断，因此单次搜索的时间复杂度为$O(N)$。由于有$M$个测试用例，因此整体时间复杂度为$O(MN)$。

- **代码**

  ```c++
  #include<bits/stdc++.h>
  
  using namespace std;
  
  int N, A, B;
  int _move[300]; //存放题目所给的电梯移动步长
  int reach[300]; //记录到达当前节点的最少次数
  queue<int> q; //用于存放将要遍历的节点
  
  int main()
  {
      ios::sync_with_stdio(0);
      cin.tie(nullptr);
  
      while(true) //外层循环，直至输入结束
      {
          cin >> N;
          if (N == 0) break;
  
          cin >> A >> B;
  
          //读取数据，初始化
          for(int i = 1; i <= N; i++)
          {
              cin >> _move[i];
              reach[i] = -1;
          }
  
          //初始化起始节点
          reach[A] = 0;
          while(!q.empty()) q.pop();
          q.emplace(A);
  
          while (!q.empty())
          {
              int t = q.front();
              //判断电梯上行到达的节点是否能被访问且是否已经到达过
              if (t + _move[t] <= N && reach[t + _move[t]] == -1) 
              {
                  //若满足条件，则更新次数，并将节点加入队列
                  reach[t + _move[t]] = reach[t] + 1;
                  q.emplace(t + _move[t]);
              }
              if (t - _move[t] > 0 && reach[t - _move[t]] == -1) //同上
              {
                  reach[t - _move[t]] = reach[t] + 1;
                  q.emplace(t - _move[t]);
              }
  
              if (reach[B] != -1) break;
  
              q.pop();
          }
  
          cout << reach[B] << '\n';
      }
  
      return 0;
  }
  ```

#### Question4

- **解法**

  与背包问题有些相似，注意到数据规模较小，因此可以尝试使用深度优先算法解题。具体来说，实现一个递归函数用于选取或是不选取当前数字，并传递已选取的数字个数和数字之和，当数字个数满足条件时判断数字之和是否为素数。同时进行了适当剪枝，当数字遍历完时或是选完时，及时终止搜索。

- **时间复杂度**

  每个数字有选与不选两种可能，总共有$n$个数字，因此最坏情况下时间复杂度为$O(2^n)$。由于数据规模较小，还是能够AC的

- **代码**

  ```c++
  #include<bits/stdc++.h>
  
  using namespace std;
  
  int n, k;
  int num[30]; //记录所给数字
  int ans; //记录结果
  
  // 判断当前数字是否为素数
  bool checkPrime(int m)
  {
      if (m == 1) return false;
      else if (m == 2) return true;
      else if (m % 2 == 0) return false;
      else
      {
          int tmp = ceil(sqrt(m));
          for(int i = 3; i < tmp; i += 2)
              if (m % i == 0) return false;
      }
  
      return true;
  }
  
  //深度优先搜索，depth表示选取数字个数，loc表示遍历到哪个数字，res表示数字之和
  void dfs(const int &depth, const int &loc, const int &res)
  {
      if (depth > k)
      {
          if (checkPrime(res)) ++ans; //符合条件，结果加1
          return;
      }
  
      if (loc > n) //递归深度超过所给个数，终止搜索
          return;
  
      dfs(depth, loc + 1, res); //不选取，进入下一层搜索
      dfs(depth + 1, loc + 1, res + num[loc]); //选取，进入下一层搜索
  }
  
  int main()
  {
      ios::sync_with_stdio(0);
      cin.tie(nullptr);
  
      cin >> n >> k;
      for(int i = 1; i <= n; i++)
          cin >> num[i];
  
      // 开始深度优先搜索
      dfs(1, 1, 0);
  
      cout << ans << '\n';
  
      return 0;
  }
  ```

  
