#ifndef FALLOUT_TEXT_H
#define FALLOUT_TEXT_H

#include <map>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <unordered_set>
#include <tuple>
#include <algorithm>

class Character
{
private:
    char character_;
    int screen_y_;
    int screen_x_;
    
public:
    Character(char character, int screen_y, int screen_x);
    char get_char(void);
    int get_y(void);
    int get_x(void);
};

class FalloutText
{
private:
    
    std::map <std::string, std::string> top_text = {
            {"logo", "ROBCO INDUSTRIES (TM) TERMLINK PROTOCOL"},
            {"command", "ENTER PASSWORD NOW"},
            {"warning", "!!! WARNING: LOCKOUT IMMINENT !!!"}
            };
    
    // text up-down bounds (screen coords)        
    int row_start_;
    int row_end_;
    
    int left_col_start_;
    int right_col_start_;
    int line_width_;
    unsigned int num_rows_;
    
    // left text column bounds (screen coords)
    int left_lower_;
    int left_upper_;
    
    // right column bounds (screen coords)
    int right_lower_;
    int right_upper_;
    
    // random starting memory address
    int start_address_;
    
    // list of hex memory addresses
    std::vector < std::string > address_list_;
    
    // original text strings for searching through
    std::string left_text_;
    std::string right_text_;
    
    // array for storing right side text strings
    std::vector < std::string > right_text_list_ = {};
    int right_max_lines_ = 20;
    unsigned int max_bracket_len_ = 20;
    
    std::unordered_set < char > alphabet_ = {
            'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q',
            'R','S','T','U','V','W','X','Y','Z'};
    std::unordered_set < char > junk_ = {
            '$','.','\'',':','_','!','\\','"','+','-','%','/','|','*','@','#',
            '`','=','^',';','?',','};
    std::vector < char > left_brackets_ = {'(', '[', '<', '{'};
    std::vector < char > right_brackets_ = {')', ']', '>', '}'};
    
    // need a function to return a reference to this vector
    // make sure Im returning references right
    std::vector < Character > hl_list_;
    
    FalloutText() { } // private default constructor
    
public:
    FalloutText(int row_start, int left_col_start, int right_col_start, 
            int line_width, int num_rows);
    void report_values(void);
    int set_start_address(void);
    void gen_address_list(void);
    std::string int_address_to_hex_string(int address);
    void gen_junk_strings(void);
    const std::string & get_top_text(std::string key);
    const std::string & get_left_right_text(std::string side);
    const std::vector < std::string > & get_address_list(void);
    int screen_coords_to_index(std::string side, int screen_y, int screen_x);
    std::tuple < int, int > index_to_screen_coords(std::string side, int index);
    void reset_text_list(void);
    const std::vector < Character > & get_highlighted(
            std::string side, int cursor_y, int cursor_x);
    std::string get_selected_word(void);
    bool is_alpha(char character);
    bool is_left_bracket(char character);
    bool is_right_bracket(char character);
    void check_bracket_left(
            std::string side, int index, char matching_char);
    void check_bracket_right(
            std::string side, unsigned int index, char matching_char);
    char get_left_bracket(char right_bracket);
    char get_right_bracket(char left_bracket);
};

#endif
