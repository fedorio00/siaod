#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

// Узел дерева
struct Node {
    char data;
    Node* left;
    Node* right;

    Node(char value) : data(value), left(nullptr), right(nullptr) {}
};

// Функция для создания идеально сбалансированного дерева
Node* createBalancedTree(const vector<char>& keys, int start, int end) {
    if (start > end) return nullptr;

    int mid = (start + end) / 2; // исправить вот это, нельзя так делить
    Node* root = new Node(keys[mid]);

    root->left = createBalancedTree(keys, start, mid - 1);
    root->right = createBalancedTree(keys, mid + 1, end);

    return root;
}

// Функция для определения уровня, на котором находится заданное значение
int findLevel(Node* root, char value, int level = 1) {
    if (!root) return -1;
    if (root->data == value) return level;

    int leftLevel = findLevel(root->left, value, level + 1);
    if (leftLevel != -1) return leftLevel;

    return findLevel(root->right, value, level + 1);
}

// Вспомогательная функция для подсчета количества узлов
int countNodes(Node* root) {
    if (!root) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Функция для подсчета количества узлов в левом поддереве
int countNodesInLeftSubtree(Node* root) {
    if (!root || !root->left) return 0;
    return countNodes(root->left);
}

// Вывод дерева (обход в ширину)
void printTreeVertically(Node* root) {
    if (!root) return;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size();
        vector<char> levelNodes;

        for (int i = 0; i < levelSize; ++i) {
            Node* current = q.front();
            q.pop();
            levelNodes.push_back(current->data);

            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }

        // Вывод узлов текущего уровня
        for (char node : levelNodes) {
            cout << node << " ";
        }
        cout << endl;
    }
}

int main() {
    // Пример ключей для дерева
    vector<char> keys = {'d', 'a', 'b', 'e', 'f', 'c', 'g'};
    sort(keys.begin(), keys.end());

    Node* root = createBalancedTree(keys, 0, keys.size() - 1);

    cout << "Tree structure:" << endl;
    printTreeVertically(root);

    // Определить уровень, на котором находится заданное значение
    char targetValue = 'c';
    int level = findLevel(root, targetValue);
    if (level != -1) {
        cout << "Level of value '" << targetValue << "': " << level << endl;
    } else {
        cout << "Value '" << targetValue << "' not found in the tree." << endl;
    }

    // Определить количество узлов в левом поддереве исходного дерева
    int leftSubtreeNodes = countNodesInLeftSubtree(root);
    cout << "Node count in left subtree: " << leftSubtreeNodes << endl;

    cin.get();
    return 0;
}
