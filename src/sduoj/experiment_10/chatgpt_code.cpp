#include <iostream>
#include <string>
#include <queue>
#include <vector>
using namespace std;

struct freqNode {
    int freq;
    freqNode* left;
    freqNode* right;

    freqNode(int f) : freq(f), left(nullptr), right(nullptr) {}
};

// 比较函数，用于优先队列
struct compare {
    bool operator()(const freqNode* a, const freqNode* b) {
        return a->freq > b->freq; // 小顶堆，频率小的优先
    }
};

int calculateHuffmanLength(priority_queue<freqNode*, vector<freqNode*>, compare>& pq) {
    int totalLength = 0;
    
    while (pq.size() > 1) {
        // 取出两个最小频率的节点
        freqNode* left = pq.top(); pq.pop();
        freqNode* right = pq.top(); pq.pop();

        // 合并为新节点
        int mergedFreq = left->freq + right->freq;
        totalLength += mergedFreq;

        freqNode* newNode = new freqNode(mergedFreq);
        newNode->left = left;
        newNode->right = right;

        // 新节点入堆
        pq.push(newNode);
    }

    // 清理剩余的哈夫曼树节点
    while (!pq.empty()) {
        delete pq.top();
        pq.pop();
    }

    return totalLength;
}

int main() {
    string str;
    cin >> str;

    // 统计字符频率
    vector<int> freq(26, 0);
    for (char c : str) {
        freq[c - 'a']++;
    }

    // 构建优先队列
    priority_queue<freqNode*, vector<freqNode*>, compare> pq;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            pq.push(new freqNode(freq[i]));
        }
    }

    // 计算哈夫曼编码的总长度
    int huffmanLength = calculateHuffmanLength(pq);
    cout << huffmanLength << endl;

    return 0;
}
