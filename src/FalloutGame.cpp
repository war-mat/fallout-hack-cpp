#include "../include/FalloutGame.h"

// constructor
FalloutGame::FalloutGame(void) 
    : words_(FalloutWords("/usr/share/dict/words")),
    text_(FalloutText(
            row_start_, left_text_start_, 32, line_width_, num_rows_)),
    display_(FalloutDisplay(line_width_, num_rows_)),
    // cursor variables are weird, need to reevaluate just how many are actually needed
    cursor_(FalloutCursor(row_start_, left_text_start_, row_start_,
            line_width_, num_rows_, left_text_start_, right_text_start_))
    //int initial_y, int initial_x, int row_start, int line_width, 
    //int num_rows, int left_text_start, int right_text_start)
{
    //
}

void FalloutGame::set_game_word_params(void)
{
    word_length_ = levels_[curr_level_][0];
    num_words_ = levels_[curr_level_][1];
    match_limit_ = levels_[curr_level_][2];
}

void FalloutGame::new_game(int level)
{
    // set current level
    curr_level_ = level;
    
    // clear all text on screen
    display_.clear_all();
    
    // clear right text list
    text_.reset_text_list();
    
    // set word parameters
    set_game_word_params();
    
    // reset attempts
    attempts_ = 4;
}

void FalloutGame::update_upper_text(void)
{
    // clear command/warning line
    display_.move_print_string_delay(std::string(35, ' '), 1, 2, 0);
    
    // update current command/warning line
    if (attempts_ > 1)
    {
        display_.move_print_string_char_dly(
                text_.get_top_text("command"), 1, 2, 0);
    }            
    else
    {
        display_.move_print_string_char_dly(
            text_.get_top_text("warning"), 1, 2, 0);
    }

    // clear attempts indicators
    display_.move_print_string_delay(std::string(8, ' '), 18, 4, 0);
    
    // print remaining attempts
    display_.print_attempts(attempts_, 0);
}

std::string FalloutGame::take_turn(void)
{
    update_upper_text();
    
    std::string result = "";
    
    // check attempts remaining, fail if 0
    if (attempts_ < 1)
    {
        result = "lose";
    }
    else
    {
        while (true)
        {
            std::vector < Character > highlighted;
            
            std::vector < Character > hl_list = text_.get_highlighted(
                    cursor_.get_side(), cursor_.get_cursor_y(), 
                    cursor_.get_cursor_x());
                    
            // get character or word under cursor
            std::string selected_word = text_.get_selected_word();
            
            // highlight character or word under cursor
            display_.highlight(hl_list, 1);
            
            // print selected word at right cursor position
            display_.print_right(selected_word);
            
            int input_char = getch();

            if (input_char == 'q')
            {
                result = "quit";
                break;
            }
            else if (input_char == ' ')
            {
                // check is selected is a word, bracket set, or neither
                break;
            }
            else
            {
                // handle input
                cursor_.handle_arrow_keys(input_char);
            }
            
            // revert highlight
            display_.highlight(hl_list, 0);
        }
    }
    
    return result;
}

/*
    def take_turn(self):
        
        self.update_upper_text()
        
        result = ""
        
        # check attempts remaing, fail if 0
        if self.attempts_left < 1:
            result = "lose"
        else:

            highlighted = self.game_text.get_highlighted(
                    self.cursor.side, self.cursor.cursor_y, 
                    self.cursor.cursor_x)
                
        
            # get character or word under cursor
            selected_word = self.game_text.get_selected_word(highlighted)
            
            # highlight character or word under cursor
            self.display.highlight(highlighted, 1)
            
            # print selected word at right cursor position
            self.display.print_right(selected_word, 0, 0)
            
            char = self.screen.getch()
            * 
            * 
                
            if char == ord('q'):
                result = "quit"
                
            elif char == ord(' '):
                
                # check if selected is a word, bracket set, or neither
                
                # write handler functions for word and bracket set
                
                if self.game_text.is_word(highlighted):
                        
                    # check if password or not
                    if selected_word == self.password:

                        # need "win" functionality here
                        
                        self.display.print_right("password", 0, 0)
                            
                        char = self.screen.getch()
                        
                        result = "win"
                    else:
                        
                        self.wrong_word(selected_word)
                        
                elif self.game_text.is_bracket_set(highlighted):
                    
                    # add selected bracket set to right text list
                    self.game_text.add_right_line(selected_word)
                    
                    # handle bracket selection
                    self.bracket_set_selected(highlighted)
                    
                    
                        
            else:
                # handle input
                self.cursor.handle_arrow_keys(char)
                
            # revert highlight
            self.display.highlight(highlighted, 0)
                
        return result
*/

// change this return type to bool, with true for win and false for loss
std::string FalloutGame::play_game(void)
{
    // print logo at top
    display_.move_print_string_char_dly(text_.get_top_text("logo"), 1, 1, 25);
    
    // print command line
    display_.move_print_string_char_dly(
            text_.get_top_text("command"), 1, 2, 25);
    
    // print remaining attempts
    display_.print_attempts(attempts_, 25);
    
    // display main text block
    display_.print_game_text(
            1, 6, text_.get_left_right_text("left"), 
            text_.get_left_right_text("right"), text_.get_address_list());
            
    //words_.report_values();
    
    // main game loop
    while (1)
    {
        /*
        result = self.take_turn()
            
        if result == "quit":
            break
        elif result == "win":
            return "win"
        elif result == "lose":
                
            # print lockout text
            break
        */
        
        std::string result = take_turn();
        if (result == "quit")
        {
            break;
        }
        else if (result == "lose")
        {
            break;
        }
        
    }
    
    return "lose";
}

/*
    def new_game(self, level):
        
        # generate distribution of random number of character matches
        self.match_distribution = self.linear_distrib(
                self.num_words, self.match_limit)
        
        self.game_text.left_text, self.game_text.right_text, self.password, \
                self.candidate_list = self.words.new_game(
                        self.word_length, self.num_words, 
                        self.match_distribution, self.line_width, self.num_rows)
                        
        self.update_text_arrays()
*/

// make per char delay a variable to adjust in one place
