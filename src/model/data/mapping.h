#ifndef MULTILAYER_PERCEPTRON_CPP_QT_MAPPING_H
#define MULTILAYER_PERCEPTRON_CPP_QT_MAPPING_H

#include <set>
#include <vector>

class Mapping {
 public:
  void AppendData(const std::set<int>&);
  [[nodiscard]] std::size_t GetDataSize() const;
  [[nodiscard]] const std::vector<std::set<int>>& GetData() const;
  void SetMinIndex(std::size_t min_index);
  [[nodiscard]] std::size_t GetMinIndex() const;

 private:
  std::vector<std::set<int>> data_;
  std::size_t min_index_;
};

#endif  // MULTILAYER_PERCEPTRON_CPP_QT_MAPPING_H
