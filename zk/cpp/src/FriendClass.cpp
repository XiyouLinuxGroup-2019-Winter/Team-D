#include <iostream>
#include <string>

using namespace std;

class Lovers {
public:
    Lovers(string theName);
    void kiss(string theName);
    void ask(string theName);
    friend class Others;

protected:
    string name;
};

Lovers::Lovers(string theName) {
    name = theName;
}

void kiss(string theName) {
    cout << "I kiss " << theName << endl;
}

void ask(string theName) {
    cout << "I ask " << theName << "do something"<< endl;
}
 
class Boyfriend : public Lovers {
public:
    Boyfriend(string theName);
};

Boyfriend::Boyfriend(string theName) : Lovers(theName) {

}

class Girlfriend : public Lovers {
public:
    Girlfriend(string theName);
};

Girlfriend::Girlfriend(string theName) : Lovers(theName) {

}

class Others {
public:
    Others(string theName);
    void kiss(string theName);
protected:
    string name;
};

Others::Others(string theName) {
    name = theName;
}

void Others::kiss(string name) {
    cout << "kiss " << name << endl;
}

int main()
{
    Others others("others");
    Girlfriend girlfriend("girl");
    Boyfriend boyfriend("boy");
    girlfriend.kiss(boyfriend.name);

    others.kiss()
    return 0;
}

