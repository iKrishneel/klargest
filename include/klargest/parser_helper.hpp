
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
class ParserHelper {
  
 private:
  VectorPairs pairs;
  int k;
 protected:
  bool split(VectorPairs &, const std::string, const char = ' ');
  bool readDataFromFile(VectorPairs &, std::string);
  void readDataFromCL(VectorPairs &);
  void help();
  bool isFile(const std::string);
  bool isValidK(const std::string);
  void getKFromCL(const std::string = "");
  
 public:
  ParserHelper(const int, const char **);
  VectorPairs getPairs();
};

#endif /* PARSER_HELPER_H */
