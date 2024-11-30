#include "iostream"
#include "vector"
#include "stack"

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class SearchTree
{
public:
    SearchTree() : root(nullptr), size(0) {}
    SearchTree(TreeNode *r) : root(r), size(0) {}

    int insert(int v);
    int search(int v);
    int erase(int v);
    int rankSearch(int rank);
    int rankErase(int rank);

    TreeNode* getRoot() { return this->root; }
    TreeNode* getByRank(int rank);

protected:
    TreeNode *root;
    int       size;
};

int SearchTree::insert(int v)
{
    if (root == nullptr) {
        root = new TreeNode(v);
        size++;
        return 0;
    }

    TreeNode *finalNode = root;
    int res = 0;
    for (int i = 0; i < size; i++)
    {
        res ^= finalNode->val;
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

    TreeNode *finalNode = root, *parentNode = nullptr;
    int res = 0;
    for (int i = 0; i < size; i++)
    {
        res ^= finalNode->val;
        if (v > finalNode->val) {
            if (finalNode->right == nullptr) return 0;
            else {
                parentNode = finalNode;
                finalNode  = finalNode->right;
            }
        }
        else if (v < finalNode->val) {
            if (finalNode->left == nullptr) return 0;
            else {
                parentNode = finalNode;
                finalNode  = finalNode->left;
            }
        }
        else break;
    }

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
        TreeNode *temp = finalNode->right;
        while (temp->left != nullptr) temp = temp->left;
        finalNode->val = temp->val;
        if (temp->right != nullptr) {
            TreeNode *tempRight = temp->right;
            temp->val = tempRight->val;
            temp->right = tempRight->right;
            delete tempRight;
        }
        else {
            if (finalNode->right == temp) finalNode->right = nullptr;
            else finalNode->right = temp->right;
            delete temp;
        }
    }

    size--;
    return res;
}

int main()
{
    return 0;
}