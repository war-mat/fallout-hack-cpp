#ifndef FALLOUT_CURSOR_H
#define FALLOUT_CURSOR_H

#include <ncursesw/curses.h>

#include <string>

class FalloutCursor
{
private:
    // cursor position
    int cursor_y_;
    int cursor_x_;
    
    int row_start_;
    int row_end_;
    int col_start_;
    
    int line_width_;
    int num_rows_;
    
    // text column left to right bounds
    int left_lower_;
    int right_lower_;
    int left_upper_;
    int right_upper_;
    
    std::string side_;
    
public:
    FalloutCursor(
            int initial_y, int initial_x, int row_start, int col_start,
            int line_width, int num_rows, int left_col_start, 
            int right_col_start);
    void move_left(void);
    void move_right(void);
    void move_up(void);
    void move_down(void);
    std::string get_side(void);
};

#endif
