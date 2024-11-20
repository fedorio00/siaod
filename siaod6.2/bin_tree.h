#include <iostream>
using namespace std;
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int key) : val(key), left(nullptr), right(nullptr) {}
};
class BalancedBinaryTree {
public:
    TreeNode* insert(TreeNode* root, int key) {
        if (root == nullptr) {
            return new TreeNode(key);
        }

        // Логика для вставки в идеально сбалансированное дерево
        if (key < root->val) {
            root->left = insert(root->left, key);
        } else {
            root->right = insert(root->right, key);
        }

        return root;
    }

    void display(TreeNode* root, int level = 0) {
        if (root != nullptr) {
            display(root->right, level + 1);
            cout << string(level * 6, ' ') << "-> " << root->val << endl;
            display(root->left, level + 1);
        }
    }
};