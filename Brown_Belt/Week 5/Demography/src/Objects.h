#pragma once

enum class Gender {
  FEMALE,
  MALE
};


struct Person {
  int age;  // возраст
  Gender gender;  // пол
  bool is_employed;  // имеет ли работу
};


template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end);
