#pragma once
#ifndef PAIRS_H
#define PAIRS_H

template<typename T, typename U>
struct Pair {
  T identifier;
  U value;
  
  Pair(T id, U val) {
    identifier = id;
    value = val;
  }

  std::ostream& operator<<(std::ostream& os) {
    // os << "Id: " << identifier << " value: " << value << std::endl;
    return os;
  }
};

using MyPair = Pair<std::string, int>;
using DPair = Pair<std::string, int>;
using VectorPairs = std::vector<DPair>;
#endif /* PAIRS_H */
