#include <iostream>
#include <chrono>
#include <string>
#include <random>
#include <thread>

using namespace std;
int food = 3;
string foodBar[4] = {"-","- -","- - -","- - - -"};
int i;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dis(10, 45);

void foodBarTimer() {
    this_thread::sleep_for(chrono::seconds(dis(gen)));
    food--;
}

void feedKey() {
// find a way to get key input
}

int main() {
    thread(foodBarTimer).detach();
    while (i <= 240) {
        system("clear");
        cout << "*_*" << endl;
        cout << endl<<"[F]Feed" << endl;
        cout << endl<<"Food:"<<foodBar[food]<<endl;
        // implement key input scan
        this_thread::sleep_for(chrono::milliseconds(250));

        system("clear");
        cout << "-_-" << endl;
        cout << endl<<"[F]Feed" << endl;
        cout << endl<<"Food:"<<foodBar[food]<<endl;
        // implement key input scan
        this_thread::sleep_for(chrono::milliseconds(250));
    }
}
