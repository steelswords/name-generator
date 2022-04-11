#include <filesystem>
#include <iostream>
#include <string>
#include "TextGenerationGrammar.hpp"

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cerr << "Usage: " << std::string(argv[0]) << " <grammar.dat file>"
      << std::endl;
    return 1;
  }
  // Check if passed in file actually exists.
  std::string grammarFile(argv[1]);
  std::filesystem::path filePath {grammarFile};
  if (!std::filesystem::exists(filePath))
  {
    std::cerr << "ERROR! " << filePath << " does not exist!" << std::endl;
    return 2;
  }

  TextGenerationGrammar generator(grammarFile);
  std::cout << generator.generate() << std::endl;
  generator.clearState();
  return 0;
}
