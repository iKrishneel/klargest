
#include <klargest/parser_helper.hpp>

int main(int argc, const char *argv[]) {

  ParserHelper *parser = new ParserHelper(argc, argv);
  VectorPairs pairs = parser->getPairs();
  
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
