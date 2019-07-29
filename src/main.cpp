
/*
#include <iostream>
#include <vector>
#include <cstdio>
#include <cassert>
#include <sstream>
#include <iomanip>
#include <fstream>
*/

#include <klargest/parser_helper.hpp>

/**
 * class to helper with parsing of cmd
 */
/*
class ParserHelper {
  
 private:
  std::vector<std::string> inputs;
  
 public:
  ParserHelper(const int, const char **);
  bool isValidInput();
  bool isFileInput();
  void getInput();
};


ParserHelper::ParserHelper(const int argc, const char** argv) {
  this->inputs.clear();
  for (int i = 1; i < argc; ++i) {
    inputs.push_back(std::string(argv[i]));
  }
}

bool ParserHelper::isValidInput() {
  if (this->inputs.empty()) {
    return false;
  }

  return true;
}

bool ParserHelper::isFileInput() {
  
}

void ParserHelper::getInput() {
  
}
*/



template<typename T, typename U>
struct Pair {
  T identifier;
  U value;
  
  Pair(T id, U val) {
    identifier = id;
    value = val;
  }
};

using MyPair = Pair<std::string, int>;

/**
 * function to split the input
 */
bool split(std::vector<MyPair> &pairs, const std::string input,
           const char delimiter = ' ') {
  
  std::string token;
  std::istringstream iss(input);
  std::vector<std::string> tokens;
  while (std::getline(iss, token, delimiter)) {
    tokens.push_back(token);
  }

  // check that input is valid
  bool status = false;
  if (tokens.size() == 2) {
    pairs.push_back(MyPair(tokens.at(0), std::stoi(tokens.at(1))));
    status = true;
  }
  return status;
}

bool read_from_textfile(std::vector<MyPair> &pairs, const std::string filepath) {
  // read file
  std::ifstream infile(filepath.c_str(), std::ios::in);

  // invalid file return false
  if (!infile.is_open()) {
    return false;
  }
  
  // Read the next line from File untill it reaches the end.
  std::string line;
  while (std::getline(infile, line)) {
    split(pairs, line);
  }

  // close the file
  infile.close();
  return true;
}

#define COUNT 80


void help() {
  std::cout << "\033[33mOnly takes file path as input or when input argument "
      "is not provided user will be prompted to enter the data"
      "\33[0m\n";
}

void request_data_input(std::vector<MyPair> &pairs) {
  std::cout << std::string(COUNT, '-') << std::endl;
  std::cout << "Enter input thru console infile the following format\n"
     "\033[032m<unique identifier><white_space><numeric value>"
     "\033[033m\t [eg: 1426828011 9]\033[0m\n";
  std::cout << "To signal end of input, press c\n";
  std::cout << std::string(COUNT, '-') << std::endl << std::endl;
  std::string input;
  int line_count = 1;
  while (true) {

    std::cout << std::setfill(' ') << std::setw(4) << line_count++ << "| ";
        
    // get the user input
    std::getline(std::cin >> std::ws, input);
    
    // break the loop to get the data
    if (input == "C" || input == "c") {
      if (!pairs.empty()) {
        std::cout << std::string(COUNT, '-') << std::endl;
        // std::cout << "END OF INPUT\n" << std::string(COUNT, '-') << std::endl;
      }
      break;
    }

    // split and pack
    if (!split(pairs, input)) {
      line_count--;
      std::cout << "\033[033m[WARN]Ignored->Incorrect Format\033[0m\n";
    }
  }

}

int main(int argc, const char *argv[]) {

  // input argument is only the file path
  if (argc > 2) {
    help();
    std::exit(EXIT_FAILURE);
  }
  
  std::vector<MyPair> pairs;
  
  // check that input is file
  if (argc == 1) {
    request_data_input(pairs);
  } else if (argc == 2) {
    if (!read_from_textfile(pairs, argv[1])) {
      std::cout << "\033[031mInvalid filepath: "<< argv[1] << " \033[0m\n";
      help();
    }
  }
  
  // do not proceed if input is empty
  if (pairs.empty()) {
    std::cout << "No input to process\n";
    return 0;
  }

  for (auto it = pairs.begin(); it != pairs.end(); it++) {
    std::cout << it->identifier << " " << it->value  << "\n";
  }


  
  /*
  ParserHelper *parser = new ParserHelper(argc, argv);
  parser->isFileInput();
  delete parser;
  */
  return 0;
}
