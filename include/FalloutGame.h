#ifndef FALLOUT_GAME_H
#define FALLOUT_GAME_H

#define _XOPEN_SOURCE_EXTENDED

#include <locale.h>
#include <ncursesw/curses.h>
#include <unistd.h>

#include <cstdlib>
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include "FalloutText.h"
#include "FalloutWords.h"
#include "FalloutDisplay.h"
#include "FalloutCursor.h"

class FalloutGame
{
private:
    std::string password;
    
    std::vector < std::string > candidate_list;
    
    // index = level, (word_length, num_words, match_limit)
    std::vector < std::vector<int> > levels_ = {
            {6, 15, 4},
            {6, 15, 3},
            {7, 15, 4},
            {7, 15, 3},
            {8, 15, 4},
            {8, 15, 3}
            };
    
    // current level        
    int curr_level_;
    
    // attempts left
    int attempts_;
    
    // word constants (based on difficulty)
    int word_length_;
    int num_words_;
    int match_limit_;
    
    // text/display constants
    int line_width_ = 15;
    int num_rows_ = 17;
    int row_start_ = 6;
    int left_text_start_ = 8;
    int right_text_start_ = left_text_start_ + line_width_ + 9;
    int right_cursor_pos_ = 49;
    
    
    FalloutWords words_;
    
    // game text object
    FalloutText text_;

    FalloutDisplay display_;
    
    FalloutCursor cursor_;
    
public:
    FalloutGame(void);
    void set_game_word_params(void);
    //void test_run(void);
    void new_game(int level);
    std::string play_game(void);
    void update_upper_text(void);
    std::string take_turn(void);
};

#endif
