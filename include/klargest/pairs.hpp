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
};

template<typename T, typename U>
std::ostream& operator<<(std::ostream& os, const Pair<T, U> &dpair) {
    os << "Id: " << dpair.identifier << " value: " << dpair.value << std::endl;
    return os;
}


// using MyPair = Pair<std::string, int>;
using DPair = Pair<std::string, int>;
using VectorPairs = std::vector<DPair>;
using VectorInt = std::vector<int>;

#endif /* PAIRS_H */
