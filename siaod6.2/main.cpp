#include <iostream>
#include "bin_tree.h"
using namespace std;

int main() {
    BalancedBinaryTree tree;
    TreeNode* root = nullptr;
    int keys[] = {10, 20, 30, 40, 50, 25, -10, 700, 1, 4};

    for (int key : keys) {
        root = tree.insert(root, key);
    }

    cout << "Tree struct:" << endl;
    tree.display(root);
    cout << "\nPress Enter to exit...";
    cin.get();
    return 0;
}