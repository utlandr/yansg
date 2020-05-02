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
    halfdelay(1);
    noecho();

    // Initialize the windows and scoreboard
    struct GAME_SCREEN g_win = init_game();
    int user_in, x, y;
    char snake_dir = 'N'; 

    // Retrieve random start point
    rand_coords(g_win.map_window, &y, &x);    

    // Initialize the snake
    struct SNAKE* g_snake = init_snake(g_win.map_window, y, x, SNAKE_START_LEN);

    // Snake movement and coloring TODO: Maybe put in a method/something better
    keypad(g_win.map_window, TRUE);
    nodelay(g_win.map_window, TRUE);
    init_pair(1, COLOR_BLACK, COLOR_RED);
    init_pair(2, COLOR_BLACK, COLOR_YELLOW);
    wattron(g_win.map_window, COLOR_PAIR(1));

    do {
        user_in = wgetch(g_win.map_window);

		switch(user_in){
            case KEY_UP:
                snake_dir = 'U';
                break;

			case KEY_DOWN:
                snake_dir = 'D';
				break;

			case KEY_LEFT:
                snake_dir = 'L';
                break;

            case KEY_RIGHT:
                snake_dir = 'R';
                break;
        }
        
        switch(snake_dir) {
            case 'N':
                break;

            case 'U':
                y--;
                break;

            case 'D':
                y++;
                break;

            case 'L':
                x-=2;
                break;

            case 'R':
                x+=2;
                break;
        }

        // update snake position
        mvwprintw(g_win.map_window, 0, 0, "%i is x and %i is y", x, y);
        snake_movement_update(g_snake, y, x);

    } while(1);
    wattroff(g_win.map_window, COLOR_PAIR(1));

    endwin(); //de-allocate and end ncurses
    return(0);
}
