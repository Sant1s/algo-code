#include <algorithm>
#include <iostream>
#include <vector>

class Heap {
 public:
  std::vector<int> heap;
  int64_t Parent(int child_index) { return (child_index - 1) / 2; }
  int64_t LeftChild(int parent_index) { return 2 * parent_index + 1; }
  int64_t RightChild(int parent_index) { return 2 * parent_index + 2; }
  void Insert(int data) {
    heap.push_back(data);
    SiftUp(heap.size() - 1);
  }
  int GetMin() { return heap[0]; }
  void ExtractMin() {
    if (heap.size() > 1) {
      heap[0] = heap[heap.size() - 1];
      SiftDown(0);
    }
    heap.resize(heap.size() - 1);
  }
  int64_t Size() { return heap.size(); }

 private:
  void SiftDown(int64_t index) {
    while (LeftChild(index) < Size()) {
      int64_t k = LeftChild(index);
      if (k + 1 < Size() && heap[k + 1] > heap[k]) {
        ++k;
      }
      if (heap[k] > heap[index]) {
        std::swap(heap[index], heap[k]);
        index = k;
      } else {
        break;
      }
    }
  }
  void SiftUp(int64_t index) {
    int64_t tmp = Parent(index);
    if (index != 0 && heap[tmp] < heap[index]) {
      std::swap(heap[tmp], heap[index]);
      SiftUp(tmp);
    }
  }
};

int main() {
  int64_t n, k, a_0, x, y;
  std::cin >> n >> k;
  std::cin >> a_0 >> x >> y;
  Heap arr;
  for (int i = 0; i < n; ++i) {
    a_0 = (a_0 * x + y) % (1ll << 30);
    if (i < k) {
      arr.Insert(a_0);
    } else {
      if (arr.GetMin() > a_0) {
        arr.ExtractMin();
        arr.Insert(a_0);
      }
    }
  }
  std::sort(arr.heap.begin(), arr.heap.end());
  for (int64_t i = 0; i < arr.Size(); ++i) {
    std::cout << arr.heap[i] << " ";
  }
  std::cout << std::endl;
}
