#include "dataset_parser.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

Dataset DatasetParser::Parse(const std::string& file_path) {
  Dataset dataset;
  std::ifstream file(file_path);

  if (!file.is_open() && !CheckEmnistDataset(file_path)) {
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
    dataset.AppendPair(tmp_data);
  }

  dataset.SetSizeOutputLayers(FindOutputLayerSize(file_path));

  return dataset;
}

int DatasetParser::FindOutputLayerSize(const std::string& file_path) {
  std::filesystem::path filePath(fullPath);
  std::string fileName = filePath.filename().string();
  std::string directory = filePath.directory().string();
  // emnist-*-
  // in same directory emnist-*-mapping.txt
  // return kol-vo strok v mapping
}

bool DatasetParser::CheckEmnistDataset(const std::string& file_path) {
  std::filesystem::path filePath(fullPath);
  std::string fileName = filePath.filename().string();
  // return true/false fileName == "emnist-*"
  return false;
}
