#include <iostream>
#include <string>

using namespace std;

class Animal {
public://这是访问控制,公开的
    Animal(string theName);//构造器
    void eat();
    void sleep();
    void drool();

protected://被保护的
    string name;
};//基类

class Pig : public Animal {
public:
    Pig(string theName);
    void climb();    
};//子类
//子类会继承基类的属性和方法
class Turtle : public Animal {
public:
    Turtle(string theName);
    void swim();
};

Animal::Animal(string theName) {
    name = theName;
}

void Animal::eat() {
    cout << "I'm eatting!" << endl;
}

void Animal::sleep() {
    cout << "I'm sleeping!Don't disturb me!" << endl;
}

void Animal::drool() {
    cout << "I'm drooling!" << endl;
}

Pig::Pig(string theName) : Animal(theName) {

}//子类构造器继承基类构造器,在调用子类
//构造器时,基类构造器会被自动调用

void Pig::climb() {
    cout << "I'm a pig, i'm climbing!" << endl;
}

Turtle::Turtle(string theName) : Animal(theName) {

}

void Turtle::swim() {
    cout << "i'm a turtle, i'm swimming!" << endl;
}

int main()
{
    Pig pig("xiaozhu");
    Turtle turtle("xiaogui");
    //pig.name = "xiaowugui";
    //这个操作无法成功,因为name是被保护的属性
    pig.eat();
    turtle.eat();
    pig.climb();
    turtle.swim();
    return 0;
}

