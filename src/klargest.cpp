
#include <klargest/klargest.hpp>

KLargest::KLargest(const VectorPairs vector_pairs) {
  this->pairs = vector_pairs;
}

/*
 * function to get the k-largest element
 * the idea is to use Median-of-Medians algorithm to find the k-th
 * largest element and then loop over the vector to find all elements
 * in the vector greater then k-th largest
 * @param k: the kth largest element to search
 */
VectorPairs KLargest::getKLargest(const int k) {

  // check that given k is within the range
  if (k < 1 || k > static_cast<int>(this->pairs.size())) {
    std::cout << "\033[031mInvalid value for k\033[0m"  << "\n";
    return VectorPairs();
  }

  // make a copy
  VectorPairs vector_pairs = this->pairs;
  auto start = vector_pairs.begin();
  auto end = vector_pairs.begin() + k;

  // comparator lambda for the custom data type
  auto comparator = [](DPair &a, DPair &b) {
                      return a.value > b.value;
                    };
  
  // use median-of-medians algorithm to find the k-largest value
  std::nth_element(start, end, vector_pairs.end(), comparator);
  
  // the kth largest value is at position k-1 since k is between [1-n]
  DPair kth_largest = vector_pairs.at(k-1);

  // iterate over the array and find all elements greater than
  // kth_largerst
  VectorPairs k_largest_pairs;
  for (auto it = vector_pairs.begin(); it != vector_pairs.end(); it++) {
    if (it->value >= kth_largest.value) {
      k_largest_pairs.push_back(*it);
    }
  }
  return k_largest_pairs;
}

/*
 * printer function
 */
void KLargest::print(const VectorPairs vector_pairs) {
  for (auto it = vector_pairs.begin(); it != vector_pairs.end(); it++) {
    std::cout <<*it;
  }
}
