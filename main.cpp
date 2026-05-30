/**
 * Terminal Snake Game 
 * @author Oliver Santana
 * 
 * A simple terminal based snake game for me learn and experiment.
 */

#include <ncurses.h>
#include <random>
#include <chrono>
#include <thread>

/**
 * @brief Simple 2D vector struct
 */
struct Vec2 {
    int x;
    int y;

    /**
     * @brief Adds another Vec2 to this Vec2 in-place.
     * @param rhs The right-hand side Vec2 to add to this Vec2.
     * @return A reference to this Vec2 after addition.
     */
    Vec2& operator+=(const Vec2& rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
};

int main() {
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    clear();
    nodelay(stdscr, TRUE);

    // Get terminal dimensions
    int maxX = COLS / 2 - 1;
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
        mvaddch(applePos.y, applePos.x * 2, '@');
        mvaddch(headPos.y, headPos.x * 2, '*');
        headPos += direction; 
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

        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
    endwin();
    return 0;
}
