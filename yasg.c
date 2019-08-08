#include <stdlib.h>
#include <ncurses.h>
#include <string.h>

// I'm gonna be wrong and say that this is how one should setup config
// global variables for a game
char* TITLE=" Yet Another Snake Game ";     // Game title
int SCOREBOARD_LEN = 4;                     // Absolute scoreboard length

int START_X = 0;                            // Main window start x
int START_Y = 0;                            // Main window start y
int EDGE = 0;                               // Main window edge char
int CORN = (int)'*';                        // Main window corner char

int G_EDGE = 0;                             // Game window edge char
int G_CORN = (int)'*';                      // Game window corner char

struct GAME_SCREEN {
    WINDOW* main_window;
    WINDOW* game_window;
    WINDOW* map_window;
};

// Create a window
WINDOW* init_window(int edge, int corn, int start_x, int start_y, int height, int width) {
    WINDOW* win = newwin(height, width, start_x, start_y);
    wborder(win, edge, edge, edge, edge, corn, corn, corn, corn);
    return(win);
}

// Initialize the game screen 
struct GAME_SCREEN init_game() {
    struct GAME_SCREEN g_win;
    // Generate main screen
    int x_max, y_max;
    getmaxyx(stdscr, y_max, x_max);
    g_win.main_window = init_window(EDGE, CORN, START_X, START_Y, y_max, x_max);
    
    // Title
    char* title = TITLE;
    int title_pos = (int)((x_max-strlen(TITLE))/2);
    mvwprintw(g_win.main_window, 0, title_pos, title);
    wrefresh(g_win.main_window);

    // Generate the game map
    int x_game_start, y_game_start, game_wid, game_len ;
    x_game_start = 0;
    y_game_start = SCOREBOARD_LEN;

    game_wid = x_max;
    game_len = y_max-y_game_start;
    
    // Generate game window
    g_win.game_window = init_window(G_EDGE, G_CORN, y_game_start, x_game_start, game_len, game_wid);
    wrefresh(g_win.game_window);

    // Create empty map inside game window
    g_win.map_window = init_window((int)' ', (int)' ', y_game_start + 1, x_game_start + 1, game_len - 2, game_wid - 2); 

    return(g_win);

}

int main(void) {
    initscr(); //set up memory and clear screen

    if (has_colors() == FALSE) {
        endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }
    start_color();
    use_default_colors();
    curs_set(0);
    cbreak();
    noecho();


    // Initialize the windows and scoreboard
    struct GAME_SCREEN g_win = init_game();
    int c, x, y;
    x = y = 10;
    
    init_pair(1, COLOR_RED, COLOR_RED);
    wattron(g_win.map_window,COLOR_PAIR(1));

    keypad(g_win.map_window, TRUE);
    while(1) {
        wrefresh(g_win.map_window);
        c = wgetch(g_win.map_window);
        wclear(g_win.map_window);
		switch(c){
            case KEY_UP:
                y--;
                break;

			case KEY_DOWN:
                y++;
				break;

			case KEY_LEFT:
                x--;
                break;

            case KEY_RIGHT:
                x++;
                break;
                
        }
        mvwprintw(g_win.map_window,y,x," ");
    }
    wattroff(g_win.map_window, COLOR_PAIR(1));

    endwin(); //de-allocate and end ncurses
    
    return(0);
}
