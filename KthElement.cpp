#include <iostream>
//The median of medians approach didn't work 
//I suppose because of very large data so I took a different approach (median of three)

void Swap(int& a, int& b) {
  int temp = a;
  a = b;
  b = temp;
}

int Partition(int* arr, int left, int right, int pivot_index) {
  int pivot_value = arr[pivot_index];
  Swap(arr[pivot_index], arr[right]);
  int key = left;

  for (int i = left; i < right; ++i) {
    if (arr[i] < pivot_value) {
      Swap(arr[key], arr[i]);
      ++key;
    }
  }
  Swap(arr[key], arr[right]);
  return key;
}

int MedianOfThree(int* arr, int left, int right) {
    int mid = left + (right - left) / 2;

    if (arr[left] > arr[mid]) {
        Swap(arr[left], arr[mid]);
    }
    if (arr[left] > arr[right]) {
        Swap(arr[left], arr[right]);
    }
    if (arr[mid] > arr[right]) {
        Swap(arr[mid], arr[right]);
    }

    return mid;
}

int Quickselect(int* arr, int left, int right, int k) {
  while (left < right) {
    int pivot_index = MedianOfThree(arr, left, right);
    int pivot_value = arr[pivot_index];
    pivot_index = Partition(arr, left, right, pivot_index);

    if (k == pivot_index) {
      return arr[k];
    } else if (k < pivot_index) {
      right = pivot_index - 1;
    } else {
      left = pivot_index + 1;
    }
  }
  return arr[left];
}

int main() {
  std::size_t n;
  int k, a0, a1;

  if (!(std::cin >> n >> k >> a0 >> a1)) {
    std::cout << "Invalid input!" << std::endl;
    return 1;
  }

  if (n < 1 || k < 1 || k > n) {
    std::cout << "Invalid n or k!" << std::endl;
    return 1;
  }

  constexpr int mod = 10000000 + 4321;
  int* arr = new int[n];
  arr[0] = a0;
  arr[1] = a1;

  for (std::size_t i = 2; i < n; ++i) {
    arr[i] = (arr[i - 1] * 123LL + arr[i - 2] * 45LL) % mod;
  }

  int result = Quickselect(arr, 0, n - 1, k - 1);

  std::cout << result << std::endl;

  delete[] arr;
  return 0;
}
