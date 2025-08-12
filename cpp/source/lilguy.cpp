#include <iostream>
#include <chrono>
#include <string>
#include <random>
#include <thread>
#include <ncurses.h>
#include <atomic>

using namespace std;
atomic<int> food(4);
atomic<int> emotionSet(2);
string foodBar[5] = {" ","-", "- -", "- - -", "- - - -"};
string emotion[3] = {";_;","*_*","^_^"};
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

void emotionEval() {
    while (true) {
        switch(food) {
        case 0:
            emotionSet = 0;
            break;
        case 1:
            emotionSet = 0;
            break;
        case 2:
            emotionSet = 1;
            break;
        case 3:
            emotionSet = 1;
            break;
        case 4:
            emotionSet = 2;
            break;
        }
    }
}



void deathCheck() {
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
    thread(deathCheck).detach();
    thread(emotionEval).detach();

    while (true) {
        ch = getch();

        if (ch == 'f' && food < 4) {
            food++;
        }

        clear();
        mvprintw(0, 0, emotion[emotionSet].c_str());
        mvprintw(4, 0, "[F]Feed");
        mvprintw(6, 0, "Food: %s", foodBar[food].c_str());
        refresh();
        this_thread::sleep_for(chrono::milliseconds(250));

        ch = getch();

        if (ch == 'f' && food < 4) {
            food++;
        }

        clear();
        mvprintw(0, 0, "-_-");
        mvprintw(4, 0, "[F]Feed");
        mvprintw(6, 0, "Food: %s", foodBar[food].c_str());
        refresh();
        this_thread::sleep_for(chrono::milliseconds(250));
    }
    endwin();
}
