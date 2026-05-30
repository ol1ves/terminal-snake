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

    // Get terminal dimensions
    int maxX = COLS - 1;
    int maxY = LINES - 1;

    // Initialize rng
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist_x(1, maxX);
    std::uniform_int_distribution<> dist_y(1, maxY);

    // Initialize game state
    Vec2 applePos = { dist_x(gen), dist_y(gen) };
    Vec2 headPos = { maxX / 2, maxY / 2 };
    Vec2 direction = { 1, 0 };

    // Game loop
    while (true) {
        // Draw game state
        clear();
        mvaddch(applePos.y, applePos.x, '@');
        mvaddch(headPos.y, headPos.x, '*');
        headPos.x += direction.x * 2;
        headPos.y += direction.y;
        refresh();

        // Drain input buffer
        int ch;
        int last = ERR;
        while ((ch = getch()) != ERR) {
            last = ch;
        }
        // Update direction
        if (last != ERR) {
            switch (last) {
                case 'w': direction = { 0, -1 }; break;
                case 's': direction = { 0, 1 }; break;
                case 'a': direction = { -1, 0 }; break;
                case 'd': direction = { 1, 0 }; break;
            } 
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    endwin();
    return 0;
}
