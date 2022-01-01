#include <iostream>
#include <string>
#include "TextGenerationGrammar.hpp"

int main()
{
  TextGenerationGrammar generator("inns.dat");
  std::cout << generator.generate() << std::endl;
  std::cout << generator.generate() << std::endl;
  std::cout << generator.generate() << std::endl;
  std::cout << generator.generate() << std::endl;
  std::cout << generator.generate() << std::endl;
  std::cout << generator.generate() << std::endl;
  std::cout << generator.generate() << std::endl;
  return 0;
}
