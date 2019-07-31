
#pragma once
#ifndef KLARGEST_H
#define KLARGEST_H

#include <algorithm>
#include <utility>
#include <numeric>
#include <iterator>

#include <klargest/contants.hpp>
#include <klargest/parser_helper.hpp>


class KLargest {

 private:
  VectorPairs pairs;
   
 public:
  KLargest(const VectorPairs);
  VectorPairs getKLargest(const int);
  void print(const VectorPairs);  
};

#endif /* KLARGEST_H */
