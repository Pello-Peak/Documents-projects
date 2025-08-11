#include <iostream>
#include <chrono>
#include <string>
#include <random>
#include <thread>
#include <ncurses.h>
#include <atomic>

using namespace std;
atomic<int> food(4);
string foodBar[5] = {" ","-", "- -", "- - -", "- - - -"};
char ch = '\0';
bool timerAct = true;

void foodBarTimer() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(10, 45);

    while (true) {
        this_thread::sleep_for(chrono::minutes(dis(gen)));
        food--;
    }
}

void death() {
    while (true) {
        if (food <= 0) {
            endwin();
            cout << "You killed your son..." << endl;
            exit(0);
        }
    }
}

int main() {

    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);

    thread(foodBarTimer).detach();
    thread(death).detach();

    while (true) {
        ch = getch();

        if (ch == 'f' && food < 4) {
            food++;
        }

        clear();
        mvprintw(0, 0, "*_*");
        mvprintw(2, 0, "[F]Feed");
        mvprintw(4, 0, "Food: %s", foodBar[food].c_str());
        refresh();
        this_thread::sleep_for(chrono::milliseconds(250));

        ch = getch();

        if (ch == 'f' && food < 4) {
            food++;
        }

        clear();
        mvprintw(0, 0, "-_-");
        mvprintw(2, 0, "[F]Feed");
        mvprintw(4, 0, "Food: %s", foodBar[food].c_str());
        refresh();
        this_thread::sleep_for(chrono::milliseconds(250));
    }
    endwin();
}
