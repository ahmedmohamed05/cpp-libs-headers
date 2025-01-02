#ifndef INPUT
#define INPUT
#include <iostream>
#include <limits>
#include <string>
#include <type_traits> // For type traits like std::is_arithmetic
#include <vector>

namespace input {

template <typename T>
typename std::enable_if<
    std::is_arithmetic<T>::value && !std::is_same<T, char>::value, bool>::type
isNumberBetween(T number, T min, T max) {
  return (number >= min && number <= max);
}

// Function to read any type of numbers
template <typename T>
typename std::enable_if<
    std::is_arithmetic<T>::value && !std::is_same<T, char>::value, T>::type
readNumber(std::string msg, std::string errMsg = "Invalid number\n") {
  T n;

  // Fancy way to write while (true) {...}
  while (1) {
    std::cout << msg;
    std::cin >> n;

    // No error occur
    if (!std::cin.fail()) {
      return n;
    }

    std::cout << errMsg;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  return n;
}

template <typename T>
typename std::enable_if<
    std::is_arithmetic<T>::value && !std::is_same<T, char>::value, T>::type
readNumberInRange(T min, T max, std::string msg,
                  std::string outOfRangeMsg = "Number out of range\n",
                  std::string errMsg = "Enter a NUMBER\n") {
  T n;

  // Fancy way to write while (true) {...}
  while (1) {
    n = readNumber<T>(msg, errMsg);

    if (!input::isNumberBetween<T>(n, min, max)) {
      std::cout << outOfRangeMsg;
      continue;
    }

    return n;
  }

  return n;
}

std::string readString(std::string msg) {
  std::string line;
  std::cout << msg;
  std::getline(std::cin >> std::ws, line);
  return line;
}

char readChar(std::string msg) {
  char answer;
  std::cout << msg;
  std::cin >> answer;
  return answer;
}

template <typename T>
typename std::enable_if<
    std::is_arithmetic<T>::value && !std::is_same<T, char>::value, void>::type
readVector(std::vector<T> &vector, std::string msg, unsigned itemsToRead,
           std::string errMsg = "Error: Invalid Number\n") {

  for (unsigned i = 0; i <= itemsToRead - 1 && i < vector.size(); i++) {
    vector[i] = readNumber<T>(msg, errMsg);
  }
}

void readVector(std::vector<std::string> &vector, std::string msg,
                unsigned itemsToRead) {
  for (unsigned i = 0; i <= itemsToRead - 1 && i < vector.size(); i++) {
    vector[i] = readString(msg);
  }
}

void readVector(std::vector<char> &vector, std::string msg,
                unsigned itemsToRead) {
  for (unsigned i = 0; i <= itemsToRead - 1 && i < vector.size(); i++) {
    vector[i] = readChar(msg);
  }
}

} // namespace input

#endif