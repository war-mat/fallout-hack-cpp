#ifndef FALLOUT_DISPLAY_H
#define FALLOUT_DISPLAY_H

#include <ncursesw/curses.h>
#include <unistd.h>

#include <string>
#include <vector>

class FalloutDisplay
{
private:
    int line_width_;
    int num_rows_;
    
    // screen coords of right text box
    int right_text_row_ = 20;
    int right_text_col_ = 49;
        
    int right_text_len_ = 28;
    
public:
    FalloutDisplay(int line_width, int num_rows);
    void move_print_string_delay(
            const std::string &str, int col, int row, unsigned int delay);
    void move_print_string_char_dly(
            const std::string &str, int col, int row, unsigned int delay);
    void clear_all(void);
    void print_game_text(
            int first_col, int first_row, const std::string &left_str,
            const std::string &right_str, 
            const std::vector < std::string > &address_list);
    void game_text_update(
            int left_col, int right_col, int first_row, 
            const std::string &left_str,
            const std::string &right_str);
    void print_attempts(int attempts);
};

#endif
