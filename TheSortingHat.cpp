#include <iostream>
#include <stack>
#include <string>
#include <algorithm>

class EnchantedHat {
public:
  void Enqueue(int n) {
    in_stack.push(n);
    if (in_min_stack.empty() || n <= in_min_stack.top()) {
      in_min_stack.push(n);
    } else {
      in_min_stack.push(in_min_stack.top());
    }
    std::cout << "ok" << std::endl;
  }

  void Dequeue() {
    TransferInToOut();
    if (out_stack.empty()) {
      std::cout << "error" << std::endl;
      return;
    }
    std::cout << out_stack.top() << std::endl;
    out_stack.pop();
    out_min_stack.pop();
  }

  void Front() {
    TransferInToOut();
    if (out_stack.empty()) {
      std::cout << "error" << std::endl;
    } else {
      std::cout << out_stack.top() << std::endl;
    }
  }

  void Size() {
    std::cout << in_stack.size() + out_stack.size() << std::endl;
  }

  void Clear() {
    ClearStack(in_stack);
    ClearStack(out_stack);
    ClearStack(in_min_stack);
    ClearStack(out_min_stack);
    std::cout << "ok" << std::endl;
  }

  void Min() {
    if (in_min_stack.empty() && out_min_stack.empty()) {
      std::cout << "error" << std::endl;
    } else if (in_min_stack.empty()) {
      std::cout << out_min_stack.top() << std::endl;
    } else if (out_min_stack.empty()) {
      std::cout << in_min_stack.top() << std::endl;
    } else {
      std::cout << std::min(in_min_stack.top(), out_min_stack.top()) << std::endl;
    }
  }

private:
  std::stack<int> in_stack;
  std::stack<int> out_stack;
  std::stack<int> in_min_stack;
  std::stack<int> out_min_stack;

  void TransferInToOut() {
    if (out_stack.empty()) {
      while (!in_stack.empty()) {
        int element = in_stack.top();
        in_stack.pop();
        in_min_stack.pop();
        out_stack.push(element);
        if (out_min_stack.empty() || element <= out_min_stack.top()) {
          out_min_stack.push(element);
        } else {
          out_min_stack.push(out_min_stack.top());
        }
      }
    }
  }

  void ClearStack(std::stack<int>& s) {
    while (!s.empty()) s.pop();
  }
};

int main() {
  EnchantedHat hat;
  int m;
  std::cin >> m;

  for (int i = 0; i < m; ++i) {
    std::string command;
    std::cin >> command;

    if (command == "enqueue") {
      int n;
      std::cin >> n;
      hat.Enqueue(n);
    } else if (command == "dequeue") {
      hat.Dequeue();
    } else if (command == "front") {
      hat.Front();
    } else if (command == "size") {
      hat.Size();
    } else if (command == "clear") {
      hat.Clear();
    } else if (command == "min") {
      hat.Min();
    }
  }

  return 0;
}
