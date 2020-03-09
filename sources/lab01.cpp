// Copyright 2020 Evgenij Grigorev evgengrmit@icloud.com
#include <string.hpp>
int main() {
  const char* data = "some string";
  String s0(data);
  s0[0] = 'S';
  String s1(s0);
  s1[5] = s0[0];
  String s2;
  s2 = s1;
  s2[0] = 's';
  { s1 = String("some"); }
  s1 += String(" ");
  s1 += String("string");
  s1.Replace('s', 'S');
  std::cout << s1.Size();
  std::cout << s1.Empty();
  std::cout << (s1 == s2);
  std::cout << (s1 != s2);
  std::cout << (s1 < s2);
  std::cout << (s1 > s2);
  s1 *= 2;
  s1 += s2 * 3;
  std::cout << s1.Find(String("str"));

  std::cout << String().Empty();
  String s("  abc   ____");

  s.RTrim('_');
  std::cout << s << std::endl;

  s.LTrim(' ');
  std::cout << s << std::endl;

  s.RTrim(' ');
  std::cout << s << std::endl;
  return 0;
}
