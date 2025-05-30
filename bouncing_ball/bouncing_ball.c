#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

struct ball {
  int x, y;   // coordinates
  int px, py; // previous coords
  int dx, dy; // direction
} ball;

int main(int argc, char *argv[]) {
  int input;
  int rows, cols;

  srand(time(NULL));

  ball.dx = 1;
  ball.dy = 1;

  initscr(); // init curses
  raw();
  curs_set(0); // set cursor invisible
  timeout(0);
  noecho();

  getmaxyx(stdscr, rows, cols);
  ball.y = rows / 2;
  ball.x = cols / 2;

  while ((input = getch()) != 'q') {
    usleep(40000); 
    getmaxyx(stdscr, rows, cols);
    if (ball.y == rows - 1|| ball.y == 0)
      ball.dy *=  -1;
    if (ball.x == cols - 1|| ball.x == 0)
      ball.dx *=  -1;

    ball.px = ball.x;
    ball.py = ball.y;
    ball.x += ball.dx;
    ball.y += ball.dy;

    mvprintw(0, 0, "            ");
    mvprintw(0, 0, "x:%d\ty:%d", ball.x, ball.y);
    mvprintw(ball.py, ball.px, " ");
    mvprintw(ball.y, ball.x, "#");
    refresh();
  }

  endwin();

  return EXIT_SUCCESS;
}
