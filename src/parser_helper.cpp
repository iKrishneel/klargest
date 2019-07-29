
#include <klargest/parser_helper.hpp>

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

