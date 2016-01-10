#include "../include/FalloutGame.h"

// constructor
FalloutGame::FalloutGame(int curr_level)
{
    curr_level_ = curr_level;
    
    // initialize game words object
    words_ = FalloutWords("/usr/share/dict/words");
    
    set_game_word_params();
    
    words_.new_game(8, 15, 4);
}

void FalloutGame::report_values(void)
{
    std::cout << curr_level_ << std::endl;
    std::cout << word_length_ << std::endl;
    std::cout << num_words_ << std::endl;
    std::cout << match_limit_ << std::endl;
    
    text_.report_values();
    words_.report_values();
}

void FalloutGame::set_game_word_params(void)
{
    word_length_ = levels[curr_level_][0];
    num_words_ = levels[curr_level_][1];
    match_limit_ = levels[curr_level_][2];
}

void FalloutGame::test_run(void)
{
    display.clear_all();
    
    display.move_print_string_char_dly(text_.get_top_text("logo"), 1, 1, 25);
    display.move_print_string_char_dly(text_.get_top_text("command"), 1, 2, 25);
    
    display.print_attempts(3);
    
    display.print_game_text(
            1, 6, text_.get_left_right_text("left"), 
            text_.get_left_right_text("right"), text_.get_address_list());
}
