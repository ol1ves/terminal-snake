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
     * @brief Adds two Vec2s together and returns the result.
     * @param rhs The right-hand side Vec2 to add to this Vec2.
     * @param lhs The left-hand side Vec2 to add to the rhs Vec2.
     * @return A new Vec2 that is the sum of this Vec2 and the rhs Vec2.
     */
    Vec2 operator+(const Vec2& rhs) const {
        return { x + rhs.x, y + rhs.y };
    }

    /**
     * @brief Subtracts another Vec2 from this Vec2 and returns the result.
     * @param rhs The right-hand side Vec2 to subtract from this Vec2.
     * @return A new Vec2 that is the difference between this Vec2 and rhs.
     */
    Vec2 operator-(const Vec2& rhs) const {
        return { x - rhs.x, y - rhs.y };
    }

    /**
     * @brief Adds another Vec2 to this Vec2 in-place.
     * 
     * Uses operator+ to perform addition and assigns to self.
     * 
     * @param rhs The right-hand side Vec2 to add to this Vec2.
     * @return A reference to this Vec2 after addition.
     */
    Vec2& operator+=(const Vec2& rhs) {
        *this = *this + rhs;
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

    /**
     * @brief Checks if this Vec2 is not equal to another Vec2.
     * @param rhs The right-hand side Vec2 to compare with this Vec2.
     * @return true if x or y values of the Vec2s differ, othersise false.
     */
    bool operator!=( const Vec2& rhs ) const {
        return !(*this == rhs);
    }

    /**
     * @brief Multiplies this Vec2 by a scalar and returns the result.
     * @param scalar The integer value to multiply this Vec2 by.
     * @return A new Vec2 that is the result of multiplying this Vec2 scalar.
     */
    Vec2 operator*(int scalar) const {
        return { x * scalar, y * scalar };
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

/**
 * @brief Updates the position of the snake based on its direction.
 * @param snake The vector of Vec2 representing the snake's segments.
 * @param headDir The direction in which the snake's head should move.
 */
void tickSnake(std::vector<Vec2>& snake, Vec2& headDir) {
    // Move each segment to the position of the segment in front of it
    Vec2 nextPos = snake[0] + headDir;
    for (size_t i = 0; i < snake.size(); i++) {
        Vec2 currPos = snake[i];
        snake[i] = nextPos;
        nextPos = currPos;
    }
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
    Vec2 applePos = genApplePos(gen, dist_x, dist_y, snake);
    Vec2 headDir = { 1, 0 };
    int score = 0;
    bool gameOver = false;

    // Game loop
    while (!gameOver) {
        // Drain input buffer get most recent input
        int input = []() -> int {
            int in, out = ERR;
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
            Vec2 newDir = headDir;
            switch (input) {
                case 'w': newDir = { 0, -1 }; break;
                case 's': newDir = { 0, 1 }; break;
                case 'a': newDir = { -1, 0 }; break;
                case 'd': newDir = { 1, 0 }; break;
                default: break;
            }

            // Ignore direction opposite current head direction
            if (newDir != headDir * -1) {
                headDir = newDir;
            } 
        }
        // Tick
        tickSnake(snake, headDir);
        // Out of bounds check
        if (snake[0].x < 1 || snake[0].x > MAX_X || 
            snake[0].y < 1 || snake[0].y > MAX_Y) 
        {
            gameOver = true;
            break;
        }
        // Self collision check
        for (size_t i = 1; i < snake.size(); i++) {
            if (snake[0] == snake[i]) {
                gameOver = true;
                break;
            }
        }
        // Apple collision check
        if (snake[0] == applePos) {
            score++;
            // Add new segment at tail
            snake.push_back(snake.back());
            // Generate new apple position
            applePos = genApplePos(gen, dist_x, dist_y, snake);
        }

        // Draw game state
        clear();
        mvaddch(applePos.y, applePos.x * 2, '@');
        for (const Vec2& segment : snake) {
            mvaddch(segment.y, segment.x * 2, '*');
        }
        refresh();

        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    } // Game over
    clear();
    mvprintw(LINES / 2, COLS / 2, "Game Over! Score: %d", score);
    mvprintw(LINES / 2 + 1, COLS / 2, "Press any key to exit.");
    refresh();
    nodelay(stdscr, FALSE);
    getch();
    endwin();
    return 0;
}
