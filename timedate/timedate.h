#ifndef DATE
#define DATE
#include "mstring.h"
#include <array>
#include <ctime>
#include <iostream>
#include <string>

// Default format is DD/MM/YYYY/HH/MM/SS
class TimeDate {
private:
  short _year, _month, _day, _hour, _minute, _second;
  std::string _separator;

public:
  // ************************************************************
  // *********************** Constructors ***********************
  // ************************************************************
  TimeDate() { *this = getTodayTimeDate(); }

  // Date format is DD/MM/YYYY/HH/MM/SS, if "/" is your separator
  TimeDate(const std::string &date, std::string separator = "/") {
    setTimeDate(date, separator);
    if (!isValidTimeDate(_day, _month, _year, _hour, _minute, _second)) {
      *this = getTodayTimeDate();
    }
  }

  TimeDate(short day, short month, short year, short hour, short minute,
           short second, std::string separator = "/") {
    _day = day;
    _month = month;
    _year = year;
    _hour = hour;
    _minute = minute;
    _second = second;
    if (separator.empty())
      separator = "/";
    _separator = separator;
  }

  // ***********************************************************
  // *********************** Day Methods ***********************
  // ***********************************************************

  // returns false if newDay is invalid
  bool setDay(short newDay, short month, short year) {
    if (!isValidDay(newDay, month, year))
      return false;

    _day = newDay;
    return true;
  }

  // This setter use's the current month and year to set the day
  bool setDay(short newDay) {
    if (!isValidDay(newDay, _month, _year))
      return false;

    _day = newDay;
    return true;
  }

  short getDay() const { return _day; }

  short getDayIndex() const { return _day - 1; }

  // Returns -1 if invalid input
  static short getDayOrderInWeek(short day, short month, short year) {
    if (!isValidDate(day, month, year))
      return -1;

    short a = (14 - month) / 12;
    short y = year - a;
    short m = month + 12 * a - 2;
    short dayIndex = (day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12) % 7;

    return dayIndex;
  }
  short getDayOrderInWeek() const {
    return getDayOrderInWeek(_day, _month, _year);
  }

  // Return Sunday if not found or invalid input
  static std::string getDayFullName(short day, short month, short year) {
    short dayOrder = getDayOrderInWeek(day, month, year);
    if (dayOrder == -1)
      return "Sunday";
    const auto &arr = getDaysFullNames();
    return arr[dayOrder];
  }
  std::string getDayFullName() const {
    return getDayFullName(_day, _month, _year);
  }

  // Return Sun if not found or invalid input
  static std::string getDayShortName(short day, short month, short year) {
    short dayOrder = getDayOrderInWeek(day, month, year);
    if (dayOrder == -1)
      return "Sun";
    const auto &arr = getDaysShortNames();
    return arr[dayOrder];
  }
  std::string getDayShortName() const {
    return getDayShortName(_day, _month, _year);
  }

  // Check if the given int is Valid day
  static bool isValidDayOrder(short day) { return (1 <= day && day <= 7); }
  bool isValidDayOrder() const { return isValidDayOrder(_day); }

  // Check if the given string is a Valid day name
  static bool isValidDayOrder(std::string dayName) {
    const auto &shortDaysNames = getDaysShortNames();
    const auto &fullDaysName = getDaysFullNames();
    Mstring::capitalize(dayName);

    for (std::size_t i = 0; i < shortDaysNames.size(); i++) {
      if (dayName == shortDaysNames[i] || dayName == fullDaysName[i]) {
        return true;
      }
    }

    return false;
  }

  static bool isLastDayInMonth(const TimeDate &td) {
    return td.getMonthDays() == td.getDay();
  }
  bool isLastDayInMonth() const { return isLastDayInMonth(*this); }

  // TODO: make a better way to count days and not taking a copy from td
  static int daysUntilEndOfYear(TimeDate td) {
    int days = 0;
    while (!td.isEndOfYear()) {
      days++;
      td.increaseByOneDay();
    }
    return days;
  }
  int daysUntilEndOfYear() const { return daysUntilEndOfYear(*this); }

  static unsigned daysUntilEndOfMonth(const TimeDate &td) {
    return td.getMonthDays() - td.getDay();
  }
  unsigned daysUntilEndOfMonth() { return daysUntilEndOfMonth(*this); }

  static void increaseByOneDay(TimeDate &td) {
    int day = td.getDay() + 1;
    if (day > td.getMonthDays()) {
      td.setDay(1);
      increaseByOneMonth(td);
    } else {
      td.setDay(day);
    }
  }
  void increaseByOneDay() { increaseByOneDay(*this); }

  // Adding day to Time date
  static void increaseByXDays(TimeDate td, int numberOfDays) {
    for (int i = 1; i <= numberOfDays; i++) {
      td.increaseByOneDay();
    }
  }
  void increaseByXDays(unsigned numberOfDays) {
    increaseByXDays(*this, numberOfDays);
  }

  static void decreaseByOneDay(TimeDate &td) {
    int test = td.getDay() - 1;
    if (test == 0) {
      int lastMonthDays = 0;
      if (td.getMonth() == 1) {
        lastMonthDays = getMonthDays(12, td.getYear());
      }
      lastMonthDays = getMonthDays(td.getMonth() - 1, td.getYear());
      td.setDay(lastMonthDays);

      decreaseByOneMonth(td);
    } else {
      td.setDay(test);
    }
  }
  void decreaseByOneDay() { decreaseByOneDay(*this); }

  static void decreaseByXDays(TimeDate td, int numberOfDays) {
    for (int i = 1; i <= numberOfDays; i++) {
      td.decreaseByOneDay();
    }
  }
  void decreaseByXDays(int numberOfDays) {
    decreaseByXDays(*this, numberOfDays);
  }

  // returns -1 if it's invalid month
  static short getMonthDays(short month, short year) {
    if (!isValidMonth(month)) {
      return -1;
    }

    short numberOfDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return (month == 2) ? (isLeapYear(year) ? 29 : 28)
                        : numberOfDays[month - 1];
  }
  short getMonthDays() const { return getMonthDays(_month, _year); }

  static short getYearDays(short year) { return isLeapYear(year) ? 366 : 365; }
  short getYearDays() { return getYearDays(_year); }

  static bool isBusinessDay(const TimeDate &td) { return !isWeekEnd(td); }
  bool isBusinessDay() const { return isBusinessDay(*this); }

  // ***********************************************************
  // *********************** Week Methods **********************
  // ***********************************************************

  static short daysUntilEndOfWeek(const TimeDate &td) {
    return 6 - td.getDayOrderInWeek();
  }
  short daysUntilEndOfWeek() { return daysUntilEndOfWeek(*this); }

  static bool isEndOfWeek(const TimeDate &td) {
    return td.getDayShortName() == "Sat";
  }
  bool isEndOfWeek() const { return isEndOfWeek(*this); }

  static bool isWeekEnd(const TimeDate &td) {
    std::string dayName = td.getDayShortName();
    return dayName == "Fri" || dayName == "Sat";
  }
  bool isWeekEnd() const { return isWeekEnd(*this); }

  static void increaseByOneWeek(TimeDate &td) { td.increaseByXDays(7); }
  void increaseByOneWeek() { increaseByOneWeek(*this); }

  static void decreaseByOneWeek(TimeDate &td) { td.decreaseByXDays(7); }
  void decreaseByOneWeek() { decreaseByOneWeek(*this); }

  static void increaseByXWeek(TimeDate &td, unsigned numberOfWeeks) {
    td.increaseByXDays(7 * numberOfWeeks);
  }
  void increaseByXWeek(unsigned numberOfWeeks) {
    increaseByXWeek(*this, numberOfWeeks);
  }

  static void decreaseByXWeek(TimeDate &td, unsigned numberOfWeeks) {
    td.decreaseByXDays(7 * numberOfWeeks);
  }
  void decreaseByXWeek(unsigned numberOfWeeks) {
    decreaseByXWeek(*this, numberOfWeeks);
  }

  // *************************************************************
  // *********************** Month Methods ***********************
  // *************************************************************

  // Returns false if newMonth is invalid
  bool setMonth(short newMonth) {
    if (!isValidMonth(newMonth))
      return false;

    _month = _month;
    return true;
  }

  short getMonth() const { return _month; }

  // Returns December if month not found
  std::string getMonthFullName() const { return findMonthFullName(_month); }

  // Returns Dec if month not found
  std::string getMonthShortName() const { return findMonthShortName(_month); }

  static bool isLastMonth(short month) { return month == 12; }
  bool isLastMonth() const { return isLastMonth(_month); }

  static void increaseByOneMonth(TimeDate &td) {
    int month = td.getMonth() + 1;

    if (month > 12) {
      td.setMonth(1);
      increaseByOneYear(td);
    } else {
      td.setMonth(month);
    }

    const int monthDays = td.getMonthDays();
    if (td.getDay() > monthDays) {
      td.setDay(monthDays);
    }
  }
  void increaseByOneMonth() { increaseByOneMonth(*this); }

  static void decreaseByOneMonth(TimeDate &td) {
    int test = td.getMonth() - 1;

    if (test == 0) {
      td.setMonth(12);
      decreaseByOneYear(td);
    } else {
      td.setMonth(test);
    }

    const int monthDays = td.getMonthDays();
    if (td.getDay() > monthDays) {
      td.setDay(monthDays);
    }
  }
  void decreaseByOneMonth() { decreaseByOneMonth(*this); }

  static void increaseByXMonths(int months, TimeDate &td) {
    for (int i = 1; i <= months; i++)
      td.increaseByOneMonth();
  }
  void increaseByXMonths(int months) { increaseByXMonths(months, *this); }

  static void decreaseByXMonths(int monthsToRemove, TimeDate &date) {
    for (int i = 1; i <= monthsToRemove; i++)
      date.decreaseByOneMonth();
  }
  void decreaseByXMonths(int monthsToRemove) {
    decreaseByXMonths(monthsToRemove, *this);
  }

  // ************************************************************
  // *********************** Year methods ***********************
  // ************************************************************

  // Returns false if newYear is invalid
  bool setYear(short newYear) {
    if (!isValidYear(newYear))
      return false;

    _year = newYear;
    return true;
  }

  short getYear() const { return _year; }

  static bool isLeapYear(short year) {
    return (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0));
  }
  bool isLeapYear() const { return isLeapYear(_year); }

  static void increaseByOneYear(TimeDate &date) {
    if (date.getDay() == 29 && date.getMonth() == 2 && date.isLeapYear()) {
      date.setDay(28);
    }
    date.setYear(date.getYear() + 1);
  }
  void increaseByOneYear() { increaseByOneYear(*this); }

  static void decreaseByOneYear(TimeDate &date) {
    if (date.getDay() == 29 && date.getMonth() == 2 && date.isLeapYear()) {
      date.setDay(28);
    }
    date.setYear(date.getYear() - 1);
  }
  void decreaseByOneYear() { decreaseByOneYear(*this); }

  static void increaseByXYears(int years, TimeDate &date) {
    if (date.getDay() == 29 && date.getMonth() == 2 && date.isLeapYear()) {
      date.setDay(28);
    }
    date.setYear(date.getYear() + years);
  }
  void increaseByXYears(int years) { increaseByXYears(years, *this); }

  static void decreaseByXYears(int yearsToRemove, TimeDate &td) {
    if (yearsToRemove >= td.getYear())
      return;

    if (td.getDay() == 29 && td.getMonth() == 2 && td.isLeapYear()) {
      td.setDay(28);
    }

    td.setYear(td.getYear() - yearsToRemove);
  }
  void decreaseByXYears(int yearsToRemove) {
    decreaseByXYears(yearsToRemove, *this);
  }

  static bool isEndOfYear(const TimeDate &td) {
    return td.isLastMonth() && td.isLastDayInMonth();
  }
  bool isEndOfYear() const { return isEndOfYear(*this); }

  // Count from 1/1 from the same year
  static short getDayOrderInYear(const TimeDate &td) {
    return differenceBetweenTimeDates(TimeDate(1, 1, td.getYear(), 0, 0, 0),
                                      td);
  }

  // ***********************************************************
  // *********************** Hours Methods *********************
  // ***********************************************************

  // Returns false if newHour is invalid
  bool setHour(short newHour) {
    if (!isValidHour(newHour))
      return false;

    _hour = newHour;
    return true;
  }

  short getHour() const { return _hour; }

  static unsigned short getMonthHours(short month, short year) {
    return getMonthDays(month, year) * 24;
  }
  unsigned short getMonthHours() const { return getMonthHours(_month, _year); }

  static short getYearHours(short year) { return getYearDays(year) * 24; }
  short getYearHours() const { return getYearHours(_year); }

  // ***********************************************************
  // *********************** Minutes Methods *******************
  // ***********************************************************

  // Returns false if newSecond is invalid
  bool setMinute(short newMinute) {
    if (!isValidMinute(newMinute))
      return false;

    _minute = newMinute;
    return true;
  }

  short getMinute() const { return _minute; }

  static unsigned short getMonthMinutes(short month, short year) {
    return getMonthHours(month, year) * 60;
  }
  unsigned short getMonthMinutes() const {
    return getMonthMinutes(_month, _year);
  }

  static unsigned getYearMinutes(short year) { return getYearHours(year) * 60; }
  unsigned getYearMinutes() const { return getYearMinutes(_year); }

  // ***********************************************************
  // *********************** Seconds Methods *******************
  // ***********************************************************

  // Returns false if newSecond is invalid
  bool setSecond(short newSecond) {
    if (!isValidSecond(newSecond))
      return false;

    _second = newSecond;
    return true;
  }

  short getSecond() const { return _second; }

  static unsigned getYearSeconds(short year) {
    return getYearMinutes(year) * 60;
  }
  unsigned getYearSeconds() const { return getYearSeconds(_year); }

  // ************************************************************
  // *********************** Separator Methods ******************
  // ************************************************************

  // Returns false if newSeparator is empty
  bool setSeparator(std::string newSeparator) {
    if (!newSeparator.empty())
      return false;

    _separator = newSeparator;
    return true;
  }

  std::string getSeparator() const { return _separator; }

  // ************************************************************
  // *********************** Full Date Methods ******************
  // ************************************************************

  void swap(TimeDate &td) {
    TimeDate temp = *this;
    *this = td;
    td = temp;
  }

  // If the given date is invalid, the data won't change
  bool setTimeDate(short day, short month, short year, short hour, short minute,
                   short second, std::string separator = "/") {
    if (!isValidTimeDate(day, month, year, hour, minute, second)) {
      return false;
    }

    _day = day;
    _month = month;
    _year = year;
    _hour = hour;
    _minute = minute;
    _second = second;
    _separator = separator;
    return true;
  }

  // Format as following, saying your separator is '/' => DD/MM/YYYY/HH/MM/SS
  // Returns false if newDate is invalid or something went wrong
  bool setTimeDate(std::string newDate, std::string separator = "/") {
    TimeDate *newTimeDate =
        TimeDate::convertStringToTimeDate(newDate, separator);
    if (newTimeDate == nullptr)
      return false;

    *this = *newTimeDate;
    delete newTimeDate;
    return true;
  }

  // Get today's date
  static TimeDate getTodayTimeDate(std::string separator = "/") {
    std::time_t t = std::time(0);
    std::tm *now = std::localtime(&t);

    return TimeDate(now->tm_mday, now->tm_mon + 1, now->tm_year + 1900,
                    now->tm_hour, now->tm_min, now->tm_sec, separator);
  }

  // PASS the correct separator, returns nullptr if something went wrong
  static TimeDate *convertStringToTimeDate(const std::string &date,
                                           const std::string &separator) {
    std::vector<std::string> vDate = Mstring::split(date, separator);
    if (vDate.empty())
      return nullptr;

    short day = std::stoi(vDate.at(0));
    short month = std::stoi(vDate.at(1));
    short year = std::stoi(vDate.at(2));
    short hour = std::stoi(vDate.at(3));
    short minute = std::stoi(vDate.at(4));
    short second = std::stoi(vDate.at(5));

    if (!isValidTimeDate(day, month, year, hour, minute, second))
      return nullptr;

    return new TimeDate(day, month, year, hour, minute, second, separator);
  }

  std::string getAsString() const { return convertTimeDateToString(*this); }

  // ************************************************************
  // **************** General Static Methods ********************
  // ************************************************************

  static bool isDateInsideRange(TimeDate tdToCheck, TimeDate from,
                                TimeDate to) {
    if (tdToCheck == from || tdToCheck == to)
      return true;

    if (tdToCheck > from && tdToCheck < to)
      return true;

    return false;
  }

  // BUG: fix here
  static unsigned calculateAgeInDays(const TimeDate &birthDay) {
    TimeDate today;
    int ageInDays = 0;

    while (birthDay < today) {
      today.decreaseByOneDay();
      ageInDays++;
    }

    return ageInDays;
  }

  // TODO: Find better way avoid copying timedates

  static short calculateBusinessDays(TimeDate from, TimeDate to) {
    if (to > from) {
      return -1;
    }
    short days = 0;
    while (to != from) {
      if (from.isBusinessDay()) {
        days++;
      }
      from.increaseByOneDay();
    }

    return days;
  }

  // TODO: Find better way avoid copying timedates

  static short calculateVacationDays(TimeDate from, TimeDate to) {
    if (to > from) {
      return -1;
    }
    short days = 0;
    while (to != from) {
      if (from.isWeekEnd()) {
        days++;
      }
      from.increaseByOneDay();
    }
    return days;
  }

  // TODO: Find better way avoid copying timedates

  static unsigned differenceBetweenTimeDates(TimeDate td1, TimeDate td2) {
    int difference = 0;
    bool multiple = false;

    if (td1 > td2) {
      td1.swap(td2);
      multiple = true;
    }

    while (td1 != td2) {
      td1.increaseByOneDay();
      difference++;
    }

    return multiple ? difference * -1 : difference;
  }

  // You can use "==" operator it's overloaded
  static bool areTimeDatesEqual(const TimeDate &td1, const TimeDate &td2) {
    return td1 == td2;
  }

  // You can use ">" operator it's overloaded
  static bool isTm1AfterTm2(const TimeDate &d1, const TimeDate &d2) {
    return d1 > d2;
  }

  // You can use "<" operator it's overloaded
  static bool isTm1BeforeTm2(const TimeDate &d1, const TimeDate &d2) {
    return d1 < d2;
  }

  static void swapTimeDates(TimeDate &td1, TimeDate &td2) {
    TimeDate x = td1;
    td1 = td2;
    td2 = x;
  }

  // Return date from number of days from (1 / 1 / given year)
  static TimeDate *getTimeDateFromNumberOfDays(int days, int year,
                                               std::string separator = "/") {
    int d = days;
    int m = 1;
    int y = year;

    short monthDays = getMonthDays(m, y);

    while (d > monthDays) {
      d = d - monthDays;
      m++;
      if (m == 13) {
        m = 1;
        y++;
      }

      monthDays = getMonthDays(m, y);
    }

    std::string date = "";
    date += std::to_string(d) + separator;
    date += std::to_string(m) + separator;
    date += std::to_string(y);
    // return Date(d, m, y);
    return new TimeDate(d, m, y, 0, 0, 0, separator);
  }

  static bool isValidTimeDate(short day, short month, short year, short hour,
                              short minute, short second) {

    return (isValidYear(year) && isValidMonth(month) &&
            isValidDay(day, month, year) && isValidHour(hour) &&
            isValidMinute(minute) && isValidSecond(second));
  }

  static std::string convertTimeDateToString(const TimeDate &td) {
    std::string str = std::to_string(td.getDay()) + td.getSeparator();
    str = std::to_string(td.getMonth()) + td.getSeparator();
    str = std::to_string(td.getYear()) + td.getSeparator();
    str = std::to_string(td.getHour()) + td.getSeparator();
    str = std::to_string(td.getMinute()) + td.getSeparator();
    str = std::to_string(td.getSecond());
    return str;
  }

  // Returns December if month not found
  static std::string findMonthFullName(short monthOrder) {
    if (!isValidMonth(monthOrder))
      return "Dec";

    const auto &arr = getMonthsFullNames();
    std::string monthName = arr[monthOrder];
    return monthName;
  }

  // Returns Dec if month not found
  static std::string findMonthShortName(short monthOrder) {
    if (!isValidMonth(monthOrder))
      return "Dec";

    const auto &arr = getMonthsShortNames();
    std::string monthName = arr[monthOrder];
    return monthName;
  }

  static std::array<std::string, 12> getMonthsShortNames() {
    static std::array<std::string, 12> arr = {"Jan", "Feb", "Mar", "Apr",
                                              "May", "Jun", "Jul", "Aug",
                                              "Sep", "Oct", "Nov", "Dec"};

    return arr;
  }

  static std::array<std::string, 12> getMonthsFullNames() {
    static std::array<std::string, 12> arr = {
        "January", "February", "March",     "April",   "May",      "June",
        "July",    "August",   "September", "October", "November", "December"};

    return arr;
  }

  static std::array<std::string, 7> getDaysFullNames() {
    static std::array<std::string, 7> arr = {"Sunday",    "Monday",   "Tuesday",
                                             "Wednesday", "Thursday", "Friday",
                                             "Saturday"};

    return arr;
  }

  static std::array<std::string, 7> getDaysShortNames() {
    static std::array<std::string, 7> arr = {"Sun", "Mon", "Tue", "Wed",
                                             "Thu", "Fri", "Sat"};
    return arr;
  }

  static bool isValidDay(short dayOrder, short month, short year) {
    int monthDays = getMonthDays(month, year);
    return (1 <= dayOrder && dayOrder <= monthDays);
  }

  static bool isValidMonth(short month) { return (month >= 1 && month <= 12); }

  static bool isValidMonth(std::string monthName) {
    const auto &fullNamesArr = getMonthsFullNames();
    const auto &shortNamesArr = getMonthsShortNames();
    for (int i = 0; i < 12; i++) {
      if (monthName == fullNamesArr[i] || monthName == shortNamesArr[i]) {
        return true;
      }
    }
    return false;
  }

  static bool isValidYear(short year) { return year > 0; }

  static bool isValidHour(short Hour) { return (0 <= Hour && Hour <= 23); }

  static bool isValidMinute(short minute) {
    return (0 <= minute && minute <= 59);
  }

  // Checks if the given second is 0 <= second <= 59
  static bool isValidSecond(short second) {
    return (0 <= second && second <= 59);
  }

  static bool isValidDate(short day, short month, short year) {
    return (isValidDay(day, month, year) && isValidMonth(month) &&
            isValidYear(year));
  }

  // ************************************************************
  // **************** Operator Overloading **********************
  // ************************************************************

  bool operator==(const TimeDate &other) const {
    return (_day == other.getDay() && _month == other.getMonth() &&
            _year == other.getYear() && _hour == other.getHour() &&
            _minute == other.getMinute() && _second == other.getSecond());
  }

  bool operator!=(const TimeDate &other) const { return !(*this == other); }

  bool operator>(const TimeDate &other) const {
    if (_year > other.getYear())
      return true;
    if (_month > other.getMonth())
      return true;
    if (_day > other.getDay())
      return true;
    if (_hour > other.getHour())
      return true;
    if (_minute > other.getMinute())
      return true;
    if (_second > other.getSecond())
      return true;

    return false;
  }

  bool operator<(const TimeDate &other) const { return !(*this > other); }
};

std::ostream &operator<<(std::ostream &os, const TimeDate &date) {
  std::string separator = date.getSeparator();
  os << date.getYear() << separator;
  os << date.getMonth() << separator;
  os << date.getDay() << ":";
  os << date.getHour() << separator;
  os << date.getMinute() << separator;
  os << date.getSecond();
  return os;
}

#endif