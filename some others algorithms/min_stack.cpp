#include <iostream>
#include <string>

class Stack {
 public:
  Stack() {
    capasity_ = 1;
    value_ = new int[capasity_];
    min_ = new int[capasity_];
    node_size_ = 0;
  }

  ~Stack() {
    delete[] value_;
    delete[] min_;
  }

  void Push(int data) {
    if (node_size_ == 0) {
      node_size_++;
      value_[node_size_ - 1] = data;
      min_[node_size_ - 1] = data;
    } else if (capasity_ == node_size_) {
      capasity_ *= 2;
      int* tmp_value = new int[capasity_];
      int* tmp_min = new int[capasity_];
      node_size_++;
      for (int i = 0; i < node_size_ - 1; i++) {
        tmp_value[i] = value_[i];
        tmp_min[i] = min_[i];
      }
      tmp_value[node_size_ - 1] = data;
      tmp_min[node_size_ - 1] =
          std::min(tmp_value[node_size_ - 1], tmp_min[node_size_ - 2]);
      delete[] value_;
      delete[] min_;
      value_ = tmp_value;
      min_ = tmp_min;
    } else {
      ++node_size_;
      value_[node_size_ - 1] = data;
      min_[node_size_ - 1] =
          (node_size_ == 1)
              ? data
              : std::min(value_[node_size_ - 1], min_[node_size_ - 2]);
    }
    std::cout << "ok" << std::endl;
  }
  void Pop() {
    if (node_size_ == 0) {
      std::cout << "error" << std::endl;
    } else {
      std::cout << value_[node_size_ - 1] << std::endl;
      --node_size_;
    }
  }
  void Back() {
    if (node_size_ == 0) {
      std::cout << "error" << std::endl;
    } else {
      std::cout << value_[node_size_ - 1] << std::endl;
    }
  }
  void Min() {
    if (node_size_ == 0) {
      std::cout << "error" << std::endl;
    } else {
      std::cout << min_[node_size_ - 1] << std::endl;
    }
  }
  void Size() { std::cout << node_size_ << std::endl; }
  void Clear() {
    delete[] value_;
    delete[] min_;
    node_size_ = 0;
    capasity_ = 1;
    value_ = new int[capasity_];
    min_ = new int[capasity_];
    std::cout << "ok" << std::endl;
  }

 private:
  int* value_;
  int* min_;
  int node_size_;
  int capasity_;
};

int main() {
  int m;
  std::cin >> m;
  Stack stack;
  for (int i = 0; i < m; ++i) {
    std::string command;
    std::cin >> command;
    if (command == "push") {
      int number;
      std::cin >> number;
      stack.Push(number);
    }
    if (command == "pop") {
      stack.Pop();
    }
    if (command == "back") {
      stack.Back();
    }
    if (command == "min") {
      stack.Min();
    }
    if (command == "size") {
      stack.Size();
    }
    if (command == "clear") {
      stack.Clear();
    }
  }
}
