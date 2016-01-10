#include "../include/FalloutCursor.h"

// constructor
FalloutCursor::FalloutCursor(
        int initial_y, int initial_x, int row_start, int col_start,
        int line_width, int num_rows, int left_col_start, int right_col_start)
{
    cursor_y_ = initial_y;
    cursor_x_ = initial_x;
    
    row_start_ = row_start;
    row_end_ = row_start_ + num_rows - 1;
    col_start_ = col_start;
    
    line_width_ = line_width;
    num_rows_ = num_rows;
    
    left_lower_ = left_col_start;
    right_lower_ = right_col_start;
    left_upper_ = left_lower_ - 1;
    right_upper_ = right_lower_ - 1;
    
    // get which column cursor is currently on
    side_ = get_side();
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

std::string FalloutCursor::get_side(void)
{
    std::string side;
    
    if (cursor_x_ < right_lower_)
    {
        side = "left";
    }
    else
    {
        side = "right";
    }
    
    return side;
}

// go through all files and convert row/col to y/x coords
