
#include <klargest/parser_helper.hpp>
#include <klargest/klargest.hpp>

// temp hardcored
std::string default_folder = "../tests/";
std::string prefix = "test_";
std::string default_name = "_result_k";

void writeToTextfile(const VectorPairs vector_pair, const int k,
                     const int size) {
  // todo: make the directory if not exit
  std::string dlen = std::to_string(size);
  std::string n = std::string(8-dlen.size(), '0') + dlen;
  std::string filename = default_folder + prefix + n + default_name +
      std::to_string(k) + ".txt";

  std::ofstream outfile(filename);
  for (auto it = vector_pair.begin(); it != vector_pair.end(); it++) {
    outfile << it->identifier << " " << it->value << "\n";
  }
  outfile.close();
}

int main(int argc, const char *argv[]) {

  ParserHelper *parser = new ParserHelper(argc, argv);
  VectorPairs pairs = parser->getPairs();
  
  // do not proceed if input is empty
  if (pairs.empty()) {
    std::cout << "No input to process\n";
    return EXIT_SUCCESS;
  }

  bool is_debug = false;
  if (is_debug) {
    for (auto it = pairs.begin(); it != pairs.end(); it++) {
      std::cout << *it;
    }
    std::cout << "\n";
  }

  int k = parser->getK();
  KLargest *k_largest = new KLargest(pairs);
  VectorPairs k_largest_pairs;
  do {
     k = parser->getK();
     std::cout << "\nResults for K=" << k << "\n";
     k_largest_pairs = k_largest->getKLargest(k);
     k_largest->print(k_largest_pairs);

     // write to file
     writeToTextfile(k_largest_pairs, k, pairs.size());
     
     std::cout << "\n\nEnter K for another test or C(c) to end."  << "\n";
     std::cout << std::string(CMD_COUNT, '-') << std::endl;
  } while (parser->getKFromCL());
  
  // book keeping
  delete parser;
  delete k_largest;
  return EXIT_SUCCESS;
}
