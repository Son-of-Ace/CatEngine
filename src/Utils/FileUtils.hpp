#include <filesystem>
#include <algorithm>
#include <string>
#include <vector>

namespace fs = std::filesystem;

static std::vector<std::string> GetAnimationFrames(const std::string& animationPath) {
  std::vector<std::string> output;

  for (const auto& entry : fs::directory_iterator(animationPath)) {
    if (entry.path().extension() == ".png") {
      output.push_back(entry.path().string());
    }
  }

  std::sort(output.begin(), output.end());
  return output;
}
