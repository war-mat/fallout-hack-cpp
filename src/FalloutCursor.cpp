#include "../include/FalloutCursor.h"

// constructor
FalloutCursor::FalloutCursor(
        int initial_y, int initial_x, int row_start, int line_width, 
        int num_rows, int left_text_start, int right_text_start)
{
    cursor_y_ = initial_y;
    cursor_x_ = initial_x;
    
    row_start_ = row_start;
    row_end_ = row_start_ + num_rows - 1;
    
    line_width_ = line_width;
    num_rows_ = num_rows;
    
    left_lower_ = left_text_start;
    right_lower_ = right_text_start;
    left_upper_ = left_lower_ + line_width_ - 1;
    right_upper_ = right_lower_ + line_width_ - 1;
    
    // get which column cursor is currently on
    get_side();
}

void FalloutCursor::move_left(void)
{
    cursor_x_ -= 1;
    
    if ((cursor_x_ < right_lower_) && (cursor_x_ > left_upper_))
    {
        cursor_x_ = left_upper_; // skip over center
    }
    else if (cursor_x_ < left_lower_)
    {
        cursor_x_ = left_lower_; // set to left edge
    }
}

void FalloutCursor::move_right(void)
{
    cursor_x_ += 1;
    
    if ((cursor_x_ > left_upper_) && (cursor_x_ < right_lower_))
    {
        cursor_x_ = right_lower_;
    }
    else if (cursor_x_ > right_upper_)
    {
        cursor_x_ = right_upper_;
    }
}

void FalloutCursor::move_up(void)
{
    if (cursor_y_ > row_start_)
    {
        cursor_y_ -= 1;
    }
}

void FalloutCursor::move_down(void)
{
    if (cursor_y_ < row_end_)
    {
        cursor_y_ += 1;
    }
}

// this could be made to not return anything, just alter side_
std::string FalloutCursor::get_side(void)
{    
    return side_;
}

int FalloutCursor::get_cursor_y(void)
{
    return cursor_y_;
}

int FalloutCursor::get_cursor_x(void)
{
    return cursor_x_;
}

void FalloutCursor::handle_arrow_keys(int key)
{
    switch (key)
    {
        case KEY_LEFT:
            move_left();
            break;
        case KEY_RIGHT:
            move_right();
            break;
        case KEY_UP:
            move_up();
            break;
        case KEY_DOWN:
            move_down();
            break;
    }
    
    // update text column side
    set_side();
    
    // move cursor to new position
    update_cursor_pos();
}

void FalloutCursor::set_side(void)
{
    if (cursor_x_ > left_upper_)
    {
        side_ = "right";
    }
    else
    {
        side_ = "left";
    }
}

void FalloutCursor::update_cursor_pos(void)
{
    move(cursor_y_, cursor_x_);
}

/*
def handle_arrow_keys(self, key):
        
        if key == curses.KEY_LEFT:
            self.move_left()
        elif key == curses.KEY_RIGHT:
            self.move_right()
        elif key == curses.KEY_UP:
            self.move_up()
        elif key == curses.KEY_DOWN:
            self.move_down()
        
        # check which column cursor is on
        self.side = self.get_side()
        
        # move cursor to new position
        self.update_cursor_pos()
*/

// go through all files and convert row/col to y/x coords
