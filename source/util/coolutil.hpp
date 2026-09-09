#include <string>
#include <nonstd/expected.hpp>

bool fileExists(const std::string& filename);
std::string parentPath(const std::string &path);
nonstd::expected<std::vector<std::string>, std::string> listDirectory(const std::string &path);