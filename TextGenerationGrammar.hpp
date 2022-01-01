#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include <map>
#include <vector>

struct TextToken
{
  /** @brief A terminal TextToken will have only one element in the outer vector */
  std::vector<std::vector<std::string>> contents;
  std::vector<std::string> &choosePossibility();
  static std::vector<std::string> splitLineIntoWords(std::string line);
};

class TextGenerationGrammar
{
public:
  TextGenerationGrammar(std::string fileName);
  TextToken getToken(std::string tokenName);

  std::string generate() { return generate("MAIN"); }
  std::string generate(std::string tokenName);
protected:
  std::map<std::string, std::shared_ptr<TextToken>> tokens;
  void parse(std::string rawGrammarInput);
};

bool startsWith(std::string input, std::string prefix);

