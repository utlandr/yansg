#include <ncurses.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

// I'm gonna be wrong and say that this is how one should setup config
// global variables for a game
char TITLE[]=" Yet Another Snake Game ";     // Game title
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


typedef struct SNAKE {
    int id;
    WINDOW* body;
    struct SNAKE* next;
} snake;

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

int get_int_from_range(int l_bound, int u_bound) {
    srand(time(0));
    int rand_int = (rand() % (u_bound - l_bound + 1)) + l_bound;
    return(rand_int);
}

void rand_coords(WINDOW* win, int* y_start, int* x_start) {
    int x_max, y_max;
    getmaxyx(win, y_max, x_max);
    
    int y_rand = get_int_from_range(1, y_max-1);
    int x_rand = get_int_from_range(1, x_max-1);
    
    *y_start = y_rand;
    *x_start = x_rand;
}
