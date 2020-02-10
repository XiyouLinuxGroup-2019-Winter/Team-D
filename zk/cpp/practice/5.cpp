#include <iostream>
using namespace std;

enum CPU_Rank{P1=1, P2, P3, P4, P5, P6, P7};

class Cpu {
private:
    CPU_Rank rank;
    int m_frequency;
    double m_voltage;
public:
    Cpu(CPU_Rank r, int f, double v) {
        rank = r;
        m_frequency = f;
        m_voltage = v;
        cout << "构造了一个CPU!!" << endl;
    }
    ~Cpu() {
        cout << "析构了一个CPU!" << endl;
    }

    CPU_Rank GetRank() {
        return rank;
    }
    int getFrequency() {
        return m_frequency;
    }
    int getVoltage() {
        return m_voltage;
    }

    void setRank(CPU_Rank r) {
        rank = r;
    }
    void setFrequency(int f) {
        m_frequency = f;
    }
    void setVoltage(double v) {
        m_voltage = v;
    }

    void Run() {
        cout << "CPU开始运行!" << endl;
    }
    void Stop() {
        cout << "cpu开始停止" << endl;
    }

};

int main()
{
    Cpu cpu(P6, 300, 2.8);
    cpu.Run();
    cpu.setRank(P5);
    cpu.setVoltage(3.0);
    cpu.setFrequency(200);
    cout << "CPU的频率是:" << cpu.getFrequency() << endl;
    cpu.Stop(); 
    return 0;
}

