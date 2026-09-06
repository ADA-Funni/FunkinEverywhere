#include <string>
#include <nonstd/expected.hpp>

bool fileExists(const std::string& filename);
nonstd::expected<std::vector<std::string>, std::string> listDirectory(const std::string &path);