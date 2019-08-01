// Copyright (C) 2019 by Krishneel

#pragma once
#ifndef PAIRS_H
#define PAIRS_H

/*
  data structure for the holding identifier and its value
 */
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

using DPair = Pair<std::string, int>;
using VectorPairs = std::vector<DPair>;

#endif /* PAIRS_H */
