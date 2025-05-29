#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

struct ball {
  int x, y;   // coordinates
  int dx, dy; // direction
} ball;

int main(int argc, char *argv[]) {
  int input;
  int rows, cols;

  ball.dx = 1;
  ball.dy = 0;

  initscr(); // init curses
  raw();
  curs_set(0); // set cursor invicible
  halfdelay(1);
  noecho();

  getmaxyx(stdscr, rows, cols);
  ball.y = rows / 2;
  ball.x = cols / 2;

  while ((input = getch()) != 'q') {
    switch (input) {
    case 'w':
      ball.dy = -1;
      ball.dx = 0;
      break;
    case 's':
      ball.dy = 1;
      ball.dx = 0;
      break;
    case 'a':
      ball.dx = -1;
      ball.dy = 0;
      break;
    case 'd':
      ball.dx = 1;
      ball.dy = 0;
      break;
    default:
      break;
    }

    getmaxyx(stdscr, rows, cols);
    if (ball.y > rows) {
      ball.y = 0 ;
    }else if (ball.y < 0) {
      ball.y = rows;
    }
    if (ball.x > cols) {
      ball.x = 0 ;
    }else if (ball.x < 0) {
      ball.x = cols;
    }
    ball.x += ball.dx;
    ball.y += ball.dy;

    clear();
    mvprintw(ball.y, ball.x, "*");
    mvprintw(0, 0, "x:%d\ty:%d", ball.x, ball.y);
    refresh();
  }

  endwin();

  return EXIT_SUCCESS;
}
