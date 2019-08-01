
#include <klargest/klargest.hpp>

KLargest::KLargest(const VectorPairs vector_pairs) {
  this->pairs_ = vector_pairs;
}

/*
 * function to get the k-largest element
 * the idea is to use Median-of-Medians algorithm to find the k-th
 * largest element and then loop over the vector to find all elements
 * in the vector greater then k-th largest
 * @param k: the kth largest element to search
 */
VectorPairs KLargest::getKLargest(const int k) {

  int v_size = static_cast<int>(this->pairs_.size());
  
  // check that given k is within the range
  if (k < 1 || k > v_size) {
    std::cout << "\033[031mInvalid value for k\033[0m"  << "\n";
    return VectorPairs();
  }

  // case of k = n
  if (k == v_size) {
    return this->pairs_;
  }

  // return getKLargestMHeap(k);
  return getKLargestMoMedians(k);
}

VectorPairs KLargest::getKLargestMoMedians(const int k) {
  // make a copy
  auto vector_pairs = this->pairs_;
  auto start = vector_pairs.begin();
  auto end = vector_pairs.begin() + k-1;

  // comparator lambda for the custom data type
  auto comparator = [](const DPair &a, const DPair &b) {
                      return a.value > b.value;
                    };
  
  // use median-of-medians algorithm to find the k-largest value
  std::nth_element(start, end, vector_pairs.end(), comparator);
  
  // the kth largest value is at position k
  auto kth_largest = vector_pairs.at(k);
  std::cout << "k-th: "<< kth_largest << "\n";

  // iterate over the array and find all elements greater than
  // kth_largerst
  VectorPairs k_largest_pairs;
  for (auto it = vector_pairs.begin(); it != vector_pairs.end(); it++) {
    if (it->value > kth_largest.value) {
      k_largest_pairs.push_back(*it);
    }
  }
  return k_largest_pairs;
}

VectorPairs KLargest::getKLargestMHeap(const int k) {
  
  // comparator lambda for the custom data type
  auto comparator = [](const DPair &a, const DPair &b) {
                      return a.value < b.value;
                    };
  
  // create priority queue in O(n)
  std::priority_queue<DPair, VectorPairs, decltype(comparator)> p_queue(
      comparator, this->pairs_);

  // top is the max-value
  VectorPairs k_largest_pairs;
  int temp_k = k;
  while (temp_k-- > 0) {
    k_largest_pairs.push_back(p_queue.top());
    p_queue.pop();
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
