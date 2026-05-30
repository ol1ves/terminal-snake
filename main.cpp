/**
 * @file main.cpp
 * @author Oliver Santana
 * @brief Main entry point for the Snake game.
 */

#include <ncurses.h>
#include <random>
#include <chrono>
#include <thread>
#include "util.h"

int main() {
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    clear();
    nodelay(stdscr, TRUE);

    int maxX = COLS - 1;
    int maxY = LINES - 1;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist_x(1, maxX);
    std::uniform_int_distribution<> dist_y(1, maxY);

    Vec2 applePos = { dist_x(gen), dist_y(gen) };
    Vec2 headPos = { maxX / 2, maxY / 2 };
    Vec2 direction = { 1, 0 };

    while (true) {
        clear();
        mvaddch(applePos.y, applePos.x, '@');
        mvaddch(headPos.y, headPos.x, '*');
        headPos += direction;
        refresh();

        
        int ch = getch();
        if (ch != ERR) {
            switch (ch) {
                case 'w': direction = { 0, -1 }; break;
                case 's': direction = { 0, 1 }; break;
                case 'a': direction = { -1, 0 }; break;
                case 'd': direction = { 1, 0 }; break;
            } 
        }
        
        timeout(100);
        }
    endwin();
    return 0;
}
