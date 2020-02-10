#include <iostream>
#include <fstream>

using namespace std;

class StoreQuote {
public:
    string quote, speaker;
    ofstream fileOutput;

    StoreQuote();
    ~StoreQuote();

    void inputQuote();
    void inputSpeaker();
    int write();

};

StoreQuote::StoreQuote() {
    fileOutput.open("test.txt", ios::app);
}

StoreQuote::~StoreQuote() {
    fileOutput.close();
}

void StoreQuote::inputQuote() {
    getline(cin, quote);
}

void StoreQuote::inputSpeaker() {
    getline(cin, speaker);
}

int StoreQuote::write() {
    if (fileOutput.is_open()) {
        fileOutput << quote << "|" << speaker << "\n";
        return 1;
    }
    else {
        return 0;
    }
}

int main()
{
    StoreQuote quote;

    cout << "请输入一句名言: \n";
    quote.inputQuote();
    cout << "请输入作者: \n";
    quote.inputSpeaker();
    if (quote.write()) {
        cout << "Successful!";
    }
    else {
        cout << "Sorry, write fail!!";
        return 1;
    }
    return 0;
}

