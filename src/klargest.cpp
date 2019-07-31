
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
DPair KLargest::getMedian(VectorPairs &sub_pairs) {

  /*
  for (int i = 0; i < sub_pairs.size(); i++) {
    std::cout << sub_pairs[i].value << " " <<
        sub_pairs[sorted_indices[i]].value << " " <<
        sorted_indices[i] << "\n";
  }
  std::cout << "\n --- " << sub_pairs.size() << "\n";
  */

  auto comparator = [](DPair &a, DPair &b ) {
                      if (a.value < b.value) {
                        int t = a.index;
                        a.index = b.index;
                        b.index = t;
                        return true;
                      }
                      return a.value < b.value;
                    };
  std::sort(sub_pairs.begin(), sub_pairs.end(), comparator);

  int mid_point = static_cast<int>(sub_pairs.size() / 2);
  DPair dp = sub_pairs[mid_point];
  return dp;
}


DPair KLargest::medianHelper(VectorPairs &vectorPairs, const int left,
                             const int i, const int j) {
  int index = left + i * SUB_SIZE;
  auto start = vectorPairs.begin() + index;
  auto end = vectorPairs.begin() + index + (j == -1 ? SUB_SIZE : j);
  auto v_pairs = VectorPairs(start, end);
  auto median = getMedian(v_pairs);
  std::copy(v_pairs.begin(), v_pairs.end(), start);
  return median;
}

// Returns k'th smallest element in vectorPairs[left..right] in worst case
// linear time. ASSUMPTION: ALL ELEMENTS IN ARR[] ARE DISTINCT
int KLargest::getKLargest(VectorPairs vectorPairs, int left, int right, int k) {
  // If k is smaller than number of elements in array
  
  if (k > 0 && k <= right - left + 1) {

    int n = right-left+1;

    std::cout << "\n----------------------\nN: " << n
              << " " << left << " " << right << " " << k << "\n";

    VectorPairs medians;
    int i = 0;
    for (; i < n/5; i++) {
      auto mid = medianHelper(vectorPairs, left, i);
      medians.push_back(mid);
    }
    
    if (i*5 < n) {
      auto mid = medianHelper(vectorPairs, left, i, n%5);
      medians.push_back(mid);
      i++;
    }

    std::cout << "Value"  << "\n";
    for (int i = 0; i < vectorPairs.size(); i++) {
      std::cout << vectorPairs[i].value << " " << vectorPairs[i].index  << "\n";
    }
    

    
    std::cout << "\nMedians: \n";
    for (int j = 0; j < medians.size(); j++) {
      std::cout << medians[j].value << " " << medians[j].index << "\n";

    }
    
    std::cout << "i: " << i << " " << medians.size() << "\n";
    
    // Find median of all medians using recursive call.
    // If median[] has only one element, then no need of recursive call
    int mom_index = i == 1 ? i-1:
        getKLargest(medians, 0, i-1, i/2);

    // search with id
    int count = 0;
    for (auto it = vectorPairs.begin(); it != vectorPairs.end(); it++) {
      if (it->index == medians[mom_index].index) {
        mom_index = count;
        break;
      }
      count++;
    }


    std::cout << "i: " << i << " " << medians.size() << "\n";
    std::cout << medians[mom_index].value << "\n";
    std::cout << "med: "  << mom_index << "\n";
    
    // Partition the array around a random element and
    // get position of pivot_index element in sorted array
    int position = partition(vectorPairs, left, right, mom_index);

    std::cout << "Position:" << position  << "\n";
    
    
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
  return INT_MAX;
}

void swap(VectorPairs &vectorPairs, int a, int b) {
  std::swap(vectorPairs[a], vectorPairs[b]);
  int temp = vectorPairs[a].index;
  vectorPairs[a].index = vectorPairs[b].index;
  vectorPairs[b].index = temp;
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

  std::cout << vectorPairs.size();
  
  std::cout << "\n\tPart: " << left << " " << right << " " <<
      pivot_index << " " << vectorPairs[pivot_index].value << "\n";
  
  
  swap(vectorPairs, pivot_index, right);
  
  /*
  std::cout << "AF: " << vectorPairs[pivot_index].index << " "
            << vectorPairs[pivot_index].value << " "
            << vectorPairs[right].index << " "
            << vectorPairs[right].value << "\n";
  std::exit(1);
  */
  
  // std::swap(vectorPairs[pivot_index], vectorPairs[right]);

  int i = left;
  for (int j = left; j < right; j++) {
    if (vectorPairs[j].value < vectorPairs[pivot_index].value) {
      // std::swap(vectorPairs[i++], vectorPairs[j]);
      swap(vectorPairs, i++, j);
    }
  }

  // std::swap(vectorPairs[i], vectorPairs[right]);
  swap(vectorPairs, i, right);
  std::cout << "I: " << i  << "\n";
  return i;
}
