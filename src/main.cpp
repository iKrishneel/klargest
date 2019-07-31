
#include <klargest/parser_helper.hpp>
#include <klargest/klargest.hpp>

int main(int argc, const char *argv[]) {

  ParserHelper *parser = new ParserHelper(argc, argv);
  VectorPairs pairs = parser->getPairs();
  
  // do not proceed if input is empty
  if (pairs.empty()) {
    std::cout << "No input to process\n";
    return EXIT_SUCCESS;
  }
  
  for (auto it = pairs.begin(); it != pairs.end(); it++) {
     std::cout << *it;
  }
  std::cout << "\n";
  
  KLargest *k_largest = new KLargest(pairs);
  VectorPairs k_largest_pairs = k_largest->getKLargest(3);

  k_largest->print(k_largest_pairs);

  // book keeping
  delete parser;
  delete k_largest;
  return EXIT_SUCCESS;
}
