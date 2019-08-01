// Copyright (C) 2019 by Krishneel

#pragma once
#ifndef KLARGEST_H
#define KLARGEST_H

#include <queue>
#include <klargest/contants.hpp>
#include <klargest/parser_helper.hpp>

class KLargest {

 private:
  VectorPairs pairs_;

 protected:
  VectorPairs getKLargestMHeap(const int);
  VectorPairs getKLargestMoMedians(const int);
  
 public:
  KLargest(const VectorPairs);
  VectorPairs getKLargest(const int);
  void print(const VectorPairs);
  
};

#endif /* KLARGEST_H */
