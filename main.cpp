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

    /**
     * @brief Checks if this Vec2 is equal to another Vec2.
     * @param rhs The right-hand side Vec2 to compare with this Vec2.
     * @return true if both Vec2s have the same x and y values, false otherwise.
     */
    bool operator==( const Vec2& rhs ) const {
        return x == rhs.x && y == rhs.y;
    }
};

/**
 * @brief Generates a random position for apple that is not occupied by snake.
 * 
 * Repeadedly generates random positions until it finds one that is not occupied 
 * by the snake.
 * 
 * @param gen The random number generator to use for generating random numbers.
 * @param dist_x The uniform distribution for generating x coordinates.
 * @param dist_y The uniform distribution for generating y coordinates.
 * @param snake The current positions of the snake segments.
 * @return A Vec2 representing a valid position for the apple.
 */
Vec2 genApplePos(
    std::mt19937& gen, 
    std::uniform_int_distribution<>& dist_x, 
    std::uniform_int_distribution<>& dist_y, 
    const std::vector<Vec2>& snake
) {
    Vec2 pos;
    bool valid;
    // Generate positions until one is valid
    do {
        pos = { dist_x(gen), dist_y(gen) };
        valid = true;
        // Check all snake segments for collision with generated position
        for (const Vec2& segment : snake) {
            if (pos == segment) {
                valid = false;
                break;
            }
        }
    } while (!valid);
    return pos;
}

int main() {
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    clear();
    nodelay(stdscr, TRUE);

    // Get terminal dimensions
    int MAX_X = COLS / 2 - 1;
    int MAX_Y = LINES - 1;

    // Initialize rng
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist_x(1, MAX_X);
    std::uniform_int_distribution<> dist_y(1, MAX_Y);

    // Initialize game state
    std::vector<Vec2> snake = { Vec2{MAX_X / 2, MAX_Y / 2} };
    Vec2 applePos = { dist_x(gen), dist_y(gen) };
    Vec2 direction = { 1, 0 };
    int score = 0;

    // Game loop
    while (true) {
        // Drain input buffer get most recent input
        int input = []() -> int {
            int in, out;
            while ((in = getch()) != ERR) {
                out = in; 
            }
            return out;
        }();

        /*
            Update state
        */
        // Update direction
        if (input != ERR) {
            switch (input) {
                case 'w': direction = { 0, -1 }; break;
                case 's': direction = { 0, 1 }; break;
                case 'a': direction = { -1, 0 }; break;
                case 'd': direction = { 1, 0 }; break;
            } 
        }
        // Tick
        snake[0] += direction;
        // Out of bounds check
        if (snake[0].x < 1 || snake[0].x > MAX_X || 
            snake[0].y < 1 || snake[0].y > MAX_Y) 
        {
            break;
        }

        // Draw game state
        clear();
        mvaddch(applePos.y, applePos.x * 2, '@');
        mvaddch(snake[0].y, snake[0].x * 2, '*');
        refresh();

        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    } // Game over
    clear();
    mvaddstr(LINES / 2, (COLS - 9) / 2, "Game Over");
    refresh();
    nodelay(stdscr, FALSE);
    getch();
    endwin();
    return 0;
}
