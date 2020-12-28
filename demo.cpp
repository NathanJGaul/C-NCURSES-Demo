#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

# define ITERMAX 10000

int main(int argc, char const *argv[])
{
    long iter;
    int yi, xi;
    int y[3], x[3];
    int index;
    int maxlines, maxcols;
    clock_t prevTime = clock();
    auto drawPerSec = 10000;
    auto delay = static_cast<clock_t>(CLOCKS_PER_SEC/drawPerSec);

    // Initialize ncurses

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    endwin();
    clear();

    // initialize triangle

    maxlines = LINES - 1;
    maxcols = COLS - 1;

    y[0] = 0;
    x[0] = 0;

    y[1] = maxlines;
    x[1] = maxcols / 2;

    y[2] = 0;
    x[2] = maxcols;

    mvaddch(y[0], x[0], '0');
    mvaddch(y[1], x[1], '1');
    mvaddch(y[2], x[2], '2');

    // initialize yi,xi with random values

    yi = std::rand() % maxlines;
    xi = std::rand() % maxcols;

    mvaddch(yi, xi, '.');

    for (iter = 0; iter < ITERMAX; iter++)
    {
        index = std::rand() % 3;

        yi = (yi + y[index]) / 2;
        xi = (xi + x[index]) / 2;

        mvaddch(yi, xi, '*');
        refresh();
        
        while (clock() < (prevTime + delay))
        {

        }
        prevTime = clock();
    }

    // done

    mvaddstr(maxlines, 0, "Press any key to quit");

    refresh();

    getch();
    endwin();

    std::exit(0);

    return 0;
}
