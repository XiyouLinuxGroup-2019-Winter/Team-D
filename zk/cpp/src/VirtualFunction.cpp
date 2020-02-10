#include <iostream>
using namespace std;

class Animal {
public:
    virtual void speak() {
        cout << "Animal::speak()" << endl;
    }
    virtual void run() {
        cout << "Animal::run()" << endl;
    }
};

class Dog : public Animal {
public:
    // 重写(override)
    void speak() {
        cout << "Dog::speak()" << endl;
    }
    void run() {
        cout << "Dog::run()" << endl;
    }
};

class Cat : public Animal {
    void speak() {
        cout << "Cat::speak()" << endl;
    }
    void run() {
        cout << "Cat::run()" << endl;
    }
};

class Pig : public Animal {
    void speak() {
        cout << "Pig::speak()" << endl;
    }
    void run() {
        cout << "Pig::run()" << endl;
    }
};

void liu(Animal *p) {
    p->speak();
    p->run();
}

int main()
{
    liu(new Dog());
    liu(new Cat());
    liu(new Pig());
    return 0;
}

