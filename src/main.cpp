
#include <iostream>
#include <vector>
#include <cstdio>
#include <cassert>
#include <sstream>

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

int main(int argc, const char *argv[]) {

  // condiiton to check that input is provided
  if (argc < 2 || argv[argc-1] == NULL) {
    std::cout << "\033[1;31m Provide the data\33[0m\n";
    std::exit(EXIT_FAILURE);
  }
  
  // check that input is file
  if (argc == 2) {
    //
  }

  const int COUNT = 80;
  
  std::cout << std::string(COUNT, '-') << std::endl;
  std::cout << "Enter input thru console in the following format\n"
     "\033[032m<unique identifier><white_space><numeric value>"
     "\033[033m\t [eg: 1426828011 9]\033[0m\n";
  std::cout << "To signal end of input, press c\n";
  std::cout << std::string(COUNT, '-') << std::endl << std::endl;
    
  std::vector<MyPair> pairs;
  std::string input;
  int line_count = 1;
  while (true) {
    // get the user input
    std::getline(std::cin >> std::ws, input);
    
    // break the loop to get the data
    if (input == "C" || input == "c") {
      if (!pairs.empty()) {
        std::cout << std::string(COUNT, '-') << std::endl;
        std::cout << "END OF INPUT\n" << std::string(COUNT, '-') << std::endl;
      }
      break;
    }

    // split and pack
    if (!split(pairs, input)) {
      std::cout << "\033[033m[WARN]Ignored->Incorrect Format\033[0m\n";
    }
  }

  if (pairs.empty()) {
    std::cout << "No input to process\n";
    return 0;
  }
  
  /*
  ParserHelper *parser = new ParserHelper(argc, argv);
  parser->isFileInput();
  delete parser;
  */
  return 0;
}
