#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <time.h>

// I'm gonna be wrong and say that this is how one should setup config
// global variables for a game
char TITLE[] = " Yet Another Snake Game ";     // Game title
int SCOREBOARD_LEN = 4;                     // Absolute scoreboard length

int START_X = 0;                            // Main window start x
int START_Y = 0;                            // Main window start y
int EDGE = 0;                               // Main window edge char
int CORN = (int)'*';                        // Main window corner char

int G_EDGE = 0;                             // Game window edge char
int G_CORN = (int)'*';                      // Game window corner char

int SNAKE_START_LEN = 3;

// Game screen windows
struct GAME_SCREEN {
    WINDOW* main_window;
    WINDOW* game_window;
    WINDOW* map_window;
};

// Snake 
struct SNAKE {
    int id;
    int y_pos;
    int x_pos;
    WINDOW* body;
    struct SNAKE* next;
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

    return(g_win) ;

}

// sub method for generatin random start positions
int get_int_from_range(int l_bound, int u_bound) {
    srand(time(0));
    int rand_int = (rand() % (u_bound - l_bound + 1)) + l_bound;
    return(rand_int);
}

void rand_coords(WINDOW* win, int* y_start, int* x_start) {
    int x_max, y_max, x_rand, y_rand;
    getmaxyx(win, y_max, x_max);
    
    y_rand = get_int_from_range(1, y_max-1);
    x_rand = get_int_from_range(1, x_max-1);
    
    *y_start = y_rand;
    *x_start = x_rand;
}

struct SNAKE* init_snake(WINDOW* game_win, int y_start, int x_start, int start_len) {
    struct SNAKE* head;
    struct SNAKE* main;
    struct SNAKE* conveyor;
    
    // Create the head
    main = (struct SNAKE*)malloc(sizeof(struct SNAKE));
    head = main;

    // I think I am being naughty here as I haven't been
    // able to find a creditable source online in which 
    // someone has created a linked list from a for loop. 
    // Might have to do with the fact that 
    // anyone could change the 'start_len' to some atrocious
    // number which might lead to memory overflow. 
    for(int i=1; i<start_len; i++) {
        conveyor = (struct SNAKE*)malloc(sizeof(struct SNAKE));
        main->id = i;
        main->y_pos = y_start;
        main->x_pos = x_start + 2*i;
        main->body = subwin(game_win, 1, 2, y_start, x_start + 2*i); 
        wattron(main->body, COLOR_PAIR(1));
        main->next = conveyor;

        main = main->next;
    }
    return head;
}
