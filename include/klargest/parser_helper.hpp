
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

#include <klargest/pairs.hpp>
#include <klargest/contants.hpp>

/**
 * class to helper with parsing of cmd
 */

using MyPair = Pair<std::string, int>;
using VectorPairs = std::vector<MyPair>;

class ParserHelper {
  
 private:
  // std::vector<std::string> inputs;
  VectorPairs pairs;
  bool split(VectorPairs &, const std::string, const char = ' ');
  
 public:
  ParserHelper(const int, const char **);
  bool readDataFromFile(VectorPairs &, std::string);
  void readDataFromCL(VectorPairs &);
  void help();

  VectorPairs getPairs();
};

#endif /* PARSER_HELPER_H */
