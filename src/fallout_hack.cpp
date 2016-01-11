// this needs it's own header file or something

#include "../include/FalloutGame.h"

void close_curses(void)
{
    nocbreak();
    curs_set(1);
    endwin();
}

void open_curses(void)
{
    initscr();
        
    cbreak();
    curs_set(0);
        
    start_color();
        
    use_default_colors();
    
    init_pair(1, 47, COLOR_BLACK);
        
    attron(COLOR_PAIR(1));
    attron(A_BOLD);
        
    border(ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER,
            ACS_LLCORNER, ACS_LRCORNER);
}

int main()
{	
    setlocale(LC_ALL, "en_US.UTF-8");
    
    // attempt to set $TERM to 256 color mode, exit if failure
    // or maybe just revert to 8-color mode
    if (setenv("TERM", "xterm-256color", 1) != 0)
    {
        exit(1);
    }
    
    try 
    {
        open_curses();
        
        FalloutGame game = FalloutGame();
        
        //game.test_run();
        
        game.new_game(1);

        game.play_game();
        
        int ch;
        
        ch = wgetch(stdscr);
    

    }
    catch (...)
    {
        // close ncurses
        close_curses();
    }

    close_curses();
    
    return 0;
}

