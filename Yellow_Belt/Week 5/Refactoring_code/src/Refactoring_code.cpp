#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Human{
public:
	Human(const string& _Name, const string& _Profession) : Name(_Name), Profession(_Profession) {}
	virtual void Walk(const string& destination) const {
		cout << Profession << ": " << Name << " walks to: " << destination << endl;
	};
	string GetName() const {
		return Name;
	}
	string GetProfession() const {
		return Profession;
	}
protected:
	const string Name;
	const string Profession;
};

class Student : public Human {
public:
    Student(const string& _Name, const string& favouriteSong) :
    	Human(_Name, "Student"), FavouriteSong(favouriteSong) {}
    void Learn() const {
        cout << "Student: " << GetName() << " learns" << endl;
    }
    void Walk(const string& destination) const override {
        Human::Walk(destination);
        SingSong();
    }
    void SingSong() const {
        cout << "Student: " << GetName() << " sings a song: " << FavouriteSong << endl;
    }
protected:
    const string FavouriteSong;
};

class Teacher : public Human {
public:
    Teacher(const string& name, const string& subject, const string& _Profession = "Teacher") :
    	Human(name, "Teacher"), Subject(subject) {}
    void Teach() const {
        cout << "Teacher: " << GetName() << " teaches: " << Subject << endl;
    }
protected:
    const string Subject;
};


class Policeman : public Human {
public:
    Policeman(const string& name) : Human(name, "Policeman") {}
    void Check(const Human& M) const {
    	cout << "Policeman: " << GetName() << " checks " << M.GetProfession()
    			<< ". " << M.GetProfession() << "'s name is: " << M.GetName() << endl;
    }
};

void VisitPlaces(const Human& t, const vector<string>& places) {
    for (const auto& p : places) {
        t.Walk(p);
    }
}

int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");
    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}
