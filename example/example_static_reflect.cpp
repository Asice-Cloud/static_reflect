#include "../static_reflect.h"
#include "../static_reflect_json.h"
#include <iostream>
#include <vector>

struct Address {
  std::string country;
  std::string field;
  std::string city;

  int (*func)();

  void show() {
    std::cout << "Country: " << country << '\n';
    std::cout << "Field: " << field << '\n';
    std::cout << "City: " << city << '\n';
  }

  std::string to_str() const { return country + " " + field + " " + city; }

  static void test() { std::cout << "static function test\n"; }

  REFLECT(country, field, city, func, show, to_str, test);
};

struct Student {
  std::string name;
  int age;

  void (*func)();
  void display() {
    std::cout << "Name: " << name << '\n';
    std::cout << "Age: " << age << '\n';
  }
  Address addr;

  REFLECT(name, age, display, addr);
};

int main() {
  Student stu = {.name = "Reissiya Rin",
                 .age = 20,
                 .func = []() -> void { std::cout << "func\n"; },
                 .addr = {
                     .country = "SierruEua",
                     .field = "convergence/crossing",
                     .city = "Cloud",
                     .func = []() -> int {
                       std::cout << "func\n";
                       return 0;
                     },
                 }};

  std::string binary = reflect_json::serialize(stu);
  std::cout << binary << '\n';
  auto stuDes = reflect_json::deserialize<Student>(binary);

  std::cout << stuDes.name << '\n';
  std::cout << stuDes.age << '\n';
  std::cout << stuDes.addr.country << '\n';
  std::cout << stuDes.addr.field << '\n';
  std::cout << stuDes.addr.city << '\n';

  auto vec =
      reflect_json::deserialize<std::vector<int>>(R"json([1, 2, 3])json");
  std::cout << vec.at(0) << '\n';
  std::cout << vec.at(1) << '\n';
  std::cout << vec.at(2) << '\n';

  return 0;
}
