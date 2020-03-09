// Copyright 2020 Evgenij Grigorev evgengrmit@icloud.com

#include "string.hpp"
/// Деструктор
String::~String() { delete Data; }
/// Конструктор по умолчанию
String::String() {
  Data = new char[1];
  Data[0] = '\0';
}
/// Конструктор копирования
String::String(const String& rhs) {
  Data = new char[std::strlen(rhs.Data) + 1];
  std::snprintf(Data, std::strlen(rhs.Data) + 1, "%s", rhs.Data);
}
/// Пользовательский конструктор
String::String(const char* data) {
  Data = new char[std::strlen(data) + 1];
  std::snprintf(Data, std::strlen(data) + 1, "%s", data);
}
/// Оператор присваивания
String& String::operator=(const String& rhs) {
  if (this == &rhs) {  // Обработка самоприсваивания
    return *this;
  } else {
    if (!Data) {  // Если указатель непустой очищаем массив
    } else {
      delete[] Data;
    }
    Data = new char[std::strlen(rhs.Data) + 1];
    std::snprintf(Data, std::strlen(rhs.Data) + 1, "%s", rhs.Data);
  }
  return *this;
}
/// Оператор +=
String& String::operator+=(const String& rhs) {
  char* temporaryArray =
      new char[std::strlen(Data) + std::strlen(rhs.Data) + 1];
  std::copy(Data, Data + std::strlen(Data), temporaryArray);
  std::snprintf(temporaryArray, std::strlen(Data) + 1, "%s", Data);
  std::snprintf(temporaryArray + std::strlen(Data), std::strlen(rhs.Data) + 1,
                "%s", rhs.Data);
  delete[] Data;
  Data = temporaryArray;
  return *this;
}
/// Оператор *=
String& String::operator*=(unsigned int m) {
  char* temporaryArray = new char[std::strlen(Data) * (m + 1) + 1];
  for (size_t i = 0, step = 0; i < (m + 1); ++i, step += std::strlen(Data)) {
    std::snprintf(temporaryArray + step, std::strlen(Data) + 1, "%s", Data);
  }
  delete[] Data;
  Data = temporaryArray;
  return *this;
}
/// Оператор ==
bool String::operator==(const String& rhs) const {
  for (size_t i = 0; i < std::max(std::strlen(Data), std::strlen(rhs.Data));
       ++i) {
    if (Data[i] - rhs.Data[i]) {
      return false;
    }
  }
  return true;
}
/// Оператор &lt;
bool String::operator<(const String& rhs) const {
  for (size_t i = 0; i < std::max(std::strlen(Data), std::strlen(rhs.Data));
       ++i) {
    if (Data[i] - rhs.Data[i] < 0) {
      return true;
    } else if (Data[i] - rhs.Data[i] > 0) {
      return false;
    }
  }
  return false;
}
///Функция поиска подстроки
size_t String::Find(const String& substr) const {
  bool flag = false;  // Подстрока не найдена
  int index = 0;
  for (size_t i = 0; i < std::strlen(Data); ++i) {
    if (Data[i] == substr.Data[0]) {
      flag = true;
      index = i;
      for (size_t j = 1;
           j < std::strlen(substr.Data) && i + j < std::strlen(Data); ++j) {
        if (Data[i + j] == substr.Data[j]) {
          flag = true;
        } else {
          flag = false;
          break;
        }
      }
    }
    if (flag) {
      return index;
    }
  }

  return -1;
}
/// Функция замены символов, заменяет все символы oldSymbol на newSymbol.
void String::Replace(const char& oldSymbol, const char& newSymbol) {
  for (size_t i = 0; i < std::strlen(Data); ++i) {
    if (Data[i] == oldSymbol) {
      Data[i] = newSymbol;
    }
  }
}
/// Функция возвращает длину строки
size_t String::Size() const { return std::strlen(Data); }
/// Функция для определения пуста ли строка
bool String::Empty() const { return std::strlen(Data) == 0; }
/// Оператор [] без доступа
char String::operator[](const size_t& index) const {
  if (index > std::strlen(Data) - 1) {
    exit(1);
  }
  return Data[index];
}
/// Оператор [] с доступом
char& String::operator[](const size_t& index) {
  if (index > std::strlen(Data) - 1) {
    exit(1);
  }
  return Data[index];
}
/// Отрезание символов справа
void String::RTrim(const char& symbol) {
  size_t countOfTrim = 0;
  for (size_t i = std::strlen(Data) - 1; i; --i) {
    if (Data[i] == symbol) {
      ++countOfTrim;
    } else {
      break;
    }
  }

  char* temporaryArray = new char[std::strlen(Data) - countOfTrim + 1];
  std::snprintf(temporaryArray, std::strlen(Data) + 1 - countOfTrim, "%s",
                Data);
  delete[] Data;
  Data = temporaryArray;
}
/// Отрезание символов слева
void String::LTrim(const char& symbol) {
  size_t countOfTrim = 0;
  for (size_t i = 0; i < std::strlen(Data); ++i) {
    if (Data[i] == symbol) {
      ++countOfTrim;
    } else {
      break;
    }
  }
  char* temporaryArray = new char[(std::strlen(Data) - countOfTrim) + 1];
  std::snprintf(temporaryArray, std::strlen(Data) + 1 - countOfTrim, "%s",
                Data + countOfTrim);
  delete[] Data;
  Data = temporaryArray;
}
void String::swap(String& oth) {
  char* temp = Data;
  Data = oth.Data;
  oth.Data = temp;
}
/// Оператор +
String operator+(const String& a, const String& b) {
  String sum(a);
  sum += b;
  return sum;
}
/// Оператор *
String operator*(const String& a, unsigned int b) {
  String multiplyingByTheNumber(a);
  for (size_t i = 0; i < b - 1; ++i) {
    multiplyingByTheNumber += a;
  }
  return multiplyingByTheNumber;
}
/// Оператор !=
bool operator!=(const String& a, const String& b) { return !(a == b); }
/// Оператор &gt;
bool operator>(const String& a, const String& b) { return !(a == b || a < b); }
/// Оператор вывода
std::ostream& operator<<(std::ostream& out, const String& str) {
  for (size_t i = 0; i < std::strlen(str.Data); ++i) {
    out << str.Data[i];
  }
  return out;
}
