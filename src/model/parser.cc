#include "parser.h"

#include <fstream>
#include <sstream>

Dataset Parser::ParseDataset(const std::string &file_path) {
  Dataset dataset;
  std::ifstream file(file_path);

  if (!file.is_open()) {
    throw std::ios_base::failure("The file does not exist!");
  }

  std::string buffer_line;

  while (std::getline(file, buffer_line)) {
    std::stringstream string_stream(buffer_line);
    std::pair<Picture, int> tmp_data;
    std::vector<int> pixels;
    std::string pixel;

    string_stream >> tmp_data.second;
    string_stream.ignore(1);

    while (std::getline(string_stream, pixel, ',')) {
      pixels.push_back(std::stoi(pixel));
    }

    tmp_data.first.SetData(pixels);
    dataset.AppendDataToVector(tmp_data);
  }

  return dataset;
}

Mapping Parser::ParseMapping(const std::string &file_path) {
  Mapping mapping;
  std::ifstream file(file_path);

  if (!file.is_open()) {
    throw std::ios_base::failure("The file does not exist!");
  }

  std::string buffer_line;

  while (std::getline(file, buffer_line)) {
    std::stringstream string_stream(buffer_line);
    int mapped_key;
    std::set<int> value;

    string_stream >> mapped_key;

    int temp;
    while (string_stream >> temp && !string_stream.fail()) {
      value.insert(temp);
    }

    mapping.AddData(mapped_key, value);
  }

  return mapping;
}
