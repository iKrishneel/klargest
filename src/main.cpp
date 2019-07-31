
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
  int k = parser->getK();

  std::cout << "\n";
  std::cout << "K is: " << k << "\n";

  std::string input;
  KLargest *k_largest = new KLargest(pairs);
  VectorPairs k_largest_pairs;
  
  do {
     k_largest_pairs = k_largest->getKLargest(parser->getK());
     k_largest->print(k_largest_pairs);
     std::cout << "\n\nEnter K for another test c to end."  << "\n";
  } while (parser->getKFromCL());
  

  // book keeping
  delete parser;
  delete k_largest;
  return EXIT_SUCCESS;
}
