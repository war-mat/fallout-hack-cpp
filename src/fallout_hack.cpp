#define _XOPEN_SOURCE_EXTENDED

#include <locale.h>
#include <ncursesw/curses.h>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include <map>
#include <vector>
#include "../include/FalloutGame.h"

void move_print_str(const std::string &str, int y, int x)
{
    move(y, x);
    
	for(char ch : str)
	{
		addch(ch);
	}
}

void move_print_str_char_dly(const std::string &str, int y, int x, unsigned int delay)
{
    // convert microseconds to milliseconds
    delay *= 1000;
    
    move(y, x);
    
	for(char ch : str)
	{
		addch(ch);
        refresh();
        usleep(delay);
	}
}

void clear_all(void)
{
    std::string clear = std::string(78, ' ');
    
    for (int i = 1; i < 23; i++)
    {
        move_print_str(clear, i, 1);
    }
}

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
    
    FalloutGame game = FalloutGame(0);
    
    game.report_values();
    
    try 
    {
        open_curses();
        
        clear_all();

        int per_char_delay = 20;
        
        //std::map <std::string, std::string> msg_map;
        std::map <std::string, std::string> msg_map = {
                {"logo", "ROBCO INDUSTRIES (TM) TERMLINK PROTOCOL"},
                {"command", "ENTER PASSWORD NOW"}
                };
        
        //msg_map["logo"] = "ROBCO INDUSTRIES (TM) TERMLINK PROTOCOL";
        
        std::string msg = "ROBCO INDUSTRIES (TM) TERMLINK PROTOCOL";
        std::string msg1 = "ENTER PASSWORD NOW";
        cchar_t block_char;
        setcchar(&block_char, L"█ ", 0, COLOR_PAIR(1), NULL);
        
        std::string msg2 = "4 ATTEMPT(S) LEFT: ";
        
        //move_print_str(msg, 1, 1);
        //move_print_str_char_dly(msg, 1, 1, per_char_delay);
        move_print_str_char_dly(msg_map["logo"], 1, 1, per_char_delay);
        //move_print_str(msg1, 2, 1);
        //move_print_str_char_dly(msg1, 2, 1, per_char_delay);
        move_print_str_char_dly(msg_map["command"], 2, 1, per_char_delay);
        //move_print_str(msg2, 4, 1);
        move_print_str_char_dly(msg2, 4, 1, per_char_delay);
        
        for (int i = 0; i < 8; i+= 2)
        {
            mvadd_wch(4, 20 + i, &block_char);
            usleep(20000);
            refresh();
        }
        
        std::string line0 = "0xB722 ;!:=}!\"`*|+'<$|  0xB821 [={|=;>_`{_]\">+";
        std::string line1 = "0xB731 ,`^}_%'%@[<[..=  0xB830 PATROL'@@`]PASS";
        std::string line2 = "0xB740 .^#(\\${|=<\\/=$'  0xB83F EL(|/(CARREL/'|";
        
        move_print_str_char_dly(line0, 6, 1, per_char_delay);
        move_print_str_char_dly(line1, 7, 1, per_char_delay);
        move_print_str_char_dly(line2, 8, 1, per_char_delay);
        
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

