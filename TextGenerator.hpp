#pragma once
#include <string>
#include <memory>

extern "C"
{
#include "iniparser/src/dictionary.h"
#include "iniparser/src/iniparser.h"
}

struct TextToken
{
  /** @brief A terminal TextToken will have only one element in the outer vector */
  std::vector<std::vector<std::string>> contents;
};

class TextGenerator
{
public:
  void parse(std::string inputFile);
  std::string expandToken(std::string token);
  std::string generateText();

protected:
  std::shared_ptr<dictionary> iniData; 

};
