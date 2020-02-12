#include <iostream>
using namespace std;

class Animal {
public:
    virtual void speak() = 0;
    virtual void run() = 0;
};

class Cat : public Animal {
public:
    void speak() {
        cout << "1" << endl;
    }
    void run() {
        cout << "22" << endl;
    }
};

int main()
{
    Animal *cat = new Cat();
    cat->speak();
    cat->run();
    return 0;
}

