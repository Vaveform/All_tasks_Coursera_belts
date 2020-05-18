void PrintStats(vector<Person> persons)
{
	cout << "Median age = " << ComputeMedianAge(persons.begin(), persons.end()) << endl;
	auto it = partition(persons.begin(), persons.end(), [](Person personal) {
		return personal.gender == Gender::FEMALE;
	});
	cout << "Median age for females = " << ComputeMedianAge(persons.begin(), it) << endl;
	it = partition(persons.begin(), persons.end(), [](Person personal) {
		return personal.gender == Gender::MALE;
	});
	cout << "Median age for males = " << ComputeMedianAge(persons.begin(), it) << endl;
	it = partition(persons.begin(), persons.end(), [](Person personal) {
		return personal.gender == Gender::FEMALE && personal.is_employed == true;
	});
	cout << "Median age for employed females = " << ComputeMedianAge(persons.begin(), it) << endl;
	it = partition(persons.begin(), persons.end(), [](Person personal) {
		return personal.gender == Gender::FEMALE && personal.is_employed == false;
	});
	cout << "Median age for unemployed females = " << ComputeMedianAge(persons.begin(), it) << endl;
	it = partition(persons.begin(), persons.end(), [](Person personal) {
		return personal.gender == Gender::MALE && personal.is_employed == true;
	});
	cout << "Median age for employed males = " << ComputeMedianAge(persons.begin(), it) << endl;
	it = partition(persons.begin(), persons.end(), [](Person personal) {
		return personal.gender == Gender::MALE && personal.is_employed == false;
	});
	cout << "Median age for unemployed males = " << ComputeMedianAge(persons.begin(), it) << endl;
}