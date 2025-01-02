#ifndef UTIL
#define UTIL

#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <string>
#include <time.h>
#include <type_traits>
#include <vector>

namespace util {
enum RandomType { smallLetter, capitalLetter, digit, specialCharacter, mix };
void urand() { srand(time(0)); }

template <typename T>
typename std::enable_if<
    std::is_arithmetic<T>::value && !std::is_same<T, char>::value, T>::type
randomNumber(T min, T max) {
  return rand() % (max - min + 1) + min;
}

char randomChar(const RandomType type) {
  char c;
  switch (type) {
  case RandomType::smallLetter:
    c = randomNumber(97, 122);
    break;
  case RandomType::capitalLetter:
    c = randomNumber(65, 90);
    break;
  case RandomType::digit:
    c = randomNumber(48, 57);
    break;
  case RandomType::specialCharacter:
    c = randomNumber(33, 47);
    break;
  case RandomType::mix:
    c = randomChar(RandomType(randomNumber(0, 3)));
    break;
  }
  return c;
}

bool isSpecialCharacter(char c) { return 33 <= c && c <= 47; }

std::string randomWord(const RandomType type, int wordLength,
                       bool withoutSpecialCharacters = true,
                       bool withoutDigits = false) {
  std::string word = "";
  for (int i = 1; i <= wordLength; i++) {
    char c = randomChar(type);

    // removing special characters
    if (withoutSpecialCharacters) {
      if (isSpecialCharacter(c)) {
        i -= 1;
        continue;
      }
    }

    // removing digits
    if (withoutDigits) {
      if (isdigit(c)) {
        i -= 1;
        continue;
      }
    }

    word += c;
  }
  return word;
}

// This method only return's key without special characters and number
std::string randomKey(short terms = 4, short termLength = 4,
                      bool useSmallLetters = false) {

  std::string key = "";

  for (short i = 1; i <= terms; i++) {
    std::string word = "";
    if (useSmallLetters) {
      word = randomWord(RandomType::mix, termLength, true, true);
    } else {
      word = randomWord(RandomType::capitalLetter, termLength, true, true);
    }

    key += word + '-';
  }

  // Removing last '-'
  key.pop_back();

  return key;
}

template <std::size_t N>
std::array<std::string, N> randomKeys(short terms = 4, short termLength = 4,
                                      bool useSmallLetters = false) {
  std::array<std::string, N> keys = {};
  for (int i = 1; i <= numberOfKeys; i++) {
    keys[i - 1] = randomKey(terms, termLength, useSmallLetters);
  }
  return keys;
}

template <typename T> void print(const std::vector<T> &v) {
  for (const T &str : v) {
    std::cout << str << '\n';
  }
}

template <typename T> void swap(T &a, T &b) {
  T c = a;
  a = b;
  b = c;
}

std::string tabs(short tabs) {
  std::string str = "";

  for (short i = 1; i <= tabs; i++) {
    str += '\t';
  }

  return str;
}

template <typename T>
typename std::enable_if<
    std::is_arithmetic<T>::value && !std::is_same<T, char>::value, void>::type
fillWithRandomNumbers(std::vector<T> &v, T min, T max) {
  for (T &i : v) {
    i = randomNumber<T>(min, max);
  }
}

template <typename T>
typename std::enable_if<
    std::is_arithmetic<T>::value && !std::is_same<T, char>::value, void>::type
fillWithRandomNumbers(T arr[], T arrayLength, T min, T max) {
  for (int i = 0; i < arrayLength; i++) {
    arr[i] = randomNumber(min, max);
  }
}

void fillWithRandomStrings(std::vector<std::string> &v, RandomType type,
                           int wordLength, bool withoutSpecialCharacters = true,
                           bool withoutDigits = false) {
  for (std::string &str : v) {
    str = randomWord(type, wordLength, withoutSpecialCharacters, withoutDigits);
  }
}

void fillWithRandomStrings(std::string arr[], int arrayLength, RandomType type,
                           int wordLength, bool withoutSpecialCharacters = true,
                           bool withoutDigits = false) {
  for (int i = 0; i < arrayLength; i++) {
    arr[i] =
        randomWord(type, wordLength, withoutSpecialCharacters, withoutDigits);
  }
}

std::string encrypt(const std::string &str, short key) {
  std::string encryptedText = "";
  for (const char c : str) {
    encryptedText += c + key;
  }
  return encryptedText;
}

std::string decrypt(const std::string &str, short key) {
  std::string decryptedText = "";
  for (const char c : str) {
    decryptedText += c - key;
  }
  return decryptedText;
}

template <typename T> void shuffle(std::vector<int> &v) {
  int size = v.size();
  for (int i = 0; i < size; i++) {
    swap<T>(v[randomNumber(1, size) - 1], v[randomNumber(1, size) - 1]);
  }
}

std::string repeat(const std::string &str, unsigned times) {
  std::string result = str;
  for (unsigned i = 1; i < times; i++) {
    result += str;
  }
  return result;
}

std::string repeat(char c, unsigned times) {
  return repeat(std::to_string(c), times);
}
}; // namespace util

#endif