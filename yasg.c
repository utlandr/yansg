#include <stdlib.h>
#include <ncurses.h>
#include "yasg.h"

int main(void) {
    initscr(); //set up memory and clear screen
    
    // Init colors if possible
    if (has_colors() == FALSE) {
        endwin();
        printf("Your terminal does not support color\n");
        exit(1);

    } else {
        start_color();
        use_default_colors();
    }

    curs_set(0);
    cbreak();
    noecho();

    // Initialize the windows and scoreboard
    struct GAME_SCREEN g_win = init_game();
    int c, x, y;
    rand_coords(g_win.map_window, &y, &x);    
    
    // Snake movement and coloring
    keypad(g_win.map_window, TRUE);
    nodelay(g_win.map_window, TRUE);
    init_pair(1, COLOR_BLACK, COLOR_RED);
    wattron(g_win.map_window,COLOR_PAIR(1));

    do {
        mvwprintw(g_win.map_window, 0, 0, "%i is x and %i is y", x, y);
        wrefresh(g_win.map_window);
        c = wgetch(g_win.map_window);

		switch(c){
            case KEY_UP:
                y--;
                break;

			case KEY_DOWN:
                y++;
				break;

			case KEY_LEFT:
                x-=2;
                break;

            case KEY_RIGHT:
                x+=2;
                break;
        }
        mvwprintw(g_win.map_window,y,x,"  ");
    } while(1);
    wattroff(g_win.map_window, COLOR_PAIR(1));

    endwin(); //de-allocate and end ncurses
    return(0);
}
