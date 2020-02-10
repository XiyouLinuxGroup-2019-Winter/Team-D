#include <iostream>

using namespace std;

int main() {
    const unsigned int ADD_SUBTRACT = 32;
    const double RATIO = 9.0 / 5.0;
    double tempIn, tempOut;
    char typeIn, typeOut;

    cout << "请以xx.x C或xx.x F格式输入一个温度:\n";
    cin >> tempIn >> typeIn;
    cin.ignore(100, '\n');
    
    switch (typeIn) {
    case 'C':
    case 'c':
        tempOut = tempIn * RATIO + ADD_SUBTRACT;
        typeOut = 'F';
        typeIn = 'C';
        break;
    case 'F':
    case 'f':
        tempOut = (tempIn - ADD_SUBTRACT) / RATIO;
        typeOut = 'C';
        typeIn = 'F';
        break;
    default :
        typeOut = 'E';
        break;
    }
    if (typeOut != 'E') {
        cout << tempIn << typeIn 
            << " = " << tempOut 
            << typeOut << "\n\n";
    }
    else {
        cout << "输入格式错误!\n" << endl;
    }

}
