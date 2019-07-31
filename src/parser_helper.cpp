
#include <klargest/parser_helper.hpp>

ParserHelper::ParserHelper(const int argc, const char** argv) {
  
  this->pairs.clear();

  if (argc > 2) {
    this->help();
    std::exit(EXIT_FAILURE);
  }
  
  // check that input is file
  if (argc == 1) {
    this->readDataFromCL(this->pairs);
  } else if (argc == 2) {
    if (!this->readDataFromFile(this->pairs, argv[1])) {
      std::cout << "\033[031mInvalid filepath: "<< argv[1] << " \033[0m\n";
      this->help();
    }
  }
}

/**
   function to read data from the text file
 */
bool ParserHelper::readDataFromFile(VectorPairs &pairs,
                                    const std::string filepath) {
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


/**
 * function to split the input strings 
 */
bool ParserHelper::split(VectorPairs &pairs, const std::string input,
                         const char delimiter) {
  std::string token;
  std::istringstream iss(input);
  std::vector<std::string> tokens;
  while (std::getline(iss, token, delimiter)) {
    tokens.push_back(token);
  }

  // check that input is valid
  bool status = false;
  if (tokens.size() == 2) {
    pairs.push_back(MyPair(tokens.at(0), std::stoi(tokens.at(1)),
                           pairs.size()));
    status = true;
  }
  return status;
}

/*
  function to read data from command line
 */
void ParserHelper::readDataFromCL(VectorPairs &pairs) {

  std::cout << std::string(CMD_COUNT, '-') << std::endl;
  std::cout << "Enter input thru console infile the following format\n"
     "\033[032m<unique identifier><white_space><numeric value>"
     "\033[033m\t [eg: 1426828011 9]\033[0m\n";
  std::cout << "To signal end of input, press c\n";
  std::cout << std::string(CMD_COUNT, '-') << std::endl << std::endl;
  
  std::string input;
  int line_count = 1;
  while (true) {
    std::cout << std::setfill(' ') << std::setw(4) << line_count++ << "| ";
        
    // get the user input
    std::getline(std::cin >> std::ws, input);
    
    // break the loop to get the data
    if (input == "C" || input == "c") {
      if (!pairs.empty()) {
        std::cout << std::string(CMD_COUNT, '-') << std::endl;
        // std::cout << "END OF INPUT\n"
        //           << std::string(CMD_COUNT, '-') << std::endl;
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

VectorPairs ParserHelper::getPairs() {
  return this->pairs;
}

void ParserHelper::help() {
  std::cout << "\033[33mOnly takes file path as input or when input argument "
      "is not provided user will be prompted to enter the data"
      "\33[0m\n";
}

