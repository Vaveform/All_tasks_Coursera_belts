
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Name
{
	string Name_val;
	explicit Name(string New_Name_val)
	{
		Name_val = New_Name_val;
	}
};
struct Second_Name
{
	string Second_Name_val;
	explicit Second_Name(string New_Second_Name_val)
	{
		Second_Name_val = New_Second_Name_val;
	}
};
struct Birth_Day
{
	int Birth_Day_val;
	explicit Birth_Day(int New_Birth_Day_val)
	{
		Birth_Day_val = New_Birth_Day_val;
	}
};
struct Birth_Month
{
	int Birth_Month_val;
	explicit Birth_Month(int New_Birth_Month_val)
	{
		Birth_Month_val = New_Birth_Month_val;
	}
};
struct Birth_Year
{
	int Birth_Year_val;
	explicit Birth_Year(int New_Birth_Year_val)
	{
		Birth_Year_val = New_Birth_Year_val;
	}
};

struct Student
{
	string name;
	string second_name;
	int birth_day;
	int birth_month;
	int birth_year;

	Student(Name new_name, Second_Name new_second_name, Birth_Day new_day,
			Birth_Month new_month, Birth_Year new_year)
	{
		name = new_name.Name_val;
		second_name = new_second_name.Second_Name_val;
		birth_day = new_day.Birth_Day_val;
		birth_month = new_month.Birth_Month_val;
		birth_year = new_year.Birth_Year_val;
	}
};

int main()
{
	int num_of_students, new_birth_day, new_birth_month, new_birth_year, num_of_request, k;
	string new_name, new_second_name, request;
	vector<Student> Students;
	cin >> num_of_students;
	while(num_of_students > 0)
	{
		cin >> new_name >> new_second_name;
		cin >> new_birth_day >> new_birth_month >> new_birth_year;
		Students.push_back(Student(Name(new_name),
				Second_Name(new_second_name), Birth_Day(new_birth_day),
				Birth_Month(new_birth_month), Birth_Year(new_birth_year)));
		num_of_students--;
	}
	cin >> num_of_request;
	while(num_of_request)
	{
		cin >> request;
		cin >> k;
		if(k == 0 || k > Students.size() || (request != "name" && request != "date"))
		{
			cout << "bad request" << endl;
		}
		else if(request == "name")
		{
			cout << Students[k-1].name << " " << Students[k-1].second_name << endl;
		}
		else if(request == "date")
		{
			cout << Students[k-1].birth_day << "." << Students[k-1].birth_month << "." << Students[k-1].birth_year << endl;
		}
		num_of_request--;
	}
	return 0;
}
