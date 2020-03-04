#include <iostream>
#include <string>

using namespace std;

class BaseClass {
public:
    BaseClass();
    ~BaseClass();

    void doSomething();
};

class SubClass : public BaseClass {
public:
    SubClass();
    ~SubClass();
};

BaseClass::BaseClass() {
    cout << "Enter BaseClass Constructors...\n";
}

BaseClass::~BaseClass() {
    cout << "Enter BaseClass Destructors...\n";
}

void BaseClass::doSomething() {
    cout << "do something...\n";
}

SubClass::SubClass() {
    cout << "Enter SubClass Constructors...\n";
}

SubClass::~SubClass() {
    cout << "Enter SubClass Destructors...\n";
}

int main()
{
    SubClass subclass;
    subclass.doSomething();
    
    cout << "OK!\n";
    return 0;
}

