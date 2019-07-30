
#include <klargest/parser_helper.hpp>
#include <KLargest/KLargest.hpp>

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
  std::cout << "\n";
  
  KLargest *k_largest = new KLargest(pairs, 2);
  
  
  delete parser;
  delete k_largest;
  return 0;
}
