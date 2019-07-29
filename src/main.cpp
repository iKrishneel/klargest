
#include <klargest/parser_helper.hpp>

int main(int argc, const char *argv[]) {

  // input argument is only the file path
  ParserHelper *parser = new ParserHelper(argc, argv);
  
  if (argc > 2) {
    parser->help();
    std::exit(EXIT_FAILURE);
  }
  
  std::vector<MyPair> pairs;
  
  // check that input is file
  if (argc == 1) {
    // request_data_input(pairs);
    parser->readDataFromCL(pairs);
    
  } else if (argc == 2) {
    if (!parser->readDataFromFile(pairs, argv[1])) {
      std::cout << "\033[031mInvalid filepath: "<< argv[1] << " \033[0m\n";
      parser->help();
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

  delete parser;
  return 0;
}
