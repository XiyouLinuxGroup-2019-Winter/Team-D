#include <iostream>
using namespace std;

class Rocket {
private:
    static Rocket *ms_rocket;
    Rocket() {}
    Rocket(const Rocket &rocket) {}
    ~Rocket() {}
    void operator=(const Rocket &rocket) {}
public:
    static Rocket *sharedRocket() {
        // 这里要考虑多线程安全
        if (ms_rocket == NULL) {
            ms_rocket = new Rocket();
        }
        return ms_rocket;
    }

    static void deleteRocket() {
        // 这里要考虑多线程安全
        if (ms_rocket != NULL) {
            delete ms_rocket;
            ms_rocket = NULL;
            // 防止野指针
        }
    }
    
    void run() {
        cout << "run()" << endl;
    }
};

Rocket *Rocket::ms_rocket = NULL;

int main()
{
    Rocket *p = Rocket::sharedRocket();
    p->run();
    p->deleteRocket();
    return 0;
}

