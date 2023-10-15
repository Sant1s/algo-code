#include <iostream>

struct Node {
  int key;
  size_t height;
  Node* left_child;
  Node* right_child;
  explicit Node(int k, Node* left = nullptr, Node* right = nullptr) {
    key = k;
    left_child = left;
    right_child = right;
    height = 0;
  }
};

class AVLTree {
 public:
  AVLTree() : root_(nullptr){};

  ~AVLTree() { Clear(root_); }

  int LowerBound(int number) {
    Node* tmp_root = root_;
    int ret_val = -1;
    if (root_ == nullptr) {
      return -1;
    }
    while (tmp_root != nullptr) {
      if (tmp_root->key == number) {
        return tmp_root->key;
      }
      if (tmp_root->key < number) {
        if (tmp_root->right_child == nullptr) {
          return ret_val;
        }
        if (tmp_root->right_child != nullptr) {
          tmp_root = tmp_root->right_child;
        }
      }
      if (tmp_root->key > number) {
        ret_val = tmp_root->key;
        if (tmp_root->left_child == nullptr) {
          return ret_val;
        }
        if (tmp_root->left_child != nullptr) {
          tmp_root = tmp_root->left_child;
        }
      }
    }
    return ret_val;
  }

  void Insert(int k) { root_ = Add(root_, k); }

 private:
  Node* root_ = nullptr;

  Node* Add(Node* node, int key) {
    if (node == nullptr) {
      return new Node(key);
    }
    if (node != nullptr) {
      if (node->key < key) {
        if (node->right_child != nullptr) {
          node->right_child = Add(node->right_child, key);
        }
        if (node->right_child == nullptr) {
          node->right_child = new Node(key);
        }
      }
      if (node->key >= key) {
        if (node->left_child != nullptr) {
          node->left_child = Add(node->left_child, key);
        }
        if (node->left_child == nullptr) {
          node->left_child = new Node(key);
        }
      }
    }
    return Balance(node);
  }

  void Clear(Node* node) {
    if (node == nullptr) {
      return;
    }
    Clear(node->left_child);
    node->left_child = nullptr;
    Clear(node->right_child);
    node->right_child = nullptr;
    delete node;
  }

  static int Height(Node* node) { return (node == nullptr) ? 0 : node->height; }

  static int SubTreeDiffHeight(Node* node) {
    if (node != nullptr) {
      return Height(node->right_child) - Height(node->left_child);
    }
    return 0;
  }

  static void UpdateHeight(Node* node) {
    size_t height_left = Height(node->left_child);
    size_t height_right = Height(node->right_child);
    if (height_left > height_right) {
      node->height = ++height_left;
    } else {
      node->height = ++height_right;
    }
  }

  static Node* RightRotate(Node* node) {
    Node* tmp_node = node->left_child;
    if (tmp_node != nullptr) {
      node->left_child = tmp_node->right_child;
      tmp_node->right_child = node;
      UpdateHeight(tmp_node);
      UpdateHeight(node);
      return tmp_node;
    }
    return nullptr;
  }

  static Node* LeftRotate(Node* node) {
    Node* tmp_node = node->right_child;
    if (tmp_node != nullptr) {
      node->right_child = tmp_node->left_child;
      tmp_node->left_child = node;
      UpdateHeight(tmp_node);
      UpdateHeight(node);
      return tmp_node;
    }
    return nullptr;
  }

  static Node* Balance(Node* node) {
    if (node->left_child == nullptr && node->right_child == nullptr) {
      return node;
    }
    UpdateHeight(node);
    if (SubTreeDiffHeight(node) == -2) {
      if (SubTreeDiffHeight(node->left_child) > 0) {
        node->left_child = LeftRotate(node->left_child);
      }
      return RightRotate(node);
    }

    if (SubTreeDiffHeight(node) == 2) {
      if (SubTreeDiffHeight(node->right_child) < 0) {
        node->right_child = RightRotate(node->right_child);
      }
      return LeftRotate(node);
    }
    return node;
  }
};

int main() {
  AVLTree tree;
  size_t n;
  int num = 0;
  int prev_num = 0;
  std::cin >> n;
  std::string command;
  std::string prev_command;
  for (size_t i = 0; i < n; ++i) {
    std::cin >> command;
    if (command == "+") {
      if (prev_command == "?") {
        std::cin >> num;
        tree.Insert((num + prev_num) % 1000000000);
        prev_command = "-";
      } else {
        std::cin >> num;
        tree.Insert(num);
      }
    }
    if (command == "?") {
      prev_command = "?";
      std::cin >> num;
      prev_num = tree.LowerBound(num);
      std::cout << prev_num << std::endl;
    }
  }
  return 0;
}
