//============================================================================
// Name        : Demography_data.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <algorithm>
#include "Objects.h"

using namespace std;



void PrintStats(vector<Person> persons){
	auto women_end = std::partition(persons.begin(), persons.end(), [](const Person& p){
		return p.gender == Gender::FEMALE;
	});
	auto employed_people = [](const Person& p){
		return p.is_employed;
	};
	auto employed_women_end = partition(persons.begin(), women_end, employed_people);
	auto employed_men_end = partition(women_end, persons.end(), employed_people);
	cout << "Median age = " << ComputeMedianAge(persons.begin(), persons.end()) << endl;
	cout << "Median age for females = " << ComputeMedianAge(persons.begin(), women_end) << endl;
	cout << "Median age for males = " << ComputeMedianAge(women_end, persons.end()) << endl;
	cout << "Median age for employed females = " << ComputeMedianAge(persons.begin(), employed_women_end) << endl;
	cout << "Median age for unemployed females = " << ComputeMedianAge(employed_women_end, women_end) << endl;
	cout << "Median age for employed males = " << ComputeMedianAge(women_end, employed_men_end) << endl;
	cout << "Median age for unemployed males = " << ComputeMedianAge(employed_men_end, persons.end()) << endl;

}


int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
