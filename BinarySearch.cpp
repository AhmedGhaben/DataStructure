#include <iostream>

bool BinarySearch(const int* begin, const int* end, int target) {
  while (begin < end) {
    const int* mid = begin + (end - begin) / 2;

    if (target == *mid) {
      return true;
    } else if (target < *mid) {
      end = mid;
    } else {
      begin = mid + 1;
    }
  }

  return false;
}

int
main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::size_t N;
  std::cin >> N;

  if (N == 0){
    std::cout << "Invalid array size! " << std::endl;
    return 1;
  }

  int* arr = new int[N];

  for (std::size_t i = 0; i < N; i++) {
    if (std::cin >> arr[i]){
      continue;
    }
    std::cout << "Invalid input!" << std::endl;
    delete[] arr;
    return 1;
  }

  std::size_t Q;
  if (!(std::cin >> Q) || Q ==0){
    std::cout << "Invalid The number of  operations must be positive!" << std::endl;
    delete[] arr;
    return 1;
  }

  for (std::size_t i = 0; i < Q; i++) {
    std::size_t begin, end;
    int target;
    if(!(std::cin >> begin >> end >> target) || end > N || end <= begin) {
      std::cout << "Invalid input!" << std::endl;
      delete[] arr;
      return 1;
    }

    if (BinarySearch(arr + begin, arr + end, target)) {
      std::cout << "YES" << std::endl;
    } else {
      std::cout << "NO" << std::endl;
    }
  }

  delete[] arr;
  return 0;
}
