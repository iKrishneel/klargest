
#pragma once
#ifndef KLARGEST_H
#define KLARGEST_H

#include <algorithm>
#include <utility>
#include <numeric>
#include <iterator>

#include <klargest/contants.hpp>
#include <klargest/parser_helper.hpp>

struct IndexMap {
  int actual_index;
  int sorted_index;
  
  IndexMap(int aindex, int sindex) {
    actual_index = aindex;
    sorted_index = sindex;
  }
};


#define SUB_SIZE 5

using IndicesMap = std::vector<IndexMap>;

class KLargest {

 private:
  VectorPairs pairs;
  int k_value;

 protected:
  DPair getMedian(VectorPairs &);
  DPair medianHelper(VectorPairs &, const int, const int, const int = -1);
  std::vector<int> sortIndexes(const std::vector<DPair> &v);
   
 public:
  KLargest(const VectorPairs, const int);
  int getKLargest(VectorPairs, int, int, int);

  void findKLargest();
  int partition(VectorPairs &, const int, const int, const int);
  
};


#endif /* KLARGEST_H */
