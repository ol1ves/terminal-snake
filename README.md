# terminal-snake

Minimal snake game in the terminal. Built as a personal playground to mess around with C++ and different programming paradigms.

**Platform:** macOS / Linux (requires ncurses)

## Build & Run

```bash
make run
```

Or separately:

```bash
make          # builds to build/terminal-snake
./build/terminal-snake
```

## Controls

| Key | Action |
|-----|--------|
| `W` / `↑` | Up |
| `S` / `↓` | Down |
| `A` / `←` | Left |
| `D` / `→` | Right |
| `Q` | Quit |

## Dependencies

- `ncurses` — usually pre-installed on macOS/Linux. If not:
  ```bash
  # macOS
  brew install ncurses

  # Debian/Ubuntu
  sudo apt install libncurses-dev
  ```
