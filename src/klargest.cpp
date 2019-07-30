
#include <klargest/klargest.hpp>

KLargest::KLargest(const VectorPairs vectorPairs, const int k) : k_value(k) {
  this->pairs = vectorPairs;
  this->findKLargest();
}

void KLargest::findKLargest() {
  int size = this->pairs.size();
  getKLargest(this->pairs, 0, size-1, this->k_value);
}

std::vector<int> KLargest::sortIndexes(const std::vector<DPair> &v) {
  
  // initialize original index locations
  std::vector<int> indices(v.size());
  std::iota(indices.begin(), indices.end(), 0);
  
  // sort indexes based on comparing values in v
  std::sort(indices.begin(), indices.end(),
            [&v](int i, int j) {
              return v[i].value < v[j].value;
            });
  return indices;
}

/*
 * function to sort the vector using comparator function
 */
IndexMap KLargest::getMedian(VectorPairs sub_pairs, const int count) {

  auto sorted_indices = sortIndexes(sub_pairs);

  /*
  for (int i = 0; i < sub_pairs.size(); i++) {
    std::cout << sub_pairs[i].value << " " <<
        sub_pairs[sorted_indices[i]].value << " " <<
        sorted_indices[i] << "\n";
  }
  std::cout << "\n --- " << sub_pairs.size() << "\n";
  /*
  auto comparator = [](DPair a, DPair b ) {
                      return a.value < b.value;
                    };
  std::sort(sub_pairs.begin(), sub_pairs.end(), comparator);
  */
  
  int mid_point = static_cast<int>(sub_pairs.size() / 2);
  // return sub_pairs[mid_point];

  int index = sorted_indices[mid_point];
  return IndexMap(count + mid_point, index + count);
}

// Returns k'th smallest element in vectorPairs[left..right] in worst case
// linear time. ASSUMPTION: ALL ELEMENTS IN ARR[] ARE DISTINCT
int KLargest::getKLargest(VectorPairs vectorPairs, int left, int right, int k) {
  // If k is smaller than number of elements in array
  
  if (k > 0 && k <= right - left + 1) {

    auto get_mid = [this, vectorPairs, left](int i, int j = -1) {
                     int index = left + i * SUB_SIZE;
                     auto start = vectorPairs.begin() + index;
                     auto end = vectorPairs.begin() + index +
                         (j == -1 ? SUB_SIZE : j);
                     return getMedian(VectorPairs(start, end), index);
                   };

    int n = right-left+1;

    std::cout << "\nN: " << n << " " << left
              << " " << right << " " << k << "\n";
    
    IndicesMap medianIndices;
    int i = 0;
    for (; i < n/5; i++) {
      auto mid = get_mid(i);
      medianIndices.push_back(mid);
    }
    
    if (i*5 < n) {
      auto mid = get_mid(i, n%5);
      medianIndices.push_back(mid);
      i++;
    }

    // std::cout << "Mid: \n";
    VectorPairs medians;
    for (int j = 0; j < medianIndices.size(); j++) {
      int idx = medianIndices[j].sorted_index;
      medians.push_back(vectorPairs.at(idx));

      std::cout << medianIndices[j].actual_index << " "
                << medianIndices[j].sorted_index << " "
                << medians[j].value << "\n";

    }
    
    std::cout << "i: " << i << " " << medians.size() << "\n";
    
    // Find median of all medians using recursive call.
    // If median[] has only one element, then no need of recursive call
    int mom_index = i == 1 ? i-1: getKLargest(medians, 0, i-1, i/2);
    
    std::cout << "med: "  << mom_index << "\n";



    std::cout << "Medians"  << "\n";
    for (int j = 0; j < medians.size(); j++) {
      std::cout  << medians[j].value << ", ";
    }
    std::cout << "\n";





    
    // Partition the array around a random element and
    // get position of pivot_index element in sorted array
    int position = partition(vectorPairs, left, right, mom_index);

    std::cout << "Part:" << position  << "\n";
    
    // If position is same as k
    if (position-left == k-1) {
      // return vectorPairs[position].value;
      return position;
    }

    // If position is more, recur for left
    if (position-left > k-1) {
      return getKLargest(vectorPairs, left, position-1, k);
    }
    
    // Else recur for right subarray
    return getKLargest(vectorPairs, position+1, right, k-position+left-1);
  }
  
  // If k is more than number of elements in array
  return -1;
}

// It searches for x in vectorPairs[l..r], and partitions the array
// around x.
int KLargest::partition(VectorPairs &vectorPairs, const int left,
                        const int right, const int pivot_index) {
  // Search for x in vectorPairs[l..r] and move it to end
  /*
  int i;
  for (i=left; i < right; i++) {
    if (vectorPairs[i].value == pivot_index) {
      break;
    }
  }
  */

  std::cout << "\tPart: " << left << " " << right << " " << pivot_index << "\n";
  
  
  std::swap(vectorPairs[pivot_index], vectorPairs[right]);

  int i = left;
  for (int j = left; j <= right - 1; j++) {
    if (vectorPairs[j].value <= pivot_index) {
      std::swap(vectorPairs[i++], vectorPairs[j]);
    }
  }

  std::swap(vectorPairs[i], vectorPairs[right]);

  return i;
}
