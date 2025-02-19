// #include <iostream>
// #include <vector>
// #include <stack>
// #include <queue>
// #include <algorithm>
// using namespace std;

// struct TreeNode {
//     int val;
//     TreeNode *left, *right;
//     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
// };

// class BinaryTree {
// public:
//     vector<int> preorder, inorder, postorder, levelOrder;
//     vector<int> nodeCount, height;

//     TreeNode* buildTree(const vector<pair<int, int>>& nodes) {
//         vector<TreeNode*> tree(nodes.size() + 1, nullptr);
//         for (int i = 1; i <= nodes.size(); i++) {
//             if (!tree[i]) tree[i] = new TreeNode(i);
//             if (nodes[i - 1].first != -1) {
//                 tree[i]->left = new TreeNode(nodes[i - 1].first);
//                 tree[nodes[i - 1].first] = tree[i]->left;
//             }
//             if (nodes[i - 1].second != -1) {
//                 tree[i]->right = new TreeNode(nodes[i - 1].second);
//                 tree[nodes[i - 1].second] = tree[i]->right;
//             }
//         }
//         return tree[1];
//     }

//     void calcNodeCountAndHeight(TreeNode* root, int& totalNodes, int& treeHeight) {
//         if (!root) {
//             totalNodes = 0;
//             treeHeight = 0;
//             return;
//         }
//         int leftNodes, rightNodes, leftHeight, rightHeight;
//         calcNodeCountAndHeight(root->left, leftNodes, leftHeight);
//         calcNodeCountAndHeight(root->right, rightNodes, rightHeight);
//         totalNodes = leftNodes + rightNodes + 1;
//         treeHeight = max(leftHeight, rightHeight) + 1;
//         nodeCount[root->val - 1] = totalNodes;
//         height[root->val - 1] = treeHeight;
//     }

//     void preorderTraversal(TreeNode* root) {
//         if (!root) return;
//         preorder.push_back(root->val);
//         preorderTraversal(root->left);
//         preorderTraversal(root->right);
//     }

//     void inorderTraversal(TreeNode* root) {
//         stack<TreeNode*> s;
//         TreeNode* curr = root;
//         while (curr || !s.empty()) {
//             while (curr) {
//                 s.push(curr);
//                 curr = curr->left;
//             }
//             curr = s.top();
//             s.pop();
//             inorder.push_back(curr->val);
//             curr = curr->right;
//         }
//     }

//     void postorderTraversal(TreeNode* root) {
//         stack<TreeNode*> s;
//         TreeNode* curr = root;
//         TreeNode* lastVisited = nullptr;
//         while (curr || !s.empty()) {
//             while (curr) {
//                 s.push(curr);
//                 curr = curr->left;
//             }
//             TreeNode* node = s.top();
//             if (node->right && node->right != lastVisited) {
//                 curr = node->right;
//             } else {
//                 postorder.push_back(node->val);
//                 lastVisited = node;
//                 s.pop();
//             }
//         }
//     }

//     void levelOrderTraversal(TreeNode* root) {
//         if (!root) return;
//         queue<TreeNode*> q;
//         q.push(root);
//         while (!q.empty()) {
//             TreeNode* node = q.front();
//             q.pop();
//             levelOrder.push_back(node->val);
//             if (node->left) q.push(node->left);
//             if (node->right) q.push(node->right);
//         }
//     }

//     void processTree(TreeNode* root, int n) {
//         nodeCount.resize(n, 0);
//         height.resize(n, 0);
//         int totalNodes, treeHeight;
//         calcNodeCountAndHeight(root, totalNodes, treeHeight);
//         preorderTraversal(root);
//         inorderTraversal(root);
//         postorderTraversal(root);
//         levelOrderTraversal(root);
//     }
// };

// int main() {
//     int n;
//     cin >> n;
//     vector<pair<int, int>> nodes(n);
//     for (int i = 0; i < n; i++) {
//         cin >> nodes[i].first >> nodes[i].second;
//     }

//     BinaryTree bt;
//     TreeNode* root = bt.buildTree(nodes);
//     bt.processTree(root, n);

//     for (int x : bt.preorder) cout << x << " ";
//     cout << endl;
//     for (int x : bt.inorder) cout << x << " ";
//     cout << endl;
//     for (int x : bt.postorder) cout << x << " ";
//     cout << endl;
//     for (int x : bt.levelOrder) cout << x << " ";
//     cout << endl;
//     for (int x : bt.nodeCount) cout << x << " ";
//     cout << endl;
//     for (int x : bt.height) cout << x << " ";
//     cout << endl;

//     return 0;
// }

#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <algorithm>
using namespace std;

vector<int> getPostOrder(const vector<int>& preOrder, const vector<int>& inOrder) {
    int n = preOrder.size();
    unordered_map<int, int> inIndexMap;
    for (int i = 0; i < n; ++i) {
        inIndexMap[inOrder[i]] = i;
    }

    vector<int> postOrder;
    stack<tuple<int, int, int>> stack; // 存储 (preIndex, inStart, inEnd)

    stack.push({0, 0, n - 1});
    while (!stack.empty()) {
        auto [preIndex, inStart, inEnd] = stack.top();
        stack.pop();

        if (inStart > inEnd) continue;

        int rootValue = preOrder[preIndex];
        int rootIndex = inIndexMap[rootValue];

        // 后序遍历的顺序是：左子树 -> 右子树 -> 根节点
        // 因此先压入右子树，再压入左子树
        if (rootIndex + 1 <= inEnd) {
            stack.push({preIndex + (rootIndex - inStart) + 1, rootIndex + 1, inEnd});
        }
        if (inStart <= rootIndex - 1) {
            stack.push({preIndex + 1, inStart, rootIndex - 1});
        }
        postOrder.push_back(rootValue);
    }

    reverse(postOrder.begin(), postOrder.end());
    return postOrder;
}

int main() {
    int n;
    cin >> n;
    vector<int> preOrder(n), inOrder(n);
    for (int i = 0; i < n; ++i) cin >> preOrder[i];
    for (int i = 0; i < n; ++i) cin >> inOrder[i];

    vector<int> postOrder = getPostOrder(preOrder, inOrder);
    for (int val : postOrder) {
        cout << val << " ";
    }
    cout << endl;
    return 0;
}

