#ifndef FALLOUT_GAME_H
#define FALLOUT_GAME_H

#include <vector>
#include <iostream>

#include "FalloutText.h"
#include "FalloutWords.h"

class FalloutGame
{
private:
    
    
    std::string password = "";
    
    std::vector < std::string > candidate_list;
    
    // index = level, (word_length, num_words, match_limit)
    std::vector < std::vector<int> > levels = {
            {6, 15, 4},
            {6, 15, 3},
            {7, 15, 4},
            {7, 15, 3},
            {8, 15, 4},
            {8, 15, 3}
            };
    
    // current level        
    int curr_level_;
    
    // word constants (based on difficulty)
    int word_length_;
    int num_words_;
    int match_limit_;
    
    // text/display constants
    int line_width_ = 15;
    int num_rows_ = 17;
    int row_start_ = 6;
    int left_text_start_ = 8;
    int right_text_start_ = left_text_start_ + line_width_ + 8;
    int right_cursor_pos_ = 49;
    
    
    //FalloutWords words_;
    FalloutWords words_ = FalloutWords("/usr/share/dict/words");
    
    // initialize game text object    
    FalloutText text_ = FalloutText(row_start_, left_text_start_, 32, 
            line_width_, num_rows_);
    
    //FalloutGame() { } // private default constructor
    
public:
    FalloutGame(int curr_level);
    void report_values(void);
    void set_game_word_params(void);
};

#endif
