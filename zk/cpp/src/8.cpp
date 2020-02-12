#include <iostream>
using namespace std;

class Animal {
public:
    virtual void speak() {
        cout << "Animal::speak()" << endl;
    }
};

class Cat : public Animal {
public:
    void speak() {
        Animal::speak();
        cout << "Cat::speak()" << endl;
    }
};

int main()
{
    Animal *cat = new Cat();
    cat->speak();
    return 0;
}

