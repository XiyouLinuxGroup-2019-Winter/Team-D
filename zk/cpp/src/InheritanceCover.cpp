#include <iostream>
#include <string>

using namespace std;

class Animal {
public:
    Animal(string theName);
    void eat();
    void sleep();
    void drool();
protected:
    string name;
};

class Pig : public Animal {
public:
    Pig(string theName);
    void eat();
    void climb();
};

class Turtle : public Animal {
public:
    Turtle(string theName);
    void eat();
    void swim();
};

Animal::Animal(string theName) {
    name = theName;
}

void Animal::eat() {
    cout << "I'm eatting!" << endl;
}

void Animal::sleep() {
    cout << "I'm sleeping!" << endl;
}

void Animal::drool() {
    cout << "I'm drooling!" << endl;
}

Pig::Pig(string theName) : Animal(theName) {

}

void Pig::eat() {
    Animal::eat();
    cout << "covering Pig\n";
}

void Pig::climb() {
    cout << "I'm climbing!" << endl;
}

Turtle::Turtle(string theName) : Animal(theName) {
    
}

void Turtle::eat() {
    cout << "covering Turtle\n";
}

void Turtle::swim() {
    cout << "I'm swimming!!\n";
}

int main() {
    Pig pig("small pig");
    Turtle turtle("small turtle");

    pig.eat();
    turtle.eat();
    
    return 0;
}


