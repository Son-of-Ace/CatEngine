#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <print>
#include <string>

namespace fs = std::filesystem;

class FileBridge {
private:
  using ifstream = std::ifstream;
  using ofstream = std::ofstream;

  static bool FileExists(const std::string &filepath) {
    return fs::exists(filepath);
  }

public:
  static void CreateDirectory(const std::string &path) {
    if (fs::exists(path)) {
      std::print("Directory already exists at path: {} - skipping creation!\n",
                 path);
      return;
    }

    fs::create_directory(path);
  }

  static void RemoveDirectory(const std::string &path) {
    if (!fs::exists(path)) {
      std::print("Directory doesn't exist at path: {} - skipping remove!\n",
                 path);
      return;
    }

    fs::remove(path);
  }

  static FILE *CreateFile(const std::string &filepath) {
    if (FileExists(filepath)) {
      std::print("File already exists at path: {} - skipping creation!\n",
                 filepath);
      return nullptr;
    }

    return fopen(filepath.c_str(), "r");
  }

  static void RemoveFile(const std::string &filepath) {
    if (!FileExists(filepath)) {
      std::print("File doesn't exist at path: {} - skipping remove!\n",
                 filepath);
      return void();
    }

    fs::remove(filepath);
  }

  static std::string ReadFile(const std::string &filepath) {
    std::string content;

    ifstream file(filepath);

    if (!file.is_open()) {
      std::print(stderr, "Error opening file for reading at: {}", filepath);
      return "";
    }
    std::string s;

    while (getline(file, s)) {
      content += s;
    }

    file.close();
    return content;
  }

  static void WriteFile(const std::string &filepath, const std::string &text) {
    if (!fs::exists(filepath)) {
      CreateFile(filepath);
    }

    ofstream file(filepath);

    if (!file.is_open()) {
      std::print(stderr, "Error opening file for writing at: {}", filepath);
    }

    file << text;
    file.close();
  }

  static void WriteLine(const std::string &filepath, const std::string &text) {
    WriteFile(filepath, text + "\n");
  }
};