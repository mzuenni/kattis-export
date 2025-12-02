#include <iostream>
#include <string>

int main() {
  std::string action;
  std::cin >> action;

  if (action == "send") {
    int length;
    std::cin >> length;
    std::string email;
    std::cin >> email;

    for (int i = 0; i < 5; ++i) {
      std::string bits(length + 3, '.');
      for (int j = 0; j < length; ++j) {
        bits[j] = '0' + ((email[j] - 'a') >> i & 1);
      }
      for (int j = 0; j < 3; ++j) {
        bits[bits.size() - 1 - j] = '0' + (i >> j & 1);
      }
      std::cout << bits << std::endl;
    }
  } else if (action == "receive") {
    std::string email;

    for (int i = 0; i < 5; ++i) {
      std::string bits;
      std::cin >> bits;
      email.resize(bits.size() - 3, 'a');

      int k = 0;
      for (int j = 0; j < 3; ++j) {
        k |= (bits[bits.size() - 1 - j] - '0') << j;
      }

      for (int j = 0; j < email.size(); ++j) {
        email[j] += (bits[j] - '0') << k;
      }
    }

    std::cout << email << std::endl;
  } else {}  // This should never happen.

  return 0;
}
