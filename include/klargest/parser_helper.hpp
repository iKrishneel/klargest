
#pragma once
#ifndef PARSER_HELPER_H
#define PARSER_HELPER_H

#include <iostream>
#include <vector>
#include <cstdio>
#include <cassert>
#include <sstream>
#include <iomanip>
#include <fstream>


/**
 * class to helper with parsing of cmd
 */
class ParserHelper {
  
 private:
  std::vector<std::string> inputs;
  
 public:
  ParserHelper(const int, const char **);
  bool isValidInput();
  bool isFileInput();
  void getInput();
};

#endif /* PARSER_HELPER_H */
