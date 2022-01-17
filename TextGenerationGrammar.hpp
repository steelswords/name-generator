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
  std::string reference {""};
  std::vector<std::string> &choosePossibility();
  bool hasReference() { return reference.empty(); }
  static std::vector<std::string> splitLineIntoWords(std::string line);
};

class TextGenerationGrammar
{
public:
  TextGenerationGrammar(std::string fileName);

  std::string generate() { return generate("MAIN"); }
  std::string generate(std::string tokenName);
  std::string expandWordIfToken(std::string word);
  void clearState(); // To stop having a shared history, run this function.
  bool hasReferenceName(std::string tokenText, std::string &tokenName, std::string &referenceName);
protected:
  std::map<std::string, std::shared_ptr<TextToken>> tokens;
  std::map<std::string, std::string> namedTokens;
  void parse(std::string rawGrammarInput);
};

bool startsWith(std::string input, std::string prefix);

