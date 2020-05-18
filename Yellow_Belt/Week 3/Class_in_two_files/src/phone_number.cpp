#include "phone_number.h"
#include <stdexcept>

using namespace std;

string PhoneNumber::GetCountryCode() const{
	return country_code_;
}

string PhoneNumber::GetCityCode() const{
	return city_code_;
}

string PhoneNumber::GetLocalNumber() const{
	return local_number_;
}

string PhoneNumber::GetInternationalNumber() const{
	return "+" + country_code_ + "-" + city_code_ + "-" + local_number_;
}

PhoneNumber::PhoneNumber(const string &international_number)
{
	string new_country_code, new_city_code, new_local_number;
	int pos = 0;
	if(international_number[0] != '+')
	{
		throw invalid_argument("Invalid syntax.");
	}
	pos++;
	for(unsigned int i = pos; i < international_number.size(); i++)
	{
		if(international_number[i] == '-' && pos < 3){
			pos++;
		}
		else if(pos == 1){
			new_country_code += international_number[i];
		}
		else if(pos == 2){
			new_city_code += international_number[i];
		}
		else if(pos == 3){
			new_local_number += international_number[i];
		}
	}
	if(new_country_code.size() == 0 ||
			new_city_code.size() == 0 ||
			new_local_number.size() == 0){
		throw invalid_argument("Invalid syntax.");
	}
	else{
		country_code_ = new_country_code;
		city_code_ = new_city_code;
		local_number_ = new_local_number;
	}
}


