#include "TextGenerationGrammar.hpp"
#include <stdexcept>
#include <exception>

#define MAX_LINE_LENGTH_IN_CHARS 1024

#define DEBUG 1

// Returns true if 'input' starts with 'prefix'
// Ignores whitespace at the beginning of 'input'
bool startsWith(std::string input, std::string prefix)
{
  // First loop to cut out whitespace
  auto inputIter = input.begin();
  for (; inputIter < input.end(); ++inputIter)
  {
    if ( (*inputIter == ' ') || (*inputIter == '\t') )
      ;
    else
      break;
  }
  // Now compare to prefix
  auto prefixIter = prefix.begin();
  for (auto prefixIter = prefix.begin(); prefixIter < prefix.end(); ++prefixIter)
  {
    if (*inputIter != *prefixIter)
      return false;
    inputIter++;
  }
  return true;
}

bool isWhitespace(char c)
{
  return c == ' ' || c == '\t';
}

std::vector<std::string> TextToken::splitLineIntoWords(std::string line)
{
  std::vector<std::string> result;
  // Allow whitespace at beginning of line
  auto lineIter = line.begin();
  while (isWhitespace(*lineIter)) lineIter++;
  auto beginningOfWord = lineIter;
  for (; lineIter <= line.end(); lineIter++)
  {
    // If we have found whitespace, we found the end of a word.
    // Also, if it is the last thing, we have found a word.
    // Add word to vector
    if (isWhitespace(*lineIter) || (lineIter == line.end()))
    {
      std::string word;
      for (; beginningOfWord < lineIter; beginningOfWord++)
      {
        word.push_back(*beginningOfWord);
      }
      result.emplace_back(word);
#if DEBUG
      std::cout << "Found word '" << word << "'" << std::endl;
#endif
    }
  }
  return result;
}

TextGenerationGrammar::TextGenerationGrammar(std::string fileName)
{
  // Error checking
  std::ifstream file(fileName, std::ios::in);
  if (!file)
  {
    std::cerr << "Cannot open file!" << std::endl;
    throw std::runtime_error("Problem opening file " + fileName);
  }

  uint32_t lineNumber = 1;
  char *buffer = new char[MAX_LINE_LENGTH_IN_CHARS];
  TextToken *inProgressTextToken = nullptr;
  std::string tokenName = "";


  // While the file still has lines to read
  // Get a line. 
  while (file.getline(buffer, MAX_LINE_LENGTH_IN_CHARS))
  {
    std::string line(buffer);
#ifdef DEBUG
    std::cout << "Parsing line '" << line << "'" << std::endl;
#endif
    // Do something based on type
    // If it's a comment, ignore
    if (startsWith(line, "#"))
    {
      continue;
    }
    // If token definition, add a new TextToken
    else if (startsWith(line, "["))
    {
      // If there is something stored in 'inProgressTextToken', then we were
      // working on a section already and need to store it.
      if (inProgressTextToken != nullptr)
      {
        tokens[tokenName] = std::shared_ptr<TextToken>(inProgressTextToken);
      }
      // Either way, we need a new Text Token now
      inProgressTextToken = new TextToken();

      // Get the name of the token
      auto endingBracketPosition = line.find(']');
      if (endingBracketPosition == std::string::npos)
      {
        std::string exceptionMessage = "Parsing error on line " + lineNumber;
        std::cerr << exceptionMessage << std::endl;
        throw std::runtime_error(exceptionMessage);
      }
      // +1 to beginning and -1 to end to take off the [ and ] characters
      tokenName = line.substr(line.find('[') + 1, endingBracketPosition - 1);
      std::cout << "Found new token: " << tokenName << std::endl;

    }
    // If the line doesn't start with anything, it's likely contents
    else
    {
      // But perhaps it's out of a section.
      if (inProgressTextToken == nullptr)
      {
        std::string message = "Got text context when a section name was expected!";
        std::cerr << message << std::endl;
        throw std::runtime_error(message);
        continue;
      }
      else
      {
        if (line.empty()) continue;
        std::vector<std::string> wordsFromLine = TextToken::splitLineIntoWords(line);
        inProgressTextToken->contents.emplace_back(wordsFromLine);
      }

    }
    
      // For each line until we reach a new token definition, add this possibility to this token's contents
    lineNumber++;
  }
}
