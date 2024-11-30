#include "iostream"
#include "vector"
#include "stack"

using namespace std;

struct TreeNode
{
    int val;
    int size;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), size(1), left(nullptr), right(nullptr) {}
};

class SearchTree
{
public:
    SearchTree() {
        this->root  = nullptr;
        this->size = 0;
    }
    SearchTree(TreeNode *r) : root(r), size(0) {}

    bool exist(int v);
    int insert(int v);
    int search(int v);
    int erase(int v);
    int rankSearch(int rank);
    int rankErase(int rank);

    void eraseNode(TreeNode *finalNode, TreeNode *parentNode);

    TreeNode* getByRank(int rank);

protected:
    TreeNode *root;
    int       size;
};

bool SearchTree::exist(int v)
{
    if (root == nullptr) return false;

    TreeNode *finalNode = root;
    for (int i = 0; i < size; i++)
    {
        if (v == finalNode->val) return true;
        else if (v > finalNode->val) {
            if (finalNode->right == nullptr) return false;
            else finalNode = finalNode->right;
        }
        else {
            if (finalNode->left == nullptr) return false;
            else finalNode = finalNode->left;
        }
    }

    return false;
}

int SearchTree::insert(int v)
{
    if (root == nullptr) {
        root = new TreeNode(v);
        size++;
        return 0;
    }

    if (exist(v)) return 0;

    TreeNode *finalNode = root;
    int res = 0;
    for (int i = 0; i < size; i++)
    {
        res ^= finalNode->val;
        finalNode->size++;
        if (v == finalNode->val) return 0;
        else if (v > finalNode->val) {
            if (finalNode->right == nullptr) {
                finalNode->right = new TreeNode(v);
                size++;
                return res;
            }
            else finalNode = finalNode->right;
        }
        else {
            if (finalNode->left == nullptr) {
                finalNode->left = new TreeNode(v);
                size++;
                return res;
            }
            else finalNode = finalNode->left;
        }
    }

    return 0;
}

int SearchTree::search(int v)
{
    if (root == nullptr) return 0;

    TreeNode *finalNode = root;
    int res = 0;
    for (int i = 0; i < size; i++)
    {
        res ^= finalNode->val;
        if (v == finalNode->val) return res;
        else if (v > finalNode->val) {
            if (finalNode->right == nullptr) return 0;
            else finalNode = finalNode->right;
        }
        else {
            if (finalNode->left == nullptr) return 0;
            else finalNode = finalNode->left;
        }
    }

    return 0;
}

int SearchTree::erase(int v)
{
    if (root == nullptr) return 0;

    if (!exist(v)) return 0;

    TreeNode *finalNode = root, *parentNode = nullptr;
    int res = 0, i = 0;
    for (; i < size; i++)
    {
        res ^= finalNode->val;
        finalNode->size--;

        if (v > finalNode->val) {
            if (finalNode->right == nullptr) return 0;
            else {
                parentNode = finalNode;
                finalNode  = finalNode->right;
                continue;
            }
        }
        else if (v < finalNode->val) {
            if (finalNode->left == nullptr) return 0;
            else {
                parentNode = finalNode;
                finalNode  = finalNode->left;
                continue;
            }
        }
        else break;
    }

    eraseNode(finalNode, parentNode);
    return res;
}

int SearchTree::rankSearch(int rank)
{
    TreeNode *temp = getByRank(rank);
    if (temp == nullptr) return 0;
    else return search(temp->val);
}

int SearchTree::rankErase(int rank)
{
    TreeNode *temp = getByRank(rank);
    if (temp == nullptr) return 0;
    else return erase(temp->val);
}

TreeNode* SearchTree::getByRank(int rank)
{
    if (root == nullptr || rank <= 0) return nullptr;

    TreeNode *finalNode = root;
    for (int i = 0; i < size; i++)
    {
        if (finalNode->left != nullptr && finalNode->left->size >= rank) finalNode = finalNode->left;
        else if (finalNode->left != nullptr && finalNode->left->size < rank) {
            rank -= finalNode->left->size;
            if (rank == 1) return finalNode;
            rank--;
            finalNode = finalNode->right;
        }
        else {
            if (rank == 1) return finalNode;
            rank--;
            finalNode = finalNode->right;
        }
    }

    return nullptr;
}

void SearchTree::eraseNode(TreeNode *finalNode, TreeNode *parentNode)
{
    if (finalNode->left == nullptr && finalNode->right == nullptr) {
        if (parentNode == nullptr) root = nullptr;
        else {
            if (parentNode->left == finalNode) parentNode->left = nullptr;
            else parentNode->right = nullptr;
        }
        delete finalNode;
    }
    else if (finalNode->left != nullptr && finalNode->right == nullptr) {
        if (parentNode == nullptr) root = finalNode->left;
        else {
            if (parentNode->left == finalNode) parentNode->left = finalNode->left;
            else parentNode->right = finalNode->left;
        }
        delete finalNode;
    }
    else if (finalNode->left == nullptr && finalNode->right != nullptr) {
        if (parentNode == nullptr) root = finalNode->right;
        else {
            if (parentNode->left == finalNode) parentNode->left = finalNode->right;
            else parentNode->right = finalNode->right;
        }
        delete finalNode;
    }
    else {
        TreeNode *rightMinNode = finalNode->right, *rmParentNode = finalNode;
        while (rightMinNode->left != nullptr)
        {
            rightMinNode->size--;
            rmParentNode = rightMinNode;
            rightMinNode = rightMinNode->left;
        }

        finalNode->val = rightMinNode->val;
        
        if (rmParentNode->left == rightMinNode) rmParentNode->left = rightMinNode->right;
        else rmParentNode->right = rightMinNode->right;

        delete rightMinNode;
    }

    size--;
}

int handleInput(int op, int v)
{
    static SearchTree searchTree = SearchTree();
    int res;

    switch (op)
    {
    case 0:
        res = searchTree.insert(v);
        break;

    case 1:
        res = searchTree.search(v);
        break;

    case 2:
        res = searchTree.erase(v);
        break;

    case 3:
        res = searchTree.rankSearch(v);
        break;

    case 4:
        res = searchTree.rankErase(v);
        break;
    
    default:
        break;
    }

    return res;
}

int main()
{
    int n, a, b;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a >> b;
        cout << handleInput(a, b) << endl;
    }
    return 0;
}