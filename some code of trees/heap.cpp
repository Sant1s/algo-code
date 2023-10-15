#include <iostream>
#include <vector>
class Heap {
 public:
  void Insert(int64_t data, int index) {
    heap_.push_back({data, index});
    SiftUp(heap_.size() - 1);
  }
  int64_t Size() { return heap_.size(); }
  int64_t GetMin() { return heap_.at(0).first; }
  void ExtractMin() {
    std::swap(heap_.at(0), heap_.at(heap_.size() - 1));
    heap_.pop_back();
    SiftDown(0);
  }
  void DecreaseKey(int64_t delta, int64_t index) {
    int64_t tmp_index = 0;
    for (tmp_index = 0; tmp_index < Size(); ++tmp_index) {
      if (index == heap_[tmp_index].second) {
        heap_[tmp_index].first -= delta;
        break;
      }
    }
    SiftUp(tmp_index);
  }

 private:
  std::vector<std::pair<int64_t, int>> heap_;
  void SiftUp(int64_t index) {
    while (index != 0) {
      int64_t tmp = (index - 1) / 2;
      if (heap_[index].first < heap_[tmp].first) {
        std::swap(heap_[index], heap_[tmp]);
        index = tmp;
      } else {
        break;
      }
    }
  }

  void SiftDown(int64_t index) {
    while (2 * index + 1 < Size()) {
      int64_t tmp = 2 * index + 1;
      if (tmp + 1 < Size() && heap_[tmp + 1].first < heap_[tmp].first) {
        ++tmp;
      }
      if (heap_[tmp].first < heap_[index].first) {
        std::swap(heap_[index], heap_[tmp]);
        index = tmp;
      } else {
        break;
      }
    }
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  Heap heap;
  int64_t n;
  std::cin >> n;
  for (int64_t i = 0; i < n; ++i) {
    std::string command;
    std::cin >> command;
    if (command == "insert") {
      int64_t number;
      std::cin >> number;
      heap.Insert(number, i + 1);
    }
    if (command == "getMin") {
      std::cout << heap.GetMin() << std::endl;
    }
    if (command == "extractMin") {
      heap.ExtractMin();
    }
    if (command == "decreaseKey") {
      int64_t num;
      size_t index;
      std::cin >> index >> num;
      heap.DecreaseKey(num, index);
    }
  }
}
