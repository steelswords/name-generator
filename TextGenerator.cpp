#include "TextGenerator.hpp"
#include <exception>

void TextGenerator::parse(std::string inputFile)
{
  dictionary *dict = iniparser_load(inputFile);
  if (NULL == ini)
  {
    std::cerr << "Cannot parse file " << inputFile << "!" << std::endl;
    throw std::runtime_exception("Cannot parse file " + inputFile);
  }
  else
  {
    m_iniData.reset(dict);
  }

  // Get number of keys in 
    
}

std::string TextGenerator::expandToken(std::string token)
{
  std::string result = "";
  if (iniparser_
  return result;
}
