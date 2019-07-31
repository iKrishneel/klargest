
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
  int k_value;

 protected:
  
   
 public:
  KLargest(const VectorPairs);
  VectorPairs getKLargest(const int k);
    
};


#endif /* KLARGEST_H */
