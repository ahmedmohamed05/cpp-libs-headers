#ifndef MSTRING
#define MSTRING

#include <iostream>
#include <string>
#include <vector>

class Mstring {
private:
  std::string _value;

public:
  Mstring() { _value = ""; }
  Mstring(std::string value) { _value = value; };
  Mstring(const char *str) { _value = str; }

  Mstring &operator=(const char *str) {
    _value = str;
    return *this;
  }

  std::string getValue() const { return _value; }
  void setValue(std::string value) { _value = value; }

  void print() const { std::cout << _value << std::endl; }

  void clear() { _value = ""; }

  // Split String And Returns vector of strings
  static std::vector<std::string> split(std::string str,
                                        const std::string &delimiter) {
    std::vector<std::string> vString;
    std::size_t delimPosition;

    while ((delimPosition = str.find(delimiter)) != str.npos) {
      vString.push_back(str.substr(0, delimPosition));
      str.erase(0, delimPosition + delimiter.length());
    }

    // Pushing last word in string
    if (str != "")
      vString.push_back(str);
    return vString;
  }
  std::vector<std::string> split(const std::string &delimiter) {
    return split(_value, delimiter);
  }

  // Print first letter from each word in string
  static void printFirstLetters(const std::string &str) {
    for (const std::string &word : split(str, " ")) {
      std::cout << word[0] << '\n';
    }
  }
  void printFirstLetters() { printFirstLetters(_value); }

  // Print each word in std::string
  static void printWords(std::string str, const std::string &delimiter) {
    for (std::string &word : split(str, delimiter)) {
      std::cout << word << '\n';
    }
  }
  void printWords(const std::string &delimiter) {
    printWords(_value, delimiter);
  }

  static void capitalize(std::string &str) {
    bool isFirstLetter = true;
    for (char &letter : str) {
      if (letter != ' ' && isFirstLetter) {
        letter = char(toupper(letter));
      }
      isFirstLetter = (letter == ' ');
    }
  }
  void capitalize() { capitalize(_value); }

  // Make first letter of each word a small letter
  static void smallLetters(std::string &str) {
    bool isFirstLetter = true;
    for (char &letter : str) {
      if (letter != ' ' && isFirstLetter)
        letter = char(tolower(letter));
      isFirstLetter = (letter == ' ');
    }
  }
  void smallLetters() { smallLetters(_value); }

  // Convert the std::string to upper case
  static void toUpperCase(std::string &str) {
    for (char &letter : str) {
      letter = char(toupper(letter));
    }
  }
  void toUpperCase() { toUpperCase(_value); }

  // Convert the std::string to upper case
  static void toLowerCase(std::string &str) {
    for (char &letter : str) {
      letter = char(tolower(letter));
    }
  }
  void toLowerCase() { toLowerCase(_value); }

  // Invert std::string case
  static void invertCase(std::string &str) {
    for (char &letter : str) {
      letter = (islower(letter) ? toupper(letter) : tolower(letter));
    }
  }
  void invertCase() { invertCase(_value); }

  // Count small letters in setring
  static unsigned countSmallLetters(const std::string &str) {
    unsigned counter = 0;
    for (char letter : str) {
      if (islower(letter)) {
        counter++;
      }
    }
    return counter;
  }
  unsigned countSmallLetters() const { return countSmallLetters(_value); }

  // Count Capital letters in setring
  static unsigned countCapitalLetters(const std::string &str) {
    unsigned counter = 0;
    for (char letter : str) {
      if (isupper(letter)) {
        counter++;
      }
    }
    return counter;
  }
  unsigned countCapitalLetters() const { return countCapitalLetters(_value); }

  // Count a specific letter in std::string
  static unsigned countSpecificLetter(std::string str, char letterToCount,
                                      const bool matchingCase = true) {
    unsigned counter = 0;

    if (!matchingCase) {
      // Convert everything to lowercase
      letterToCount = tolower(letterToCount);
      Mstring::toLowerCase(str);
    }

    for (const char &letter : str) {
      if (letter == letterToCount)
        counter++;
    }

    return counter;
  }

  unsigned countSpecificLetter(char letterToCount,
                               const bool matchingCase = true) const {
    return countSpecificLetter(_value, letterToCount, matchingCase);
  }

  // Check if the input letter is a vowel
  static bool isVowel(char letter) {
    letter = tolower(letter);
    return (letter == 'a' || letter == 'i' || letter == 'o' || letter == 'e' ||
            letter == 'u');
  }

  // count vowels in given std::string
  static unsigned countVowels(std::string str) {
    unsigned counter = 0;

    for (const char &letter : str) {
      if (isVowel(letter)) {
        counter++;
      }
    }

    return counter;
  }

  unsigned countVowels() const { return countVowels(_value); }

  // Print all vowels in given std::string
  static void printVowels(std::string str) {
    for (const char &letter : str) {
      if (isVowel(letter)) {
        std::cout << letter << " ";
      }
    }
    std::cout << "\n";
  }
  void printVowels() { printVowels(_value); }

  // Cut all the spaces on the left
  static void trimLeft(std::string &str) {
    for (std::size_t i = 0; i < str.length(); i++) {
      if (str[i] != ' ') {
        str.erase(0, i);
        break;
      };
    }
  }
  void trimLeft() { trimLeft(_value); }

  // Cut all the spaces on the Right
  static void trimRight(std::string &str) {
    for (std::size_t i = str.length() - 1; i >= 0; i--) {
      if (str[i] != ' ') {
        str.erase(i + 1, str.length());
        break;
      };
    }
  }
  void trimRight() { trimRight(_value); }

  // Cut all the spaces in the std::string
  static void trim(std::string &str) {
    trimRight(str);
    trimLeft(str);
  }
  void trim() { trim(_value); }

  // Join std::string from std::vector
  static std::string join(const std::vector<std::string> &vString,
                          const std::string &separator = " ") {
    std::string str = "";
    std::size_t size = vString.size();
    for (std::size_t i = 0; i < size - 1; i++)
      str += vString[i] + separator;
    return str + vString[size - 1];
  }

  // Join std::string from array
  static std::string join(const std::string aString[], const unsigned length,
                          const std::string &separator) {
    std::string str = "";
    for (std::size_t i = 0; i < length - 1; i++)
      str += aString[i] + separator;
    return str + aString[length - 1];
  }

  // Setting the value from the given std::vector
  void from(const std::vector<std::string> &vString,
            const std::string &separator = " ") {
    _value = join(vString, separator);
  }

  // Setting the value from the given array
  void from(const std::string aString[], const unsigned length,
            const std::string &separator) {
    _value = join(aString, length, separator);
  }

  // Reverse word in string start from end to begining
  static std::string reverse(const std::string &str,
                             const std::string &separator) {
    std::string reversedStr = "";
    std::vector<std::string> vString = split(str, separator);
    for (std::size_t i = vString.size() - 1; i >= 0; i--) {
      reversedStr += vString[i] + separator;
    }

    // Removing last separator added in the begining
    return reversedStr.substr(0, reversedStr.length() - separator.length());
  }

  void reverse(const std::string &separator) {
    _value = reverse(_value, separator);
  }

  // Replace words in string
  static void replace(std::string &str, std::string wordToReplace,
                      std::string newWord, bool machingCase) {

    // Convert everything to lowercase
    if (!machingCase) {
      toLowerCase(str);
      toLowerCase(wordToReplace);
    }

    std::size_t position;
    if ((position = str.find(wordToReplace)) != str.npos) {
      str.replace(position, wordToReplace.length(), newWord);
    }
  }

  void replace(const std::string &wordToReplace, const std::string &newWord,
               bool machingCase) {
    replace(_value, wordToReplace, newWord, machingCase);
  }

  // TODO: One punctuation still in
  // Remove Punctuations Function
  static void removePunctuations(std::string &str) {
    for (std::size_t i = 0; i < str.length(); i++) {
      if (ispunct(str[i])) {
        str.erase(i, 1);
      }
    }
  }
  void removePunctuations() { removePunctuations(_value); }

  // Check if the string is a number
  static bool isNumber(std::string s) {
    for (const char &c : s) {
      if (!isdigit(c)) {
        return false;
      }
    }
    return true;
  }

  bool isNumber() const { return isNumber(_value); }

  int length() const { return _value.length(); }
};

std::ostream &operator<<(std::ostream &os, const Mstring &string) {
  os << string.getValue();
  return os;
}

#endif