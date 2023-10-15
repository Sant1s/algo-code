#include <iostream>
#include <vector>

void Merge(std::vector<std::pair<int, int>>& vector,
           std::vector<std::pair<int, int>>& vector_1,
           std::vector<std::pair<int, int>>& vector_2) {
  unsigned int size_1 = vector_1.size();
  unsigned int size_2 = vector_2.size();
  size_t pointer_1 = 0;
  size_t pointer_2 = 0;
  while ((pointer_1 < size_1) && (pointer_2 < size_2)) {
    if (vector_1.at(pointer_1) < vector_2.at(pointer_2)) {
      vector.push_back(vector_1.at(pointer_1));
      ++pointer_1;
    } else {
      vector.push_back(vector_2.at(pointer_2));
      ++pointer_2;
    }
  }
  while (pointer_1 < size_1) {
    vector.push_back(vector_1.at(pointer_1));
    ++pointer_1;
  }
  while (pointer_2 < size_2) {
    vector.push_back(vector_2.at(pointer_2));
    ++pointer_2;
  }
}

void MergeSort(std::vector<std::pair<int, int>>& vector) {
  if (vector.size() == 1) {
    return;
  }
  if (vector.size() != 1) {
    auto tmp = vector.begin() + (vector.end() - vector.begin()) / 2;
    std::vector<std::pair<int, int>> v1(vector.begin(), tmp);
    std::vector<std::pair<int, int>> v2(tmp, vector.end());
    MergeSort(v1);
    MergeSort(v2);
    vector.clear();
    Merge(vector, v1, v2);
  }
}

void MasupLine(std::vector<std::pair<int, int>>& array) {
  std::vector<std::pair<int, int>> mashup_line;
  std::pair<int, int> tmp_line = array[0];
  int counter = 0;
  for (size_t i = 0; i + 1 < array.size(); i++) {
    if (tmp_line.second >= array[i + 1].first &&
        tmp_line.second <= array[i + 1].second) {
      tmp_line = {array[counter].first, array[i + 1].second};
    }
    if (tmp_line.second < array[i + 1].first) {
      counter = i + 1;
      mashup_line.push_back(tmp_line);
      tmp_line = array[i + 1];
    }
  }
  mashup_line.push_back(tmp_line);
  std::cout << mashup_line.size() << std::endl;
  for (size_t i = 0; i < mashup_line.size(); i++) {
    std::cout << mashup_line[i].first << " " << mashup_line[i].second
              << std::endl;
  }
}

int main() {
  size_t k;
  std::cin >> k;
  std::vector<std::pair<int, int>> mashup_line_segment;
  for (size_t i = 0; i < k; i++) {
    int segment_start, segment_end;
    std::cin >> segment_start >> segment_end;
    mashup_line_segment.push_back({segment_start, segment_end});
  }
  MergeSort(mashup_line_segment);
  MasupLine(mashup_line_segment);
}
