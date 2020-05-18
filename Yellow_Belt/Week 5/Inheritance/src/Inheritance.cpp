#include <iostream>
#include <string>

using namespace std;

class Animal {
public:
    Animal(const string& t = "animal") :
    	Name(t){
    }
    const string Name;
};


class Dog : public Animal {
public:
    Dog(const string& dog_type) : Animal(dog_type){
    }
    void Bark() {
        cout << Name << " barks: woof!" << endl;
    }
};

int main()
{
	Dog d("Pec");
	d.Bark();
	return 0;
}
