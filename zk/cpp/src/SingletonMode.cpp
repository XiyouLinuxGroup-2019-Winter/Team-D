#include <iostream>
using namespace std;

class Rocket {
private:
    Rocket() {}
    static Rocket *ms_rocket;
public:
    static Rocket *sharedRocket() {
        if (ms_rocket == NULL) {
            ms_rocket = new Rocket();
        }
        return ms_rocket;
    }

    static void deleteRocket() {
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

