#ifndef MULTILAYER_PERCEPTRON_CPP_QT_MAPPING_H
#define MULTILAYER_PERCEPTRON_CPP_QT_MAPPING_H

#include <map>
#include <set>

class Mapping {
 public:
  void AddData(int, const std::set<int>&);
  int GetDataSize() const;
  std::map<int, std::set<int> > GetData() const;
  std::set<int> GetItem(int) const;

 private:
  std::map<int, std::set<int> > data_;
};

#endif  // MULTILAYER_PERCEPTRON_CPP_QT_MAPPING_H
