#include <iostream>

class AVLNod {
public:
  explicit AVLNod(int val) {
    value = val;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
  height = 0;
  }

  explicit AVLNod() {
    value = 0;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    height = 0;
  }

  int value;
  AVLNod* left;
  AVLNod* right;
  AVLNod* parent;
  int height;
};

class AVLTree {
public:
  AVLNod* root;

  AVLTree() {
    root = nullptr;
  }

  ~AVLTree() {
    clearTree(root);
  }

  bool isTreeEmty() {
    return root == nullptr;
  }

  int height(AVLNod* nod) {
    return nod ? nod->height : -1;
  }

  void updateHeight(AVLNod* node) {
    if (node) {
      node->height = 1 + std::max(height(node->left), height(node->right));
    }
  }

  int balanceFactor(AVLNod* nod) {
    return nod ? height(nod->left) - height(nod->right) : 0;
  }

  void leftRotate(AVLNod* x) {
    AVLNod* y = x->right;
    x->right = y->left;
    if (y->left != nullptr) {
      y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
      root = y;
    } else if (x == x->parent->left) {
      x->parent->left = y;
    } else {
      x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
    updateHeight(x);
    updateHeight(y);
  }

  void rightRotate(AVLNod* x) {
    AVLNod* y = x->left;
    x->left = y->right;
    if (y->right != nullptr) {
      y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
      root = y;
    } else if (x == x->parent->right) {
      x->parent->right = y;
    } else {
      x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
    updateHeight(x);
    updateHeight(y);
  }

  void treeInsert(AVLNod* z) {
    AVLNod* x = root;
    AVLNod* y = nullptr;
    while (x != nullptr) {
      y = x;
      if (z->value < x->value) {
        x = x->left;
      } else {
        x = x->right;
      }
    }
    if (y == nullptr) {
      root = z;
    } else if (z->value < y->value) {
      y->left = z;
    } else {
      y->right = z;
    }
    z->parent = y;
    insertFix(z);
  }

  void insertFix(AVLNod* z) {
    while (z != nullptr) {
      updateHeight(z);
      int balance = balanceFactor(z);
      if (balance > 1) {
        if (balanceFactor(z->left) < 0) {
          leftRotate(z->left);
        }
          rightRotate(z);
        } else if (balance < -1) {
          if (balanceFactor(z->right) > 0) {
            rightRotate(z->right);
          }
          leftRotate(z);
        }
      z = z->parent;
    }
  }

  AVLNod* searchTree(int k) const {
    AVLNod* x = root;
    AVLNod* res = nullptr;
    while (x != nullptr) {
      if (x->value >= k) {
        res = x;
        x = x->left;
      } else {
        x = x->right;
      }
    }
    return res;
  }

private:
  void clearTree(AVLNod* node) {
    if (node) {
      clearTree(node->left);
      clearTree(node->right);
      delete node;
    }
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  AVLTree tree;
  long long last_query_result = 0;

  for (int i = 0; i < n; ++i) {
    char op;
    long long val;
    std::cin >> op >> val;

    if (op == '+') {
      if (i > 0 && last_query_result != -2) {
        val = (val + last_query_result) % 1000000000LL;
        last_query_result = -2;
      }
      tree.treeInsert(new AVLNod(static_cast<int>(val)));
    } else if (op == '?') {
      AVLNod* result = tree.searchTree(static_cast<int>(val));
        if (!result) {
          std::cout << -1 << '\n';
          last_query_result = -1;
        } else {
          std::cout << result->value << '\n';
          last_query_result = result->value;
        }
    }
  }
  return 0;
}
