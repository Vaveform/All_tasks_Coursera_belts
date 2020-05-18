
#include <iostream>
#include <string>

using namespace std;

struct Specialization
{
	string Specialization_val;
	explicit Specialization(string New_Specialization_val)
	{
		Specialization_val = New_Specialization_val;
	}
};
struct Course
{
	string Course_val;
	explicit Course(string New_Course_val)
	{
		Course_val = New_Course_val;
	}
};
struct Week
{
	string Week_val;
	explicit Week(string New_Week_val)
	{
		Week_val = New_Week_val;
	}
};

struct LectureTitle
{
  string specialization;
  string course;
  string week;

  LectureTitle(Specialization New_Specialization, Course New_Course, Week New_Week)
  {
	  specialization = New_Specialization.Specialization_val;
	  course = New_Course.Course_val;
	  week = New_Week.Week_val;
  }
};

int main()
{
	return 0;
}
