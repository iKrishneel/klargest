// Copyright (C) 2019 by Krishneel

#include <klargest/parser_helper.hpp>

ParserHelper::ParserHelper(const int argc, const char** argv) {
  
  this->pairs_.clear();

  if (argc > 3) {
    this->help();
    std::exit(EXIT_FAILURE);
  }
  
  // check that input is file
  if (argc == 1) {
    this->readDataFromCL(this->pairs_);
  } else if (argc > 1) {
    // check that input is a file with valid extension
    if (isFile(argv[1])) {
      // load the file
       if (readDataFromFile(this->pairs_, argv[1])) {
          // user also provided the value for k
          this->getKFromCL(argc == 3 ? argv[2] : "");
       } else {
         std::cout << "\033[031mFile not read \033[0m\n";
         std::exit(EXIT_FAILURE);
       }
    }
  }
}

/*
  function to check that the file path provided is a valid file
 */
bool ParserHelper::isFile(const std::string str) {
  std::string file_ext = "txt";
  try {
    if (str.substr(str.find_last_of(".")) == file_ext ||
        str.substr(str.find_last_of(".") + 1) == file_ext) {
      return true;
    }
    throw std::invalid_argument("invalid file extension");
  } catch (std::out_of_range const &error) {
    // std::cout << "\033[031m" << error.what()  << "\033[0m\n";
    this->help();
  } catch (std::invalid_argument const &error) {
    // std::cout << "\033[031m" << error.what()  << "\033[0m\n";
    this->help();
  }
    return false;
}

/*
  function to check that the value of k is valid and within the
  range. Incase of invalid k, it will prompt to user to enter a valid
  value of k
 */
bool ParserHelper::isValidK(const std::string str) {
  try {
    this->k_ = std::stoi(str);
    if (this->k_ < 1 || this->k_ > static_cast<int>(this->pairs_.size())) {
      std::string what = "X not in range of the number of elements\n";
      throw std::invalid_argument(what);
    }
    return true;
  } catch (std::invalid_argument const &error) {
    std::cout << "\033[031m" << error.what() <<
        "Enter valid value for x: x>0 \033[0m\n";
  }
  return false;
}

/*
  function to get the k value from the command line.
  the [C or c] is is used as termination signal
 */
bool ParserHelper::getKFromCL(const std::string s) {
  std::string input = s;
  while (input.empty() || !this->isValidK(input)) {
    std::cout << "Enter a value for X: [0 < X < " <<
        this->pairs_.size() + 1 << "] : ";
    // get the user input
    std::getline(std::cin >> std::ws, input);
    
    if (input == "C" || input == "c") {
      return false;
    }
  }
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
     pairs.push_back(DPair(tokens.at(0), std::stoi(tokens.at(1))));
    status = true;
  }
  return status;
}

/*
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
      }
      break;
    }

    // split and pack
    if (!split(pairs, input)) {
      line_count--;
      std::cout << "\033[033m[WARN]Ignored->Incorrect Format\033[0m\n";
    }
  }

  // get k if pairs has data
  if (!pairs.empty()) {
    this->getKFromCL();
  }
}

VectorPairs ParserHelper::getPairs() {
  return this->pairs_;
}

int ParserHelper::getK() {
  return this->k_;
}

void ParserHelper::help() {
  std::cout << "\033[33m"
      "Only takes file path as input or when input argument is not "
      "provided user will be prompted to enter the data\n"
            << std::string(40, '+') <<
      "\033[032m"
      "\n\nTo load data from file"
      "\n$./klargest <path_to_file> [user will prompted to enter k]"
      "\n$./klargest <path_to_file> <value_for_k>\n"
      "\nTo enter data thru command line"
      "\n$./klargest"
      "\33[0m\n";
}
