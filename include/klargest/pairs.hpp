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


#endif /* PAIRS_H */
