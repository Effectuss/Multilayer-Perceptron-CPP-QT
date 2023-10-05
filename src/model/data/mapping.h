#ifndef MULTILAYER_PERCEPTRON_CPP_QT_MAPPING_H
#define MULTILAYER_PERCEPTRON_CPP_QT_MAPPING_H

#include <vector>
#include <set>

class Mapping {
 public:
  void AppendData(const std::set<int>&);
  [[nodiscard]] std::size_t GetDataSize() const;
  [[nodiscard]] const std::vector<std::set<int>>& GetData() const;

 private:
  std::vector<std::set<int>> data_;
};

#endif  // MULTILAYER_PERCEPTRON_CPP_QT_MAPPING_H
