#include <iostream>

const int NUM = 1000000000;

struct Node {
  uint64_t key;
  uint64_t priority;
  uint64_t sub_sum;
  Node* left_child;
  Node* right_child;
  explicit Node(uint64_t k) : key(k), priority(rand() % NUM), sub_sum(k), left_child(nullptr), right_child(nullptr) {}
};


class Dectree {
 public:
  Dectree() : root_(nullptr) {}

  ~Dectree() { Clear(root_); }

  bool Find(uint64_t key) {
    Node* tmp_root = root_;
    while (tmp_root != nullptr) {
      if (tmp_root->key == key) {
        return true;
      }
      if (tmp_root->key < key) {
        if (tmp_root->right_child == nullptr) {
          return false;
        }
        tmp_root = tmp_root->right_child;
      } else {
        if (tmp_root->left_child == nullptr) {
          return false;
        }
        tmp_root = tmp_root->left_child;
      }
    }
    return false;
  }

  void Insert(uint64_t key) {
    if (Find(key) == true) {
      return;
    }
    Node* new_node = new Node(key);
    if (root_ == nullptr) {
      root_ = new_node;
      return;
    }
    std::pair<Node*, Node*> split_tree = Split(root_, key);
    Node* node = Merge(split_tree.first, new_node);
    UpdateSum(node);
    root_ = Merge(node, split_tree.second);
    UpdateSum(root_);
  }

  uint64_t TreeSegmentSum(uint64_t left, uint64_t right) {
    if (root_ != nullptr) {
      uint64_t left_sum = NodeLeftSum(root_, left);
      uint64_t right_sum = NodeRightSum(root_, right);
      return root_->sub_sum - left_sum - right_sum;
    }
    return 0;
  }

 private:
  Node* root_;

  uint64_t NodeSum(Node* node) { return (node != nullptr) ? node->sub_sum : 0; }

  void UpdateSum(Node* node) {
    if (node != nullptr) {
      node->sub_sum = node->key + NodeSum(node->left_child) + NodeSum(node->right_child);
    }
    return;
  }

  uint64_t NodeRightSum(Node* node, uint64_t key) {
    if (node != nullptr) {
      if (node->key <= key) {
        return NodeRightSum(node->right_child, key);
      }
      return NodeSum(node->right_child) + NodeRightSum(node->left_child, key) + node->key;
    }
    return 0;
  }

  uint64_t NodeLeftSum(Node* node, uint64_t key) {
    if (node != nullptr) {
      if (node->key >= key) {
        return NodeLeftSum(node->left_child, key);
      }
      return NodeSum(node->left_child) + NodeLeftSum(node->right_child, key) + node->key;
    }
    return 0;
  }

  Node* Merge(Node* node_1, Node* node_2) {
    if (node_1 == nullptr) {
      UpdateSum(node_2);
      return node_2;
    }
    if (node_2 == nullptr) {
      UpdateSum(node_1);
      return node_1;
    }
    if (node_1->priority <= node_2->priority) {
      node_2->left_child = Merge(node_1, node_2->left_child);
      UpdateSum(node_1);
      UpdateSum(node_2);
      return node_2;
    }
    node_1->right_child = Merge(node_1->right_child, node_2);
    UpdateSum(node_1);
    UpdateSum(node_2);
    return node_1;
  }

  std::pair<Node*, Node*> Split(Node* node, uint64_t key) {
    if (node != nullptr) {
      if (node->key > key) {
        std::pair<Node*, Node*> split_tree = Split(node->left_child, key);
        node->left_child = split_tree.second;
        UpdateSum(split_tree.first);
        UpdateSum(split_tree.second);
        UpdateSum(node);
        return std::make_pair(split_tree.first, node);
      }
      std::pair<Node*, Node*> split_tree = Split(node->right_child, key);
      node->right_child = split_tree.first;
      UpdateSum(split_tree.first);
      UpdateSum(split_tree.second);
      return std::make_pair(node, split_tree.second);
    }
    return std::make_pair(nullptr, nullptr);
  }

  void Clear(Node* tmp_root) {
    if (tmp_root == nullptr) {
      return;
    }
    Clear(tmp_root->left_child);
    Clear(tmp_root->right_child);
    delete tmp_root;
  }
};

int main() {
  Dectree tree;
  uint64_t n = 0;
  std::cin >> n;
  std::string command;
  std::string prev_command = "-";
  uint64_t number = 0;
  uint64_t prev_number = 0;
  uint64_t left = 0;
  uint64_t right = 0;
  for (uint64_t i = 0; i < n; ++i) {
    std::cin >> command;
    if (command == "?") {
      prev_command = "?";
      std::cin >> left >> right;
      prev_number = tree.TreeSegmentSum(left, right);
      std::cout << prev_number << std::endl;
    }
    if (command == "+") {
      std::cin >> number;
      if (prev_command == "?") {
        prev_command = "+";
        tree.Insert((number + prev_number) % NUM);
      }
      tree.Insert(number);
    }
  }
  return 0;
}
