#include "../include/FalloutDisplay.h"

// constructor
FalloutDisplay::FalloutDisplay(int line_width, int num_rows)
{
    line_width_ = line_width;
    num_rows_ = num_rows;
}

/**
Print string to screen with a delay after entire line is printed
**/

void FalloutDisplay::move_print_string_delay(
        const std::string &str, int col, int row, unsigned int delay)
{
    // convert microseconds to milliseconds
    delay *= 1000;
    
    move(row, col);
    
	for(char ch : str)
	{
		addch(ch);
	}
    
    if (delay > 0)
    {
        refresh();
        usleep(delay);
    }
    else
    {
        refresh();
    }
}

/**
Print string to screen with a delay after each character
**/
void FalloutDisplay::move_print_string_char_dly(
        const std::string &str, int col, int row, unsigned int delay)
{
    // convert microseconds to milliseconds
    delay *= 1000;
    
    move(row, col);
    
	for(char ch : str)
	{
		addch(ch);
        refresh();
        usleep(delay);
	}
}

void FalloutDisplay::clear_all(void)
{
    std::string clear = std::string(78, ' ');
    
    for (int i = 1; i < 23; i++)
    {
        move_print_string_delay(clear, 1, i, 0);
    }
}

void FalloutDisplay::print_game_text(
        int first_col, int first_row, const std::string &left_str,
        const std::string &right_str, 
        const std::vector < std::string > &address_list)
{
    int start;
    
    for (int i = 0; i < num_rows_; i++)
    {
        // substring start index
        start = i * line_width_;
        
        // concatenate address i, left text i, address i+num_rows, right text i
        std::string row_str = address_list[i] + " " + 
                left_str.substr(start, line_width_) + "  " + 
                address_list[(i + num_rows_)] + " " +
                right_str.substr(start, line_width_);
                
        move_print_string_delay(row_str, 1, (i + 6), 50);
    }
}

void FalloutDisplay::game_text_update(
        int left_col, int right_col, int first_row, const std::string &left_str,
        const std::string &right_str)
{
    int start;
    
    for (int i = 0; i < num_rows_; i++)
    {
        // substring start index
        start = i * line_width_;
        
        move_print_string_delay(
                left_str.substr(start, line_width_), left_col, (i + 6), 0);
        move_print_string_delay(
                right_str.substr(start, line_width_), right_col, (i + 6), 0);
    }
}

void FalloutDisplay::print_attempts(int attempts, int delay_ms)
{
    cchar_t block_char;
    
    setcchar(&block_char, L"█ ", 0, COLOR_PAIR(1), NULL);
    
    std::string out = std::to_string(attempts) + " ATTEMPT(S) LEFT: ";
    
    // position needs to be made adjustable
    move_print_string_char_dly(out, 1, 4, delay_ms);
    
    for (int i = 0; i < (attempts * 2); i+= 2)
    {
        mvadd_wch(4, 20 + i, &block_char);
        usleep((delay_ms * 1000));
        refresh();
    }
}
