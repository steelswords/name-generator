#include <iostream>
#include <string>
#include "TextGenerationGrammar.hpp"

int main()
{
  TextGenerationGrammar generator("backstory.dat");
  std::cout << generator.generate() << std::endl;
  generator.clearState();
  std::cout << generator.generate() << std::endl;
  generator.clearState();
  std::cout << generator.generate() << std::endl;
  generator.clearState();
  std::cout << generator.generate() << std::endl;
  generator.clearState();
  std::cout << generator.generate() << std::endl;
  generator.clearState();
  std::cout << generator.generate() << std::endl;
  generator.clearState();
  std::cout << generator.generate() << std::endl;
  generator.clearState();
  return 0;
}
