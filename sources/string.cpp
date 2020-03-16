// Copyright 2020 Evgenij Grigorev evgengrmit@icloud.com

#include "string.hpp"
/// Деструктор
String::~String() { delete[] Data; }
/// Конструктор по умолчанию
String::String() {
  Data = new char[1];
  Data[0] = '\0';
  SizeOfString = 0;
}
/// Конструктор копирования
String::String(const String& rhs)
    : String(rhs.Data) {}  // Делегирование конструкторов
/// Пользовательский конструктор
String::String(const char* data) {
  SizeOfString = std::strlen(data);
  Data = new char[SizeOfString + 1];
  std::copy(data, data + SizeOfString + 1, Data);
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
    SizeOfString = rhs.SizeOfString;
    Data = new char[rhs.SizeOfString + 1];
    std::copy(rhs.Data, rhs.Data + rhs.SizeOfString + 1, Data);
  }
  return *this;
}
/// Оператор +=
String& String::operator+=(const String& rhs) {
  char* tempArray = new char[SizeOfString + rhs.SizeOfString + 1];
  std::copy(Data, Data + SizeOfString + 1, tempArray);
  std::copy(rhs.Data, rhs.Data + rhs.SizeOfString + 1,
            tempArray + std::strlen(tempArray));
  delete[] Data;
  Data = tempArray;
  SizeOfString = std::strlen(tempArray);
  return *this;
}
/// Оператор *=
String& String::operator*=(unsigned int m) {
  char* tempArray = new char[SizeOfString * m + 1];
  for (size_t i = 0, step = 0; i < m; ++i, step += std::strlen(Data)) {
    std::copy(Data, Data + std::strlen(Data), tempArray + step);
  }
  tempArray[std::strlen(Data) * m] = '\0';
  delete[] Data;
  Data = tempArray;
  SizeOfString = std::strlen(tempArray);
  return *this;
}
/// Оператор ==
bool String::operator==(const String& rhs) const {
  return !std::strcmp(Data, rhs.Data);
}
/// Оператор &lt;
bool String::operator<(const String& rhs) const {
  return std::strcmp(Data, rhs.Data) < 0;
}
///Функция поиска подстроки
size_t String::Find(const String& substr) const {
  bool flag = false;  // Подстрока не найдена
  int index = 0;
  for (size_t i = 0; i < SizeOfString; ++i) {
    if (Data[i] == substr.Data[0]) {
      flag = true;
      index = i;
      for (size_t j = 1; j < substr.SizeOfString && i + j < SizeOfString; ++j) {
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
  for (size_t i = 0; i < SizeOfString; ++i) {
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
  if (index > SizeOfString - 1) {
    throw std::out_of_range("index >= length of string");
  }
  return Data[index];
}
/// Оператор [] с доступом
char& String::operator[](const size_t& index) {
  if (index > SizeOfString - 1) {
    throw std::out_of_range("index >= length of string");
  }
  return Data[index];
}
/// Отрезание символов справа
void String::RTrim(const char& symbol) {
  size_t countOfTrim = 0;
  for (int i = static_cast<int>(SizeOfString) - 1; i >= 0; --i) {
    if (Data[i] == symbol) {
      ++countOfTrim;
    } else {
      break;
    }
  }

  char* tempArray = new char[SizeOfString - countOfTrim + 1];
  std::copy(Data, Data + SizeOfString - countOfTrim, tempArray);
  tempArray[SizeOfString - countOfTrim] = '\0';
  delete[] Data;
  Data = tempArray;
  SizeOfString = std::strlen(tempArray);
}
/// Отрезание символов слева
void String::LTrim(const char& symbol) {
  size_t countOfTrim = 0;
  for (size_t i = 0; i < SizeOfString; ++i) {
    if (Data[i] == symbol) {
      ++countOfTrim;
    } else {
      break;
    }
  }
  char* tempArray = new char[(std::strlen(Data) - countOfTrim) + 1];
  std::copy(Data + countOfTrim, Data + SizeOfString + 1, tempArray);
  delete[] Data;
  Data = tempArray;
  SizeOfString = std::strlen(tempArray);
}

void String::swap(String& oth) { std::swap(Data, oth.Data); }
/// Оператор +
String operator+(const String& a, const String& b) {
  String sum(a);
  sum += b;
  return sum;
}
/// Оператор *
String operator*(const String& a, unsigned int b) {
  String multiplyingByTheNumber(a);
  multiplyingByTheNumber *= b;
  return multiplyingByTheNumber;
}
/// Оператор !=
bool operator!=(const String& a, const String& b) { return !(a == b); }
/// Оператор &gt;
bool operator>(const String& a, const String& b) { return b < a; }
/// Оператор вывода
std::ostream& operator<<(std::ostream& out, const String& str) {
  for (size_t i = 0; i < str.SizeOfString; ++i) {
    out << str.Data[i];
  }
  return out;
}
