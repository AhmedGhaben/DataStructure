#include <iostream>

void countingSort(long long A[], int n, long long exp) {
  const int k = 9;
  long long* B = new long long[n];
  int C[k + 1] = {0};

  for (int j = 0; j < n; ++j) {
    int digit = (A[j] / exp) % 10;
    C[digit]++;
  }
  
  for (int i = 1; i <= k; ++i) {
    C[i] += C[i - 1];
  }
  
  for (int j = n - 1; j >= 0; --j) {
    int digit = (A[j] / exp) % 10;
    B[C[digit] - 1] = A[j];
    C[digit]--;
  }
  
  for (int i = 0; i < n; ++i) {
    A[i] = B[i];
  }
  
  delete[] B;
}

long long findMax(long long arr[], int n) {
  long long max = arr[0];
  for (int i = 1; i < n; ++i) {
    if (arr[i] > max) max = arr[i];
  }
  return max;
}

void radixSort(long long arr[], int n) {
  long long max = findMax(arr, n);
  for (long long exp = 1; max / exp > 0; ) {
    countingSort(arr, n, exp);
    // Prevent overflow
    if (exp > 1000000000000000000LL) break;
    exp *= 10;
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  
  int n;
  std::cin >> n;
  if (n <= 0) {
    return 0;
  }
  long long* A = new long long[n];
  for (int i = 0; i < n; ++i) {
    if (!(std::cin >> A[i])) {
      delete[] A;
      return 1;
    }
  }
  
  radixSort(A, n);
  
  for (int i = 0; i < n; ++i) {
    std::cout << A[i] << '\n';
  }
  
  delete[] A;
  return 0;
}