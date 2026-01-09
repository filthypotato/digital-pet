/* main.cpp
   Example usage with TODOs for building a game
*/
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>
#include <algorithm>
#include "ncurses_app.hpp"
#include <ncurses.h>

struct Player {
  int x{}, y{};
  size_t health{};
  char symbol{'P'};

  void move(int dx, int dy);

  void attack(int dmg);
};

struct Enemy {
  int x{}, y{};
  size_t health{};
  char symbol{'E'};
  bool isAlive{};
};

struct GameState {
  Player player{};
  std::vector<Enemy> enemies{};

  bool isGameOver{false};
  bool collides(const Player& p, const Enemy& e);

  void triggerGameOver();
  void drawGameOver();


};

void GameState::triggerGameOver() {
  isGameOver = true;
}

void GameState::drawGameOver() {
  clear();

  int rows{}, cols{};
  getmaxyx(stdscr, rows, cols);

  const char* msg = "GAME OVER lil bug :(";

  int x = (cols - (int)strlen(msg)) / 2;
  int y = rows / 2;

  mvprintw(y, x, "%s", msg);
  mvprintw(y + 2, x - 6, "Press any key to quit.");
  refresh();

  nodelay(stdscr, FALSE); // blocks input
  getch();
}

void Player::move(int dx, int dy) {
  x += dx;
  y += dy;
}

bool collision(const Player& p, const Enemy& e) {
  return p.x == e.x && p.y == e.y && e.isAlive;
}

const int PLAYER_START_X{10};
const int PLAYER_START_Y{10};

const int ENEMY_START_X{12};
const int ENEMY_START_Y{12};




// TODO: Add helper functions for game logic
// Example: void updateEnemies(std::vector<Enemy>& enemies) { ... }
// Example: bool checkCollision(Player& player, Enemy& enemy) { ... }

int main() {
    NcursesApp app;
    app.init();

    GameState state{};
    state.player = {PLAYER_START_X, PLAYER_START_Y, 10, 'P'};

    // creates enemies here
    state.enemies.emplace_back(
        ENEMY_START_X,
        ENEMY_START_Y,
        3,
        'E',
        true
  );




    int score{0};
    int level{1};

    while (app.running()) {
        app.beginFrame();

        // Draws game world
        app.drawBorder();

        // Draw player
        mvaddch(state.player.y, state.player.x, state.player.symbol);

        // Draw enemies
       for (auto& enemy : state.enemies) {
         if (enemy.isAlive) mvaddch(enemy.y, enemy.x, enemy.symbol);
       }



        // Draw UI elements (score, lives, etc.)
        mvprintw(1, 2, "Score: %d", score);
        mvprintw(1, 20, "Level: %d", level);

        app.drawCenteredText(5, "Game Day Comes Once A Year");
        app.drawCenteredText(7, "Press Q to quit");

        // Handle input for game controls
        int ch = app.pollInput();

        switch (ch) {
          case 'w':
          case 'W':
            state.player.move(0, -1);
            break;

          case 's':
          case 'S':
            state.player.move(0, 1);
            break;

          case 'a':
          case 'A':
            state.player.move(-1, 0);
            break;

          case 'd':
          case 'D':
            state.player.move(1, 0);
            break;
          case 'q':
          case 'Q':
            app.stop();
            break;
        }

        // Clamp player movement so does not draw off screen
        state.player.x = std::max(1, std::min(state.player.x, COLS - 2));
        state.player.y = std::max(1, std::min(state.player.y, LINES - 2));



        // updates new enemies
        // here



        // Updates game logic

        // collision checks
        for (auto& e : state.enemies) {
          if (collision(state.player, e)) {
            state.triggerGameOver();
            break;
          }
        }

        if (state.isGameOver) {
          state.drawGameOver();
          break;
        }

        // TODO:
        // Example: updateEnemies(enemies);
        // Example: spawnNewEnemies();
        // Example: updateProjectiles();



        // TODO: Check win/lose conditions
        if (state.player.health <= 0) { state.isGameOver = false; }
        //if (enemies.empty()) { nextLevel(); }
        app.endFrame();
    }

    // TODO: Show final score or game over screen
    clear();
    mvprintw(LINES/2, COLS/2 - 10, "Final Score: %d", score);
    refresh();
    getch();

    return 0;
}
