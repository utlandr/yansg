#include <ncurses.h>
#include <string.h>

// I'm gonna be wrong and say that this is how one should setup config
// global variables for a game

char* TITLE=" GAME 'O' SNAKE ";
int SCOREBOARD_WID = 4; 

// Main window placement xy position
int START_X = 0;
int START_Y = 0;

// Main window edge and corner characters
int EDGE = 0;
int CORN = (int)'*';

// Game Window options
int G_EDGE = 0;
int G_CORN = (int)'*';

// Create a window
WINDOW* init_window(int edge, int corn, int start_x, int start_y, int height, int width) {
    WINDOW* win = newwin(height, width, start_x, start_y);
    wborder(win, edge, edge, edge, edge, corn, corn, corn, corn);
    refresh();
    wrefresh(win);
    return(win);
}

// Initialize the game screen 
void init_game(void) {

    // Generate main screen
    int x_max, y_max;
    getmaxyx(stdscr, y_max, x_max);
    WINDOW* main_window = init_window(EDGE, CORN, START_X, START_Y, y_max, x_max);
    
    int x_game_start, y_game_start, game_wid, game_len ;
    x_game_start = 0;
    y_game_start = SCOREBOARD_WID;

    game_wid = x_max;
    game_len = y_max-y_game_start;
    

    // Generate game window
    WINDOW* game_window = init_window(G_EDGE, G_CORN, y_game_start, x_game_start, game_len, game_wid);

    // Title
    char* title = TITLE;
    mvprintw(0, (x_max-strlen(TITLE))/2, TITLE);
}

int main(void) {

    initscr(); //set up memory and clear screen
    curs_set(0);
    cbreak();
    noecho();

    // Initialize the windows and scoreboard
    init_game();



    getch();
    endwin(); //de allocate and end ncurses
    
    return(0);
}
