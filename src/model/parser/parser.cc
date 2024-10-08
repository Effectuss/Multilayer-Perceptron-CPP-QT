#include "parser.h"

#include <fstream>
#include <sstream>

Dataset Parser::ParseDataset(const std::string &file_path,
                             std::size_t index_offset) {
  Dataset dataset;
  std::ifstream file(file_path);

  if (!file.is_open()) {
    throw std::ios_base::failure("The file does not exist!");
  }

  std::string buffer_line;

  while (std::getline(file, buffer_line)) {
    std::stringstream string_stream(buffer_line);
    std::pair<Picture, int> tmp_data;
    std::vector<double> pixels;
    std::string pixel;
    std::size_t index;

    string_stream >> index;
    string_stream.ignore(1);

    while (std::getline(string_stream, pixel, ',')) {
      pixels.push_back(std::stoi(pixel) / 255.0);
    }

    tmp_data.second = index - index_offset;

    if (tmp_data.second < 0) {
      throw std::logic_error("Wrong mapping loaded or wrong index offset");
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

  std::size_t max_index = 0;

  while (std::getline(file, buffer_line)) {
    std::stringstream string_stream(buffer_line);
    std::size_t mapped_index;
    std::set<int> value;

    string_stream >> mapped_index;
    if (mapped_index > max_index) {
      max_index = mapped_index;
    }

    int temp;
    while (string_stream >> temp && !string_stream.fail()) {
      value.insert(temp);
    }

    mapping.AppendData(value);
  }

  mapping.SetMinIndex(max_index + 1 - mapping.GetDataSize());

  return mapping;
}
